import { ActionsObservable, combineEpics, StateObservable } from 'redux-observable';
import { concat, EMPTY, of } from 'rxjs';
import { filter, map, switchMap, take } from 'rxjs/operators';
import { AppState } from '../../../renderer/store';
import { select } from '../../../renderer/utils/selector.util';
import { showSnackbar } from '../../../renderer/views/layout/store/layout.actions';
import {
  ConnectionStatusChangedAction,
  DB_ACTIONS,
  DbAction,
  getTablesMetadata,
  GetTablesMetadataAction,
  postgresQuery,
  PostgresQueryResultAction,
  setTablesMetadata
} from './db.actions';
import { getConnection, getDatabasesState } from './db.selectors';
import { ConnectionStatus } from './db.state';

const connectionStatusChanged$ = (action$: ActionsObservable<DbAction>) => action$
  .ofType<ConnectionStatusChangedAction>(DB_ACTIONS.CONNECTION_STATUS_CHANGED)
  .pipe(
    switchMap(action => {
      if (action.error) {
        return of(showSnackbar(action.error, 'Error'));
      }
      switch (action.status) {
        case ConnectionStatus.CONNECTED:
          return concat(
            of(showSnackbar('Successfully connected to the database.')),
            of(getTablesMetadata(action.connectionId))
          );
        case ConnectionStatus.DISCONNECTED:
          return of(showSnackbar('Disconnected from the database.'));
        case ConnectionStatus.CONNECTING:
          return of(showSnackbar('Connecting to the database'));
        default:
          return EMPTY;
      }
    })
  );

const getTablesMetadata$ = (action$: ActionsObservable<DbAction>, state$: StateObservable<AppState>) => action$
  .ofType<GetTablesMetadataAction>(DB_ACTIONS.GET_TABLES_METADATA)
  .pipe(
    switchMap(originalAction => concat(
      of(postgresQuery(
        originalAction.connectionId,
        'items',
        'SELECT * FROM pg_catalog.pg_tables;'
      )),
      action$
        .ofType<PostgresQueryResultAction>(DB_ACTIONS.QUERY_RESULT)
        .pipe(
          filter(action => action.connectionId === originalAction.connectionId),
          take(1),
          map(action => {
            const connection = select(state$.value, getDatabasesState, getConnection(action.connectionId));
            return setTablesMetadata(
              connection.clientId,
              action.result.rows
                .map((row: any) => ({
                  name: row.tablename,
                  schema: row.schemaname,
                  fields: [],
                }))
                .filter(row => row.schema !== 'pg_catalog' && row.schema !== 'information_schema')
            );
          })
        )
    ))
  );

export const appDbEpics = combineEpics(
  connectionStatusChanged$,
  getTablesMetadata$
);
