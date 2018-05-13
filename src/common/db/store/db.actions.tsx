import uuid from 'uuid/v4';
import { createAction } from '../../../renderer/utils/redux.util';
import { ConnectionStatus, DatabaseState, PostgresClientConfiguration } from './db.state';

export enum DB_ACTIONS {
  SET_DATABASE = 'DB/SET_DATABASE',
  REMOVE_DATABASE = 'DB/REMOVE_DATABASE',
  CONNECT = 'DB/CONNECT',
  CONNECTION_STATUS_CHANGED = 'DB/CONNECTION_STATUS_CHANGED',
  DISCONNECT = 'DB/DISCONNECT',
  QUERY = 'DB/QUERY',
  QUERY_RESULT = 'DB/QUERY_RESULT',
}

// ADD_DATABASE
export type SetDatabaseAction = ReturnType<typeof setDatabase>;
export const setDatabase = (database: DatabaseState) =>
  createAction(DB_ACTIONS.SET_DATABASE, { database });

// REMOVE_DATABASE
export type RemoveDatabaseAction = ReturnType<typeof removeDatabase>;
export const removeDatabase = (databaseId: string) =>
  createAction(DB_ACTIONS.REMOVE_DATABASE, { databaseId });

export type ConnectAction = ReturnType<typeof connectToPostgres>;
export const connectToPostgres = (configuration: PostgresClientConfiguration) =>
  createAction(DB_ACTIONS.CONNECT, { connectionId: uuid(), configuration });

export type ConnectionStatusChangedAction = ReturnType<typeof connectionStatusChanged>;
export const connectionStatusChanged = (
  clientId: string,
  connectionId: string,
  status: ConnectionStatus,
  error?: string
) =>
  createAction(DB_ACTIONS.CONNECTION_STATUS_CHANGED, { clientId, connectionId, status, error });

export type DisconnectFromPostgresAction = ReturnType<typeof disconnectFromPostgres>;
export const disconnectFromPostgres = (connectionId: string) =>
  createAction(DB_ACTIONS.DISCONNECT, { connectionId });

export type PostgresQueryAction = ReturnType<typeof postgresQuery>;
export const postgresQuery = (connectionId: string, queryId: string, query: string) =>
  createAction(DB_ACTIONS.QUERY, { connectionId, queryId, query });

export type PostgresQueryResultAction = ReturnType<typeof postgresQueryResult>;
export const postgresQueryResult = (connectionId: string, queryId: string, result: any) =>
  createAction(DB_ACTIONS.QUERY_RESULT, { connectionId, queryId, result });

export type DbAction =
  | SetDatabaseAction
  | RemoveDatabaseAction
  | ConnectAction
  | ConnectionStatusChangedAction
  | DisconnectFromPostgresAction
  | PostgresQueryAction
  | PostgresQueryResultAction;
