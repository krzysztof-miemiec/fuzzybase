import { ofType, StateObservable } from 'redux-observable';
import { concat, Observable, of } from 'rxjs';
import { filter, map, switchMap, take, withLatestFrom } from 'rxjs/operators';
import { AppState } from '../../../renderer/store';
import { select } from '../../utils/selector.util';
import {
  DB_ACTIONS,
  getMetadata,
  InstallationStage,
  installFuzzyExtension,
  postgresQuery,
  PostgresQueryResultAction,
  setMetadata
} from './db.actions';
import { getConnection, getDatabasesState } from './db.selectors';
import { ExtensionInstallation, FuzzyFunction, FuzzyType } from './db.state';
import { findFieldByName } from './db.utils';

export const USER_NAME_QUERY_ID = 'user_name';
export const FUZZY_FUNCTIONS_ID = 'fuzzy_functions';
export const SEARCH_PATH_ID = 'search_paths';
export const TABLES_QUERY_ID = 'table_metadata';
export const CREATE_FUZZY_EXTENSION_ID = 'create_fuzzy_extension';

export const createFuzzyExtension = (connectionId: string) => of(postgresQuery(
  connectionId,
  CREATE_FUZZY_EXTENSION_ID,
  `CREATE EXTENSION fuzzy;`,
  true
));

export const processCreateFuzzyExtensionResponse = (
  action$: Observable<any>,
  state$: StateObservable<AppState>,
  extractOnFailure: boolean
) =>
  action$.pipe(
    ofType<PostgresQueryResultAction>(DB_ACTIONS.QUERY_RESULT),
    filter(action => action.queryId === CREATE_FUZZY_EXTENSION_ID),
    take(1),
    withLatestFrom(state$),
    switchMap(([action, state]): Observable<any> => {
      const connection = select(state, getDatabasesState, getConnection(action.connectionId));

      const hasError = (error?: string) => action.error && action.error.match(new RegExp(error, 'i'));
      const setInstallationStatus = (extensionInstallation: ExtensionInstallation) => of(setMetadata({
        databaseId: connection.databaseId, extensionInstallation,
      }));
      const installExtension = () => of(installFuzzyExtension(
        connection.connectionId,
        InstallationStage.EXTRACT_FILES,
        connection.databaseId
      ));

      const installationSuccessful = !hasError();

      if (!installationSuccessful) {
        if (hasError('extension "fuzzy" already exists')) {
          return setInstallationStatus({
            status: 'error', message: 'Extension is already installed.',
          });
        }
        if (hasError('permission denied to create extension')) {
          if (extractOnFailure) {
            return installExtension();
          }
          return setInstallationStatus({
            status: 'error', message: 'Current PostgreSQL user doesn\'t have permissions to install the extension.',
          });
        }
        if (extractOnFailure && (
          hasError('could not open extension control file') ||
          hasError('has no installation script nor update path') ||
          hasError('no such file or')
        )) {
          return installExtension();
        }
        return setInstallationStatus({
          status: 'error', message: 'An error occurred: ' + action.error,
        });
      }
      return concat(
        of(getMetadata(action.connectionId)),
        setInstallationStatus({
          status: 'success',
        })
      );
    })
  );

export const getSearchPath = (connectionId: string) => of(postgresQuery(
  connectionId,
  SEARCH_PATH_ID,
  `SHOW search_path;`,
  true
));

export const processSearchPathQueryResponse = (action$: Observable<any>, state$: StateObservable<AppState>) =>
  action$.pipe(
    ofType<PostgresQueryResultAction>(DB_ACTIONS.QUERY_RESULT),
    filter(action => action.queryId === SEARCH_PATH_ID),
    take(1),
    withLatestFrom(state$),
    map(([action, state]) => {
      const connection = select(state, getDatabasesState, getConnection(action.connectionId));
      const DEFAULT_SEARCH_PATH = '"$user", public';
      const searchPathString = (action.result && action.result.rows[0][0] || DEFAULT_SEARCH_PATH);
      return setMetadata({
        databaseId: connection.databaseId,
        searchPath: searchPathString.split(',')
          .map(str => str.replace(/^"(.*)"$/, '$1')),
      });
    })
  );

