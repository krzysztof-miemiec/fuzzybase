import { applyMiddleware, compose, createStore, Reducer } from 'redux';
import { createLogger } from 'redux-logger';
import { combineEpics, createEpicMiddleware } from 'redux-observable';
import { mainDbEpics } from '../common/db/store/main.db.epics';
import { sendAction$ } from '../common/ipc';

const DEBUG = true;

// REDUCERS
const reducer: Reducer = (state) => state || {};

// EPICS
// ------------------------------------
const epics = combineEpics<any>(
  mainDbEpics,
  sendAction$
);

// CONFIG
// ------------------------------------
const epicMiddleware = createEpicMiddleware();
const configureStore = () => {
  const store =  createStore(reducer, compose(
    applyMiddleware(
      epicMiddleware,
      DEBUG ? createLogger({
        // ...options
      }) : undefined
    )
  ));
  epicMiddleware.run(epics);
  return store;
};

export const store = configureStore();
