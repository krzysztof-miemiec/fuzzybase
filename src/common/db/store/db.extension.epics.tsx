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

const findPaths = async (): Promise<{
  extensionPath: string,
  libraryPath: string,
}> => {
  const result = { extensionPath: '', libraryPath: '' };
  new Promise(((resolve, reject) => {
    exec('pg_config', { encoding: 'utf8', windowsHide: true, timeout: 5000 },
      (error, stdout, stderr) => {
        if (error) {
          console.log(stderr);
          return reject(error);
        }
        const libraryPathMatch = stdout.match(/PKGLIBDIR\s*=\s*(.+?)\n/);
        const dataPathMatch = stdout.match(/'--datadir=(.+?)'/);
        if (libraryPathMatch) {
          result.libraryPath = libraryPathMatch[1];
        }
        if (dataPathMatch) {
          result.extensionPath = path.join(dataPathMatch[1], 'extension');
        }
        if (result.extensionPath && result.libraryPath) {
          return resolve(result);
        }
      }
    );
  }));
};

const extractFile = (): Observable<ExtensionInstallation> => {
  const subject = new Subject<ExtensionInstallation>();
  (async () => {
    try {
      subject.next({ status: 'Copying extension source...' });
      const extension = path.join(app.getPath('temp'), 'extension');
      const processOptions = {
        encoding: 'utf8', cwd: extension, windowsHide: true,
      };
      await copy(R.string.fuzzyPackage, extension);
      subject.next({ status: 'Building an extension...' });

      const makeProcess = exec(`make clean all`, processOptions);

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
