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

export const sudoExec = (script: string, options: Options = {}): Observable<SudoExecResult> =>
  new Observable((observer: Subscriber<SudoExecResult>) => {
    let run = true;
    const scriptPath = path.join(app.getPath('temp'), Config.IS_WINDOWS ? 'script.cmd' : 'script.sh');
    let fullScript = Config.IS_WINDOWS ? '' : '#!/bin/bash\nset -e\n' + script + '\n';
    if (Config.IS_WINDOWS) {
      fullScript = fullScript.replace(/\n/g, '\r\n');
    }
    writeFile(scriptPath, fullScript, { encoding: 'utf8', mode: 755 }).then(() => {
      if (!run) {
        return;
      }
      sudo.exec(scriptPath, options, (error, stdout, stderr) => {
        if (!run) {
          return;
        }
        if (error) {
          observer.error(error);
        } else {
          observer.next({ stdout, stderr });
        }
        observer.complete();
      });
    });
    return () => run = false;
  });
