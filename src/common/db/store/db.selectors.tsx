import { AppState } from '../../../renderer/store';
import { DatabaseConnectionState, DbState } from './db.state';

export const getDatabasesState = (state: AppState) => state.db;

export const getDatabaseList = (state: DbState) => state.databases;

export const getDatabase = (id: string) => (state: DbState) =>
  state.databases.find(db => db.id === id);

export const getFirstDatabaseConnection = (databaseId: string) => (state: DbState) =>
  Object.values(state.connections)
    .find(connection => connection.clientId === databaseId);

export const getStatus = (state: DatabaseConnectionState) => state.status;
