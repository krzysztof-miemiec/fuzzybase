import { RouterState } from 'react-router-redux';
import { Store } from 'redux';
import { DbState } from '../../common/db/store/app';
import { LayoutState } from '../views/layout/store';

export interface AppState {
  db: DbState;
  layout: LayoutState;
  router: RouterState;
}

export type AppStore = Store<AppState>;
