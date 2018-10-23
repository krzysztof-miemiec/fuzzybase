import { dialog, remote } from 'electron';
import { createReadStream, createWriteStream, stat } from 'fs';
import { Observable, Observer, Subject } from 'rxjs';
import SaveDialogOptions = Electron.SaveDialogOptions;

export interface CopyStatus {
  progress: number;
}

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

export const copy = (source: string, destination: string): Observable<CopyStatus> => {
  let observers = [];
  let done = false;
  const subject: Subject<CopyStatus> = Subject.create((observer: Observer<CopyStatus>) => {
    observers.push(observer);
    return () => {
      observers.splice(observers.indexOf(observer), 1);
      if (!observers.length) {
        done = true;
      }
    };
  });
  setTimeout(() => {
    stat(source, (err, stats) => {
      if (err) {
        subject.error(err);
        subject.complete();
        return;
      }
      if (done) {
        subject.complete();
        return;
      }
      const totalSize = stats.size || 1;
      let readSize = 0;
      const readStream = createReadStream(source);
      const writeStream = createWriteStream(destination);
      const onError = (err: Error) => {
        if (done) {
          return;
        }
        done = true;
        subject.error(err);
        subject.complete();
      };
      readStream.on('data', data => {
        if (done) {
          return;
        }
        readSize += data.length;
        subject.next({ progress: Math.min(1, readSize / totalSize) });
      });
      readStream.on('error', onError);
      writeStream.on('error', onError);
      readStream.on('end', () => {
        if (done) {
          return;
        }
        done = true;
        writeStream.close();
        readStream.close();
        subject.next({ progress: 1 });
        subject.complete();
      });
      readStream.pipe(writeStream);
    });
  }, 0);

  return subject.asObservable();
};
