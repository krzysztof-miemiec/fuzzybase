import { ActionsObservable, combineEpics } from 'redux-observable';
import { of } from 'rxjs';
import { catchError, ignoreElements, switchMap, tap } from 'rxjs/operators';
import { ConnectionManager } from '../connection-manager';
import {
  ConnectAction,
  DB_ACTIONS,
  DbAction,
  DisconnectFromPostgresAction,
  fatalError,
  PostgresQueryAction, ReconnectToPostgresAction
} from './db.actions';
import { extractFuzzyExtension$ } from './db.extension.epics';

const errorHandler = (err) => of(fatalError(err));
const handleEventualErrors = result => result.type === DB_ACTIONS.FATAL_ERROR
  ? of(result)
  : of(result).pipe(ignoreElements());

const connect$ = (action$: ActionsObservable<DbAction>) => action$
  .ofType<ConnectAction>(DB_ACTIONS.CONNECT)
  .pipe(
    tap(action => ConnectionManager.connect(action.connectionId, action.configuration)),
    catchError(errorHandler),
    switchMap(handleEventualErrors)
  );

const disconnect$ = (action$: ActionsObservable<DbAction>) => action$
  .ofType<DisconnectFromPostgresAction>(DB_ACTIONS.DISCONNECT)
  .pipe(
    tap(action => ConnectionManager.disconnect(action.connectionId)),
    catchError(errorHandler),
    switchMap(handleEventualErrors)
  );

const reconnect$ = (action$: ActionsObservable<DbAction>) => action$
  .ofType<ReconnectToPostgresAction>(DB_ACTIONS.RECONNECT)
  .pipe(
    tap(action => ConnectionManager.reconnect(action.connectionId)),
    catchError(errorHandler),
    switchMap(handleEventualErrors)
  );

const query$ = (action$: ActionsObservable<DbAction>) => action$
  .ofType<PostgresQueryAction>(DB_ACTIONS.QUERY)
  .pipe(
    tap(action => ConnectionManager.getConnection(action.connectionId).query(action.queryId, action.query)),
    catchError(errorHandler),
    switchMap(handleEventualErrors)
  );

export const mainDbEpics = combineEpics(
  connect$,
  reconnect$,
  disconnect$,
  query$,
  extractFuzzyExtension$
);
