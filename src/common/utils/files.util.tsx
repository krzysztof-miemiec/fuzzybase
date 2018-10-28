import { app, dialog, remote } from 'electron';
import { createReadStream, createWriteStream, stat, writeFile as fsWriteFile } from 'fs';
import * as mkdirp from 'mkdirp';
import * as path from 'path';
import { Observable, Subject, Subscriber } from 'rxjs';
import { promisify } from 'util';
import SaveDialogOptions = Electron.SaveDialogOptions;

export interface CopyStatus {
  progress: number;
}

export const getTempPath = (): string => path.join(app.getPath('temp'), 'fuzzybase');

export const showSaveDialog = (options: SaveDialogOptions): Observable<string> => {
  const subject = new Subject<string>();
  (dialog || remote.dialog).showSaveDialog(options, (filename) => {
    if (!filename) {
      return subject.error(new Error('Save operation canceled.'));
    }
    subject.next(filename);
    subject.complete();
  });
  return subject.asObservable();
};

export const writeFile = promisify(fsWriteFile);

export const copy = (source: string, destination: string): Observable<CopyStatus> =>
  Observable.create((subscriber: Subscriber<CopyStatus>) => {
    let done = false;
    const onlyOnce = (fn: (...args: any[]) => void) => (...args: any[]) => {
      if (done) {
        return;
      }
      done = true;
      fn(args);
    };
    mkdirp(path.dirname(destination), err => {
      if (err) {
        subscriber.error(err);
        subscriber.complete();
        return;
      }
      if (done) {
        subscriber.complete();
        return;
      }
      stat(source, (err, stats) => {
        if (err) {
          subscriber.error(err);
          subscriber.complete();
          return;
        }
        if (done) {
          subscriber.complete();
          return;
        }
        const totalSize = stats.size || 1;
        let readSize = 0;
        const readStream = createReadStream(source);
        const writeStream = createWriteStream(destination);
        const onError = onlyOnce((err: Error) => {
          subscriber.error(err);
          subscriber.complete();
        });
        readStream.on('data', data => {
          if (done) {
            return;
          }
          readSize += data.length;
          subscriber.next({ progress: Math.min(1, readSize / totalSize) });
        });
        readStream.on('error', onError);
        writeStream.on('error', onError);
        readStream.on('end', onlyOnce(() => {
          writeStream.close();
          readStream.close();
          subscriber.next({ progress: 1 });
          subscriber.complete();
        }));
        readStream.pipe(writeStream);
      });
    });
    return () => done = true;
  });
