import { createBrowserHistory } from 'history';
import { routerMiddleware, routerReducer } from 'react-router-redux';
import { applyMiddleware, combineReducers, createStore } from 'redux';
import { composeWithDevTools } from 'redux-devtools-extension';
import { combineEpics, createEpicMiddleware } from 'redux-observable';
import { persistStore } from 'redux-persist';
import * as layout from './scenes/layout/store';
import * as settings from './shared/settings/store';
import { settingsEpics } from './shared/settings/store/settings.epics';
import { AppStore } from './store';
import { IPCManager } from './utils/ipc.util';
import sendActionEpic = IPCManager.sendActionEpic;

// TODO Remove the hack for Redux 4 Devtools
// tslint:disable:no-var-requires
const reduxModule = require('redux');
reduxModule.__DO_NOT_USE__ActionTypes.INIT = '@@redux/INIT';
reduxModule.__DO_NOT_USE__ActionTypes.REPLACE = '@@redux/REPLACE';

function configureStore() {

  const epics = combineEpics(
    settingsEpics,
    sendActionEpic
  );

  const rootReducer = combineReducers({
    settings: settings.reducer,
    layout: layout.reducer,
    router: routerReducer,
  });

  const initialState = {
    settings: settings.initialState,
    layout: layout.initialState,
    router: {},
  };

  const history = createBrowserHistory();

  const store: AppStore = createStore(rootReducer, initialState, composeWithDevTools(
    applyMiddleware(
      routerMiddleware(history),
      createEpicMiddleware(epics)
    )
  ));
  const persistor = persistStore(store);

  return { store, history, persistor };
}

export const { store, history, persistor } = configureStore();
