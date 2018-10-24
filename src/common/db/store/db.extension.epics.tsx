import { ofType } from 'redux-observable';
import { Observable } from 'rxjs';
import { map } from 'rxjs/operators';
import { DB_ACTIONS, ExtractFuzzyExtensionAction } from './db.actions';
/*
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

const extractExtension = (): Observable<ExtensionInstallation> => {
  const subject = new Subject<ExtensionInstallation>();
  (async () => {
    try {
      subject.next({ status: 'Looking for PostgreSQL extension paths...' });
      const { extensionPath, libraryPath } = await findPaths();
      subject.next({ status: 'Copying extension files to PostgreSQL directories...' });
      await copy(
        path.join(R.string.extension, 'fuzzy.control'),
        path.join(extensionPath, 'fuzzy.control')
      );
      await copy(
        path.join(R.string.extension, 'fuzzy--0.0.2.sql'),
        path.join(extensionPath, 'fuzzy--0.0.2.sql')
      );
      await copy(
        path.join(R.string.extension, R.string.fuzzyLibrary),
        path.join(libraryPath, R.string.fuzzyTargetLibrary)
      );
    } catch (error) {
      subject.next({ status: error.message, error: true });
      subject.complete();
    }
  })();
  return subject;
};*/

export const extractFuzzyExtension$ = (action$: Observable<any>) => action$
  .pipe(
    ofType<ExtractFuzzyExtensionAction>(DB_ACTIONS.EXTRACT_FUZZY_EXTENSION),
    map(() => ({ type: 'DUPA' }))
  );
