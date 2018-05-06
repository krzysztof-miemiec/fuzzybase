import { DatabaseState } from './settings.state';

export enum SETTINGS_ACTIONS {
  SET_DATABASE = 'SETTINGS/SET_DATABASE',
  REMOVE_DATABASE = 'SETTINGS/REMOVE_DATABASE',
}

// ADD_DATABASE
export type SetDatabaseAction = {
  type: SETTINGS_ACTIONS.SET_DATABASE;
  database: DatabaseState;
};

export const setDatabase = (database: DatabaseState): SetDatabaseAction => ({
  type: SETTINGS_ACTIONS.SET_DATABASE,
  database,
});

// REMOVE_DATABASE
export type RemoveDatabaseAction = {
  type: SETTINGS_ACTIONS.REMOVE_DATABASE;
  databaseId: string;
};

export const removeDatabase = (databaseId: string): RemoveDatabaseAction => ({
  type: SETTINGS_ACTIONS.REMOVE_DATABASE,
  databaseId,
});

export type SettingsAction =
  | SetDatabaseAction
  | RemoveDatabaseAction;
