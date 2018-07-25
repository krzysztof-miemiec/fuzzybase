import { AppState } from '../../../renderer/store';
import { DatabaseConnectionState, DatabaseMetadata, DatabaseState, DbState } from './db.state';

export const getDatabasesState = (state: AppState) => state.db;

export const getDatabaseList = (state: DbState) => state.databases;

export const getConnectionList = (state: DbState) => state.connections;

export const getConnection = (id: string) => (state: DbState) => state.connections[id];

export const getDatabase = (id: string) => (state: DbState) =>
  state.databases.find(db => db.id === id);

export const getDatabaseIndex = (id: string) => (state: DbState) =>
  state.databases.findIndex(db => db.id === id);

export const getDatabaseMetadata = (state: DatabaseState) => state.meta;

export const getTables = (state: Partial<DatabaseMetadata>) => state.tables;

export const getFirstDatabaseConnection = (databaseId: string) => (state: DbState) =>
  Object.values(state.connections)
    .find(connection => connection.clientId === databaseId);

export const getDatabaseConnections =  (databaseId: string) => (state: DbState) =>
  Object.values(state.connections)
    .filter(connection => connection.clientId === databaseId);

export const getStatus = (state: DatabaseConnectionState) => state.status;

export const getQuery = (id: string) => (state: DatabaseConnectionState) => state.queries[id];
