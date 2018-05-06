import { Store } from 'redux';
import { SettingsState } from '../shared/settings/store';

export interface AppState {
  settings: SettingsState;
}

export type AppStore = Store<AppState>;
