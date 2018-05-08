import { RouterState } from 'react-router-redux';
import { Store } from 'redux';
import { LayoutState } from '../scenes/layout/store';
import { SettingsState } from '../shared/settings/store';

export interface AppState {
  settings: SettingsState;
  layout: LayoutState;
  router: RouterState;
}

export type AppStore = Store<AppState>;
