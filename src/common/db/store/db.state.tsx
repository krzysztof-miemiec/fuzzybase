import { FieldDef } from 'pg';
import { PersistedState } from 'redux-persist/es/types';

export enum ConnectionStatus {
  CONNECTED = 'CONNECTED',
  CONNECTING = 'CONNECTING',
  DISCONNECTED = 'DISCONNECTED',
}

export interface DatabaseQueryState {
  id: string;
  isSystemQuery: boolean;
  query: string;
  start: number;
  end: number;
  ipcTime?: number;
  result?: PostgresResponse;
  error?: string;
}

export interface DatabaseConnectionState {
  databaseId: string;
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

export interface FuzzyFunction {
  name: string;
  range: [number, number, number, number];
}

export interface FuzzyType {
  name: string;
  functions: FuzzyFunction[];
}

export interface ExtensionInstallation {
  status: 'progress' | 'success' | 'error';
  message?: string;
}

export interface DatabaseMetadata {
  tables?: { [key: string]: Table };
  searchPath?: string[];
  user?: string;
  hasFuzzyExtension?: boolean;
  fuzzyTypes?: Record<string, FuzzyType>;
  extensionInstallation?: ExtensionInstallation | null;
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
