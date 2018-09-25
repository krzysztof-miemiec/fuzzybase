import { ofType, StateObservable } from 'redux-observable';
import { Observable, of } from 'rxjs';
import { filter, map, take } from 'rxjs/operators';
import { AppState } from '../../../renderer/store';
import { select } from '../../../renderer/utils/selector.util';
import { DB_ACTIONS, postgresQuery, PostgresQueryResultAction, setMetadata } from './db.actions';
import { getConnection, getDatabasesState } from './db.selectors';
import { findFieldByName } from './db.utils';

export const USER_NAME_QUERY_ID = 'user_name';
export const TABLES_QUERY_ID = 'table_metadata';

export const getUserName = (connectionId: string) => of(postgresQuery(
  connectionId,
  USER_NAME_QUERY_ID,
  `SELECT current_user;`
));

export const processUserNameQueryResponse = (action$: Observable<any>, state$: StateObservable<AppState>) =>
  action$.pipe(
    ofType<PostgresQueryResultAction>(DB_ACTIONS.QUERY_RESULT),
    filter(action => action.queryId === USER_NAME_QUERY_ID),
    take(1),
    map(action => {
      const { rows } = action.result;
      const connection = select(state$.value, getDatabasesState, getConnection(action.connectionId));

      const user = rows[0][0];

      return setMetadata({
        databaseId: connection.clientId,
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
       AND t.table_schema NOT IN ('pg_catalog', 'information_schema');`
));

export const processTablesQueryResponse = (action$: Observable<any>, state$: StateObservable<AppState>) =>
  action$.pipe(
    ofType<PostgresQueryResultAction>(DB_ACTIONS.QUERY_RESULT),
    filter(action => action.queryId === TABLES_QUERY_ID),
    take(1),
    map(action => {
      const { fields, rows } = action.result;
      const connection = select(state$.value, getDatabasesState, getConnection(action.connectionId));
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
        databaseId: connection.clientId,
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
