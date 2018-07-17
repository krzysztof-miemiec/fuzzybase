import { createBrowserHistory } from 'history';
import { routerMiddleware, routerReducer } from 'react-router-redux';
import { applyMiddleware, combineReducers, createStore } from 'redux';
import { composeWithDevTools } from 'redux-devtools-extension';
import { combineEpics, createEpicMiddleware } from 'redux-observable';
import { persistStore } from 'redux-persist';
import * as databases from '../common/db/store/app';
import { appDbEpics } from '../common/db/store/app.db.epics';
import { reducer as dbReducer } from '../common/db/store/db.reducer';
import { AppState, AppStore } from './store';
import { IPCManager } from './utils/ipc.util';
import * as layout from './views/layout/store';
import { layoutEpics } from './views/layout/store/layout.epics';

// TODO Remove the hack for Redux 4 Devtools
// tslint:disable:no-var-requires
const reduxModule = require('redux');
reduxModule.__DO_NOT_USE__ActionTypes.INIT = '@@redux/INIT';
reduxModule.__DO_NOT_USE__ActionTypes.REPLACE = '@@redux/REPLACE';

function configureStore() {

  const epics = combineEpics<any>(
    appDbEpics,
    layoutEpics,
    IPCManager.sendActionEpic
  );

  const rootReducer = combineReducers<AppState>({
    db: dbReducer,
    layout: layout.reducer,
    router: routerReducer,
  });

  const initialState: AppState = {
    db: databases.initialState,
    layout: layout.initialState,
    router: { location: null },
  };

  const history = createBrowserHistory();
  const epicMiddleware = createEpicMiddleware();

  const store: AppStore = createStore(rootReducer, initialState, composeWithDevTools(
    applyMiddleware(
      routerMiddleware(history),
      epicMiddleware
    )
  ));
  const persistor = persistStore(store);
  epicMiddleware.run(epics);

  return { store, history, persistor };
}

export const { store, history, persistor } = configureStore();
