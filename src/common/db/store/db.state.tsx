import { FieldDef } from 'pg';
import { PersistedState } from 'redux-persist/es/types';

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
  name?: string;
  user?: string;
  database?: string;
  password?: string;
  port?: number;
  host?: string;
  connectionString?: string;
}

export interface Column {
  index: number;
  name: string;
  'default': any;
  nullable: boolean;
  dataType: string;
}

export interface Table {
  name: string;
  schema: string;
  fields: Column[];
}

export interface DatabaseMetadata {
  tables: { [key: string]: Table };
  user: string;
}

export interface DatabaseState {
  id: string;
  name: string;
  host: string;
  port: number;
  database: string;
  username?: string;
  password?: string;
  meta: Partial<DatabaseMetadata>;
}

export interface PostgresResponse {
  command: string;
  rowCount: number;
  oid: any;
  fields: FieldDef[];
  rows: any[][];
}

export interface DbState extends PersistedState {
  databases: DatabaseState[];
  connections: Record<string, DatabaseConnectionState>;
}

export const initialState: DbState = {
  databases: [],
  connections: {},
};
