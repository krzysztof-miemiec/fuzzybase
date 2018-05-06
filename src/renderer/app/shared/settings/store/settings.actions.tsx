import { DatabaseState } from './settings.state';

export enum SETTINGS_ACTIONS {
  ADD_DATABASE = '[Settings] ADD_DATABASE',
  UPDATE_DATABASE = '[Settings] UPDATE_DATABASE',
  REMOVE_DATABASE = '[Settings] REMOVE_DATABASE',
}

// ADD_DATABASE
export type AddDatabase = {
  type: SETTINGS_ACTIONS.ADD_DATABASE;
  database: DatabaseState;
};

export const addDatabase = (database: DatabaseState): AddDatabase => ({
  type: SETTINGS_ACTIONS.ADD_DATABASE,
  database,
});

// UPDATE_DATABASE
export type UpdateDatabase = {
  type: SETTINGS_ACTIONS.UPDATE_DATABASE;
  databaseId: string;
  database: DatabaseState;
};

export const updateDatabase = (databaseId: string, database: DatabaseState): UpdateDatabase => ({
  type: SETTINGS_ACTIONS.UPDATE_DATABASE,
  databaseId,
  database,
});

// REMOVE_DATABASE
export type RemoveDatabase = {
  type: SETTINGS_ACTIONS.REMOVE_DATABASE;
  databaseId: string;
};

export const removeDatabase = (databaseId: string): RemoveDatabase => ({
  type: SETTINGS_ACTIONS.REMOVE_DATABASE,
  databaseId,
});

export type SettingsAction =
  | AddDatabase
  | UpdateDatabase
  | RemoveDatabase;
