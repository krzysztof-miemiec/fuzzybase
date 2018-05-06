import { ActionsObservable, combineEpics } from 'redux-observable';
import { ignoreElements, tap } from 'rxjs/operators';
import {
  ConnectToPostgresAction, DisconnectFromPostgresAction,
  POSTGRES_ACTION,
  PostgresAction, PostgresQueryAction, RemovePostgresConfigurationAction,
  SetPostgresConfigurationAction,
  SetPostgresConfigurationsAction
} from './postgres.actions';
import { PostgresClientManager } from './postgres.client-manager';

const setConfigs$ = (action$: ActionsObservable<PostgresAction>) => action$
  .ofType<SetPostgresConfigurationsAction>(POSTGRES_ACTION.SET_CONFIGURATIONS)
  .pipe(
    tap(action => PostgresClientManager.setClients(action.configs)),
    ignoreElements()
  );

const setConfig$ = (action$: ActionsObservable<PostgresAction>) => action$
  .ofType<SetPostgresConfigurationAction>(POSTGRES_ACTION.SET_CONFIGURATION)
  .pipe(
    tap(action => PostgresClientManager.setClient(action.config)),
    ignoreElements()
  );

const removeConfig$ = (action$: ActionsObservable<PostgresAction>) => action$
  .ofType<RemovePostgresConfigurationAction>(POSTGRES_ACTION.REMOVE_CONFIGURATION)
  .pipe(
    tap(action => PostgresClientManager.removeClient(action.id)),
    ignoreElements()
  );

const connect$ = (action$: ActionsObservable<PostgresAction>) => action$
  .ofType<ConnectToPostgresAction>(POSTGRES_ACTION.CONNECT)
  .pipe(
    tap(action => PostgresClientManager.getClient(action.clientId).connect()),
    ignoreElements()
  );

const disconnect$ = (action$: ActionsObservable<PostgresAction>) => action$
  .ofType<DisconnectFromPostgresAction>(POSTGRES_ACTION.DISCONNECT)
  .pipe(
    tap(action => PostgresClientManager.getClient(action.clientId).disconnect()),
    ignoreElements()
  );

const query$ = (action$: ActionsObservable<PostgresAction>) => action$
  .ofType<PostgresQueryAction>(POSTGRES_ACTION.QUERY)
  .pipe(
    tap(action => PostgresClientManager.getClient(action.clientId)
      .query(action.query)
    ),
    ignoreElements()
  );

export const postgresEpics = combineEpics(
  setConfigs$,
  setConfig$,
  removeConfig$,
  connect$,
  disconnect$,
  query$
);
