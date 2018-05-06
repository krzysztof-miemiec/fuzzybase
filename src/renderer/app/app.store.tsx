import { createBrowserHistory } from 'history';
import { routerMiddleware } from 'react-router-redux';
import { applyMiddleware, combineReducers, createStore } from 'redux';
import * as settings from './shared/settings/store';
import { AppStore } from './store';

const rootReducer = combineReducers({
  settings: settings.reducer,
});

const initialState = {
  settings: settings.initialState,
};

function configureStore() {

  const history = createBrowserHistory();
  const router = routerMiddleware(history);

  const enhancer = process.env.NODE_ENV !== 'production'
    ? applyMiddleware(router)
    : applyMiddleware(router);
  const store: AppStore = createStore(rootReducer, initialState, enhancer);

  return { store, history };
}

export const { store, history } = configureStore();
