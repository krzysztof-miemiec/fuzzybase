import { Persist } from '../../../renderer/utils/persist.util';

export enum ConnectionStatus {
  CONNECTED = 'CONNECTED',
  CONNECTING = 'CONNECTING',
  DISCONNECTED = 'DISCONNECTED',
}

export interface DatabaseQueryState {
  id: string;
  query: string;
  start: number;
  end: number;
  result?: PostgresResponse;
  error?: Error;
}

export interface DatabaseConnectionState {
  clientId: string;
  connectionId: string;
  status: ConnectionStatus;
  error?: string;
  queries: Record<string, DatabaseQueryState>;
}

export interface PostgresClientConfiguration {
  id: string;
  user?: string;
  database?: string;
  password?: string;
  port?: number;
  host?: string;
  connectionString?: string;
}

export interface DatabaseState {
  id: string;
  name: string;
  host: string;
  port: number;
  username?: string;
  password?: string;
}

export interface PostgresResponse {
  command: string;
  rowCount: number;
  oid: any;
  rows: object[];
}

export interface DbState {
  databases: DatabaseState[];
  connections: Record<string, DatabaseConnectionState>;
  _persist?: Persist;
}

export const initialState: DbState = {
  databases: [],
  connections: {},
};
