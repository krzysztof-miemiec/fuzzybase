import {  Persist } from '../../../utils/persist.util';

export interface DatabaseState {
  id?: string;
  name: string;
  uri: string;
  username?: string;
  password?: string;
}

export interface SettingsState {
  databases: DatabaseState[];
  _persist?: Persist;
}

export const initialState: SettingsState = {
  databases: [],
};
