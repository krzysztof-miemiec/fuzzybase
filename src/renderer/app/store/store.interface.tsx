import { Store } from 'redux';
import { LayoutState } from '../scenes/layout/store';
import { SettingsState } from '../shared/settings/store';

export interface AppState {
  settings: SettingsState;
  layout: LayoutState;
}

export type AppStore = Store<AppState>;
