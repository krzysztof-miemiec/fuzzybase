import { exec } from 'child_process';
import { app } from 'electron';
import * as path from 'path';
import { ofType } from 'redux-observable';
import { from, merge, Observable, of, zip } from 'rxjs';
import { catchError, filter, mapTo, switchMap } from 'rxjs/operators';
import { Config } from '../../config';
import { R } from '../../resources';
import { copy } from '../../utils/files.util';
import { sudoExec } from '../../utils/sudo.util';
import {
  DB_ACTIONS,
  InstallationStage,
  installFuzzyExtension,
  InstallFuzzyExtensionAction,
  setMetadata
} from './db.actions';

interface Paths {
  extensionPath: string;
  libraryPath: string;
}

const PG_CONFIG_COMMAND = 'pg_config';
const execOptions = { encoding: 'utf8', windowsHide: true, timeout: 5000 };

const setInstallationStatus = (databaseId: string, status: string) => setMetadata({
  databaseId,
  extensionInstallation: { status },
});

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
        const dataPathMatch = stdout.match(/SHAREDIR\s*=\s*(.+?)\n/);
        if (libraryPathMatch) {
          result.libraryPath = libraryPathMatch[1];
        }
        if (dataPathMatch) {
          result.extensionPath = path.join(dataPathMatch[1], 'extension');
        }
        if (result.extensionPath && result.libraryPath) {
          return resolve(result);
        }
        reject(new Error('Fuzzybase couldn\'t find location of PostgreSQL files.'));
      }
    );
  });
};

const extractExtensionAsSudo$ = (databaseId: string, paths: Paths): Observable<any> => merge(
  of(setInstallationStatus(databaseId, 'Copying extension files to temporary location...')),
  zip(
    copy(
      path.join(R.string.extension, R.string.fuzzyControl),
      path.join(app.getPath('temp'), R.string.fuzzyControl)
    ),
    copy(
      path.join(R.string.extension, R.string.fuzzySql),
      path.join(app.getPath('temp'), R.string.fuzzySql)
    ),
    copy(
      path.join(R.string.extension, R.string.fuzzyLibrary),
      path.join(app.getPath('temp'), R.string.fuzzyTargetLibrary)
    )
  ).pipe(
    switchMap(() => {
      const cp = Config.IS_WINDOWS ? 'xcopy' : 'cp';
      const temp = app.getPath('temp');
      return sudoExec(`
        ${cp} ${path.join(temp, R.string.fuzzyControl)} ${paths.extensionPath}
        ${cp} ${path.join(temp, R.string.fuzzySql)} ${paths.extensionPath}
        ${cp} ${path.join(temp, R.string.fuzzyTargetLibrary)} ${paths.libraryPath}
      `);
    })
  )
);

const extractExtension$ = (connectionId: string, databaseId: string): Observable<any> => merge(
  of(setInstallationStatus(databaseId, 'Looking for PostgreSQL extension paths...')),
  from(findPaths())
    .pipe(
      switchMap(paths => merge(
        of(setInstallationStatus(databaseId, 'Copying extension files to PostgreSQL directories...')),
        zip(
          copy(
            path.join(R.string.extension, R.string.fuzzyControl),
            path.join(paths.extensionPath, R.string.fuzzyControl)
          ),
          copy(
            path.join(R.string.extension, R.string.fuzzySql),
            path.join(paths.extensionPath, R.string.fuzzySql)
          ),
          copy(
            path.join(R.string.extension, R.string.fuzzyLibrary),
            path.join(paths.libraryPath, R.string.fuzzyTargetLibrary)
          )
        ).pipe(
          catchError(() => extractExtensionAsSudo$(databaseId, paths)),
          mapTo(installFuzzyExtension(connectionId, InstallationStage.RECREATE_EXTENSION))
        )
      )),
      catchError(error => of({ status: error.message, error: true }))
    )
);

export const extractFuzzyExtension$ = (action$: Observable<any>) => action$
  .pipe(
    ofType<InstallFuzzyExtensionAction>(DB_ACTIONS.INSTALL_FUZZY_EXTENSION),
    filter(action => action.stage === InstallationStage.EXTRACT_FILES),
    switchMap((action) => extractExtension$(action.connectionId, action.databaseId))
  );
