import uuid from 'uuid/v4';
import { createAction } from '../../utils/redux.util';
import {
  ConnectionStatus,
  DatabaseMetadata,
  DatabaseState,
  PostgresClientConfiguration,
  PostgresResponse
} from './db.state';

export enum DB_ACTIONS {
  SET_DATABASE = 'DB/SET_DATABASE',
  REMOVE_DATABASE = 'DB/REMOVE_DATABASE',
  CONNECT = 'DB/CONNECT',
  CONNECTION_STATUS_CHANGED = 'DB/CONNECTION_STATUS_CHANGED',
  RECONNECT = 'DB/RECONNECT',
  DISCONNECT = 'DB/DISCONNECT',
  QUERY = 'DB/QUERY',
  SET_QUERY = 'DB/SET_QUERY',
  CLOSE_QUERY = 'DB/CLOSE_QUERY',
  QUERY_RESULT = 'DB/QUERY_RESULT',
  GET_METADATA = 'DB/GET_METADATA',
  SET_METADATA = 'DB/SET_METADATA',
  INSTALL_FUZZY_EXTENSION = 'DB/INSTALL_FUZZY_EXTENSION',
  FATAL_ERROR = 'DB/FATAL_ERROR',
}

// DB/SET_DATABASE
export type SetDatabaseAction = ReturnType<typeof setDatabase>;
export const setDatabase = (database: DatabaseState) =>
  createAction(DB_ACTIONS.SET_DATABASE, { database });

// DB/REMOVE_DATABASE
export type RemoveDatabaseAction = ReturnType<typeof removeDatabase>;
export const removeDatabase = (databaseId: string) =>
  createAction(DB_ACTIONS.REMOVE_DATABASE, { databaseId });

// DB/CONNECT
export type ConnectAction = ReturnType<typeof connectToPostgres>;
export const connectToPostgres = (configuration: PostgresClientConfiguration) =>
  createAction(DB_ACTIONS.CONNECT, { connectionId: uuid(), configuration });

// DB/CONNECTION_STATUS_CHANGED
export type ConnectionStatusChangedAction = ReturnType<typeof connectionStatusChanged>;
export const connectionStatusChanged = (
  databaseId: string,
  connectionId: string,
  status: ConnectionStatus,
  error?: string
) =>
  createAction(DB_ACTIONS.CONNECTION_STATUS_CHANGED, { databaseId, connectionId, status, error });

// DB/DISCONNECT
export type DisconnectFromPostgresAction = ReturnType<typeof disconnectFromPostgres>;
export const disconnectFromPostgres = (connectionId: string) =>
  createAction(DB_ACTIONS.DISCONNECT, { connectionId });

// DB/RECONNECT
export type ReconnectToPostgresAction = ReturnType<typeof reconnectToPostgres>;
export const reconnectToPostgres = (connectionId: string) =>
  createAction(DB_ACTIONS.RECONNECT, { connectionId });

// DB/SET_QUERY
export type SetQueryAction = ReturnType<typeof setQuery>;
export const setQuery = (connectionId: string, queryId: string, query: string, isSystemQuery?: boolean) =>
  createAction(DB_ACTIONS.SET_QUERY, { connectionId, queryId, query, isSystemQuery });

// DB/CLOSE_QUERY
export type CloseQueryAction = ReturnType<typeof closeQuery>;
export const closeQuery = (connectionId: string, queryId: string) =>
  createAction(DB_ACTIONS.CLOSE_QUERY, { connectionId, queryId });

// DB/QUERY
export type PostgresQueryAction = ReturnType<typeof postgresQuery>;
export const postgresQuery = (connectionId: string, queryId: string, query: string, isSystemQuery?: boolean) =>
  createAction(DB_ACTIONS.QUERY, { connectionId, queryId, query, isSystemQuery });

// DB/QUERY_RESULT
export type PostgresQueryResultAction = ReturnType<typeof postgresQueryResult>;
export const postgresQueryResult = (connectionId: string, queryId: string, result: PostgresResponse, error?: string) =>
  createAction(DB_ACTIONS.QUERY_RESULT, { connectionId, queryId, result, error });

// DB/GET_METADATA
export type GetMetadataAction = ReturnType<typeof getMetadata>;
export const getMetadata = (connectionId: string) =>
  createAction(DB_ACTIONS.GET_METADATA, { connectionId });

// DB/SET_METADATA
export type SetMetadataAction = ReturnType<typeof setMetadata>;
export const setMetadata = (payload: { databaseId: string } & DatabaseMetadata) =>
  createAction(DB_ACTIONS.SET_METADATA, payload);

// DB/INSTALL_FUZZY_EXTENSION
export enum InstallationStage {
  CREATE_EXTENSION,
  EXTRACT_FILES,
  RECREATE_EXTENSION,
}

export type InstallFuzzyExtensionAction = ReturnType<typeof installFuzzyExtension>;
export const installFuzzyExtension = (connectionId: string, stage: InstallationStage, databaseId?: string) =>
  createAction(DB_ACTIONS.INSTALL_FUZZY_EXTENSION, { connectionId, stage, databaseId });

export type FatalErrorAction = ReturnType<typeof fatalError>;
export const fatalError = (error: Error) =>
  createAction(DB_ACTIONS.FATAL_ERROR, {
    name: error.name,
    message: error.message,
    stack: error.stack,
  });

export type DbAction =
  | SetDatabaseAction
  | RemoveDatabaseAction
  | ConnectAction
  | ReconnectToPostgresAction
  | ConnectionStatusChangedAction
  | DisconnectFromPostgresAction
  | PostgresQueryAction
  | SetQueryAction
  | CloseQueryAction
  | PostgresQueryResultAction
  | GetMetadataAction
  | SetMetadataAction
  | InstallFuzzyExtensionAction
  | FatalErrorAction;