export const getFuzzyFunctions = (connectionId: string) => of(postgresQuery(
  connectionId,
  FUZZY_FUNCTIONS_ID,
    `SELECT *
     FROM get_fuzzy_functions();`,
  true
));

export const processFuzzyFunctionsQueryResponse = (action$: Observable<any>, state$: StateObservable<AppState>) =>
  action$.pipe(
    ofType<PostgresQueryResultAction>(DB_ACTIONS.QUERY_RESULT),
    filter(action => action.queryId === FUZZY_FUNCTIONS_ID),
    take(1),
    withLatestFrom(state$),
    map(([action, state]) => {
      const connection = select(state, getDatabasesState, getConnection(action.connectionId));
      const hasFuzzyExtension = !action.error;
      const fuzzyTypes: Record<string, FuzzyType> = {};
      if (hasFuzzyExtension) {
        for (let [, typeName, name, fun] of action.result.rows) {
          const type = fuzzyTypes[typeName]
            || (fuzzyTypes[typeName] = { name: typeName, functions: [] as FuzzyFunction[] });
          const fuzzyFunction: FuzzyFunction = {
            name,
            range: fun.split(/[/\\~]/).map(n => parseFloat(n)),
          };
          type.functions.push(fuzzyFunction);
        }
      }
      return setMetadata({
        databaseId: connection.databaseId,
        hasFuzzyExtension,
        fuzzyTypes,
      });
    })
  );

export const getUserName = (connectionId: string) => of(postgresQuery(
  connectionId,
  USER_NAME_QUERY_ID,
  `SELECT current_user;`,
  true
));

export const processUserNameQueryResponse = (action$: Observable<any>, state$: StateObservable<AppState>) =>
  action$.pipe(
    ofType<PostgresQueryResultAction>(DB_ACTIONS.QUERY_RESULT),
    filter(action => action.queryId === USER_NAME_QUERY_ID),
    take(1),
    withLatestFrom(state$),
    map(([action, state]) => {
      const { rows } = action.result;
      const connection = select(state, getDatabasesState, getConnection(action.connectionId));

      const user = rows[0][0];

      return setMetadata({
        databaseId: connection.databaseId,
        user,
      });
    })
  );

export const getTables = (connectionId: string) => of(postgresQuery(
  connectionId,
  TABLES_QUERY_ID,
    `SELECT *
     FROM information_schema.tables t,
          information_schema.columns c
     WHERE t.table_name = c.table_name
       AND t.table_schema = c.table_schema
       AND t.table_catalog = c.table_catalog
       AND t.table_schema NOT IN ('pg_catalog', 'information_schema');`,
  true
));

export const processTablesQueryResponse = (action$: Observable<any>, state$: StateObservable<AppState>) =>
  action$.pipe(
    ofType<PostgresQueryResultAction>(DB_ACTIONS.QUERY_RESULT),
    filter(action => action.queryId === TABLES_QUERY_ID),
    take(1),
    withLatestFrom(state$),
    map(([action, state]) => {
      const { fields, rows } = action.result;
      const connection = select(state, getDatabasesState, getConnection(action.connectionId));
      const field = findFieldByName(fields);
      const catalogName = field('table_catalog');
      const schemaName = field('table_schema');
      const tableName = field('table_name');
      const columnName = field('column_name');
      const ordinalPosition = field('ordinal_position');
      const columnDefault = field('column_default');
      const isNullable = field('is_nullable');
      const udtName = field('udt_name');
      const dataType = field('data_type');
      return setMetadata({
        databaseId: connection.databaseId,
        tables: rows
          .map((row: any[]) => ({
            catalog: catalogName(row),
            name: tableName(row),
            schema: schemaName(row),
            fields: [
              {
                index: ordinalPosition(row),
                name: columnName(row),
                'default': columnDefault(row),
                nullable: isNullable(row),
                dataType: dataType(row) === 'USER_DEFINED' ? udtName(row) : dataType(row),
              },
            ],
          }))
          .reduce((tables, table) => {
            const fullName = `${table.catalog}.${table.schema}.${table.name}`;
            let tableEntry = tables[fullName];
            if (!tableEntry) {
              tables[fullName] = table;
            } else {
              tableEntry.fields.push(table.fields[0]);
            }
            return tables;
          }, {}),
      });
    })
  );
