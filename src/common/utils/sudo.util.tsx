import { app } from 'electron';
import * as path from 'path';
import { Observable, Subscriber } from 'rxjs';
import * as sudo from 'sudo-prompt';
import { Config } from '../config';
import { writeFile } from './files.util';

interface Options {
  name?: string;
  icns?: string;
}

interface SudoExecResult {
  stdout: string;
  stderr: string;
}

export const sudoExec = (script: string, options?: Options): Observable<SudoExecResult> =>
  new Observable((observer: Subscriber<SudoExecResult>) => {
    let run = true;
    const scriptPath = path.join(app.getPath('temp'), Config.IS_WINDOWS ? 'script.cmd' : 'script.sh');
    writeFile(scriptPath, '#!/bin/bash\nset -e\n\n' + script, { encoding: 'utf8', mode: 755 }).then(() => {
      if (!run) {
        return;
      }
      sudo.exec(`${path}`, options, (error, stdout, stderr) => {
        if (!run) {
          return;
        }
        observer.next({ stdout, stderr });
        if (error) {
          observer.error(error);
        }
        observer.complete();
      });
    });
    return () => run = false;
  });
