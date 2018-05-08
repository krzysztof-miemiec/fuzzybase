import { AppState } from '../../../store';
import { DatabaseState, SettingsState } from './settings.state';

export const getSettingsState = (state: AppState) => state.settings;

export const getDatabaseList = (state: SettingsState) => state.databases;

export const getDatabase = (id: string) => (state: SettingsState): DatabaseState =>
  state.databases.find(db => db.id === id);
