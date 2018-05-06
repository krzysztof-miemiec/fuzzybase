import { createBrowserHistory } from 'history';
import { routerMiddleware } from 'react-router-redux';
import { applyMiddleware, combineReducers, createStore } from 'redux';
import * as layout from './scenes/layout/store';
import * as settings from './shared/settings/store';
import { AppStore } from './store';

function configureStore() {
  const rootReducer = combineReducers({
    settings: settings.reducer,
    layout: layout.reducer,
  });

  const initialState = {
    settings: settings.initialState,
    layout: layout.initialState,
  };

  const history = createBrowserHistory();
  const router = routerMiddleware(history);

  const enhancer = process.env.NODE_ENV !== 'production'
    ? applyMiddleware(router)
    : applyMiddleware(router);
  const store: AppStore = createStore(rootReducer, initialState, enhancer);

  return { store, history };
}

export const { store, history } = configureStore();
