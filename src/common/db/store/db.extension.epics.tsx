import { exec } from 'child_process';
import { app } from 'electron';
import * as path from 'path';
import { ActionsObservable, StateObservable } from 'redux-observable';
import { concat, Observable, of, Subject } from 'rxjs';
import { switchMap, withLatestFrom } from 'rxjs/operators';
import { AppState } from '../../../renderer/store';
import { R } from '../../resources';
import { copy } from '../../utils/files.util';
import { select } from '../../utils/selector.util';
import { DB_ACTIONS, DbAction, InstallFuzzyExtensionAction, setMetadata } from './db.actions';
import { getConnection, getDatabasesState } from './db.selectors';
import { ExtensionInstallation } from './db.state';
import { createFuzzyExtension, processCreateFuzzyExtensionResponse } from './db.system.epics';

interface Paths {
  extensionPath: string;
  libraryPath: string;
}

const PG_CONFIG_COMMAND = 'pg_config';
const execOptions = { encoding: 'utf8', windowsHide: true, timeout: 5000 };

const commandExists = (command) => new Promise(resolve => {
  const execCommand = process.platform === 'win32'
    ? `${command} >nul 2>nul`
    : `command -v ${command} >/dev/null 2>&1`;
  exec(execCommand, execOptions, error => resolve(!error));
});

const findPaths = async (): Promise<Paths> => {
  const result = { extensionPath: '', libraryPath: '' };
  return new Promise<Paths>(async (resolve, reject) => {
    await commandExists(PG_CONFIG_COMMAND);
    exec(PG_CONFIG_COMMAND, { encoding: 'utf8', windowsHide: true, timeout: 5000 },
      (error, stdout, stderr) => {
        if (error) {
          console.log(stderr);
          return reject(error);
        }
        const libraryPathMatch = stdout.match(/PKGLIBDIR\s*=\s*(.+?)\n/);
        const dataPathMatch = stdout.match(/'SHAREDIR\s*=\s*(.+?)\n/);
        if (libraryPathMatch) {
          result.libraryPath = libraryPathMatch[1];
        }
        if (dataPathMatch) {
          result.extensionPath = path.join(dataPathMatch[1], 'extension');
        }
        if (result.extensionPath && result.libraryPath) {
          return resolve(result);
        }
        reject(new Error('Fuzzybase couldn\'t find '));
      }
    );
  });
};

const extractFile = (): Observable<ExtensionInstallation> => {
  const subject = new Subject<ExtensionInstallation>();
  (async () => {
    try {
      subject.next({ status: 'Looking for PostgreSQL extension paths...' });
      const { extensionPath, libraryPath } = await findPaths();
      subject.next({ status: 'Copying extension source...' });
      const extension = path.join(app.getPath('temp'), 'extension');
      const processOptions = {
        encoding: 'utf8', cwd: extension, windowsHide: true,
      };
      await copy(R.string.fuzzyPackage, extension);
      subject.next({ status: 'Building an extension...' });

    } catch (error) {
      subject.error(error);
      subject.complete();
    }
  })();
  return subject;
};

export const installExtension = (
  action$: ActionsObservable<DbAction>,
  state$: StateObservable<AppState>
) => action$
  .ofType<InstallFuzzyExtensionAction>(DB_ACTIONS.INSTALL_FUZZY_EXTENSION)
  .pipe(
    switchMap(action => concat(
      createFuzzyExtension(action.connectionId),
      processCreateFuzzyExtensionResponse(action$).pipe(
        withLatestFrom(state$),
        switchMap(([success, state]) => {
          if (success) {
            const connection = select(state, getDatabasesState, getConnection(action.connectionId));

            return of(setMetadata({
              databaseId: connection.clientId,
              extensionInstallation: { success: true },
            }));
          }

        })
      )
    ))
  );