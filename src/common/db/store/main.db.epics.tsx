import { ActionsObservable, combineEpics } from 'redux-observable';
import { ignoreElements, tap } from 'rxjs/operators';
import { ConnectionManager } from '../connection-manager';
import {
  ConnectAction,
  DB_ACTIONS,
  DbAction,
  DisconnectFromPostgresAction,
  PostgresQueryAction,
} from './db.actions';

const connect$ = (action$: ActionsObservable<DbAction>) => action$
  .ofType<ConnectAction>(DB_ACTIONS.CONNECT)
  .pipe(
    tap(action => ConnectionManager.connect(action.connectionId, action.configuration)),
    ignoreElements()
  );

const disconnect$ = (action$: ActionsObservable<DbAction>) => action$
  .ofType<DisconnectFromPostgresAction>(DB_ACTIONS.DISCONNECT)
  .pipe(
    tap(action => ConnectionManager.disconnect(action.connectionId)),
    ignoreElements()
  );

const query$ = (action$: ActionsObservable<DbAction>) => action$
  .ofType<PostgresQueryAction>(DB_ACTIONS.QUERY)
  .pipe(
    tap(action => ConnectionManager.getConnection(action.connectionId).query(action.queryId, action.query)),
    ignoreElements()
  );

export const mainDbEpics = combineEpics(
  connect$,
  disconnect$,
  query$
);
