import { exec } from 'child_process';
import * as path from 'path';
import { ofType } from 'redux-observable';
import { from, merge, Observable, of, zip } from 'rxjs';
import { catchError, filter, mapTo, switchMap } from 'rxjs/operators';
import * as which from 'which';
import { Config } from '../../config';
import { R } from '../../resources';
import { copy, getTempPath } from '../../utils/files.util';
import { sudoExec } from '../../utils/sudo.util';
import {
  DB_ACTIONS,
  InstallationStage,
  installFuzzyExtension,
  InstallFuzzyExtensionAction,
  setMetadata
} from './db.actions';
import { ExtensionInstallation } from './db.state';

interface Paths {
  extensionPath: string;
  libraryPath: string;
}

const PG_CONFIG_COMMAND = 'pg_config';

const setInstallationStatus = (databaseId: string, extensionInstallation: ExtensionInstallation) => of(setMetadata({
  databaseId,
  extensionInstallation,
}));

const resolveCommand = (command: string) => new Promise<string>((resolve, reject) => {
  which(command, { all: false }, (err, path) => {
    if (err) {
      return reject(new Error(`Could not find "${command}" executable.`));
    }
    return resolve(path);
  });
});

const findPaths = (): Promise<Paths> => resolveCommand(PG_CONFIG_COMMAND).then(commandPath =>
  new Promise<Paths>((resolve, reject) => {
    exec(commandPath, { encoding: 'utf8', windowsHide: true, timeout: 5000 }, (error, stdout, stderr) => {
      if (error) {
        error.message += '\n' + stderr;
        return reject(error);
      }
      const result = { extensionPath: '', libraryPath: '' };
      const libraryPathMatch = stdout.match(/PKGLIBDIR\s*=\s*(.+?)\r?\n/);
      const dataPathMatch = stdout.match(/SHAREDIR\s*=\s*(.+?)\r?\n/);
      if (libraryPathMatch) {
        result.libraryPath = libraryPathMatch[1];
      }
      if (dataPathMatch) {
        result.extensionPath = path.join(dataPathMatch[1], 'extension');
      }
      if (result.extensionPath && result.libraryPath) {
        return resolve(result);
      }
      console.log(stdout);
      reject(new Error('Fuzzybase couldn\'t find location of PostgreSQL files.'));
    });
  })
);

const extractExtensionAsSudo$ = (connectionId: string, databaseId: string, paths: Paths): Observable<any> => merge(
  setInstallationStatus(databaseId, {
    status: 'progress',
    message: 'Copying extension files to temporary location...',
  }),
  zip(
    copy(
      path.join(R.string.extension, R.string.fuzzyControl),
      path.join(getTempPath(), R.string.fuzzyControl)
    ),
    copy(
      path.join(R.string.extension, R.string.fuzzySql),
      path.join(getTempPath(), R.string.fuzzySql)
    ),
    copy(
      path.join(R.string.extension, R.string.fuzzyLibrary),
      path.join(getTempPath(), R.string.fuzzyTargetLibrary)
    )
  ).pipe(
    switchMap(() => {
      const cp = Config.IS_WINDOWS ? 'xcopy' : 'cp';
      const temp = getTempPath();
      return sudoExec(`
        ${cp} ${path.join(temp, R.string.fuzzyControl)} ${paths.extensionPath}
        ${cp} ${path.join(temp, R.string.fuzzySql)} ${paths.extensionPath}
        ${cp} ${path.join(temp, R.string.fuzzyTargetLibrary)} ${paths.libraryPath}
      `, {
        name: 'Fuzzybase',
      });
    }),
    mapTo(installFuzzyExtension(connectionId, InstallationStage.RECREATE_EXTENSION))
  )
);

const extractExtension$ = (connectionId: string, databaseId: string): Observable<any> => merge(
  setInstallationStatus(databaseId, {
    status: 'progress',
    message: 'Looking for PostgreSQL extension paths...',
  }),
  from(findPaths()).pipe(
    switchMap(paths => merge(
      setInstallationStatus(databaseId, {
        status: 'progress',
        message: 'Copying extension files to PostgreSQL directories...',
      }),
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
        mapTo(installFuzzyExtension(connectionId, InstallationStage.RECREATE_EXTENSION)),
        catchError(() => extractExtensionAsSudo$(connectionId, databaseId, paths))
      )
    )),
    catchError(error => setInstallationStatus(databaseId, {
      status: 'error',
      message: error.message,
    }))
  )
);

export const extractFuzzyExtension$ = (action$: Observable<any>) => action$
  .pipe(
    ofType<InstallFuzzyExtensionAction>(DB_ACTIONS.INSTALL_FUZZY_EXTENSION),
    filter(action => action.stage === InstallationStage.EXTRACT_FILES),
    switchMap((action) => extractExtension$(action.connectionId, action.databaseId))
  );
