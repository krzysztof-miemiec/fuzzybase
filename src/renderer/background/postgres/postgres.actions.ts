import { PostgresClientConfiguration } from './postgres.interface';

export enum POSTGRES_ACTION {
  SET_CONFIGURATIONS = 'POSTGRES/SET_CONFIGURATIONS',
  SET_CONFIGURATION = 'POSTGRES/SET_CONFIGURATION',
  REMOVE_CONFIGURATION = 'POSTGRES/REMOVE_CONFIGURATION',
  CONNECT = 'POSTGRES/CONNECT',
  DISCONNECT = 'POSTGRES/DISCONNECT',
  QUERY = 'POSTGRES/QUERY',
}

export interface SetPostgresConfigurationsAction {
  type: POSTGRES_ACTION.SET_CONFIGURATIONS;
  configs: PostgresClientConfiguration[];
}

export const setPostgresConfigurations = (
  configs: PostgresClientConfiguration[]
): SetPostgresConfigurationsAction => ({
  type: POSTGRES_ACTION.SET_CONFIGURATIONS,
  configs,
});

export interface SetPostgresConfigurationAction {
  type: POSTGRES_ACTION.SET_CONFIGURATION;
  config: PostgresClientConfiguration;
}

export const setPostgresConfiguration = (
  config: PostgresClientConfiguration
): SetPostgresConfigurationAction => ({
  type: POSTGRES_ACTION.SET_CONFIGURATION,
  config,
});

export interface RemovePostgresConfigurationAction {
  type: POSTGRES_ACTION.REMOVE_CONFIGURATION;
  id: string;
}

export const removePostgresConfiguration = (
  id: string
): RemovePostgresConfigurationAction => ({
  type: POSTGRES_ACTION.REMOVE_CONFIGURATION,
  id,
});

export interface ConnectToPostgresAction {
  type: POSTGRES_ACTION.CONNECT;
  clientId: string;
}

export const connectToPostgres = (clientId: string): ConnectToPostgresAction => ({
  type: POSTGRES_ACTION.CONNECT,
  clientId,
});

export interface DisconnectFromPostgresAction {
  type: POSTGRES_ACTION.DISCONNECT;
  clientId: string;

}

export const disconnectFromPostgres = (clientId: string): DisconnectFromPostgresAction => ({
  type: POSTGRES_ACTION.DISCONNECT,
  clientId,
});

export interface PostgresQueryAction {
  type: POSTGRES_ACTION.QUERY;
  clientId: string;
  query: string;
}

export const postgresQuery = (clientId: string, query: string): PostgresQueryAction => ({
  type: POSTGRES_ACTION.QUERY,
  clientId,
  query,
});

export type PostgresAction =
  | SetPostgresConfigurationsAction
  | SetPostgresConfigurationAction
  | RemovePostgresConfigurationAction
  | ConnectToPostgresAction
  | DisconnectFromPostgresAction
  | PostgresQueryAction;
