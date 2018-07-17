import { applyMiddleware, compose, createStore, Reducer } from 'redux';
import { combineEpics, createEpicMiddleware } from 'redux-observable';
import { mainDbEpics } from '../common/db/store/main.db.epics';
import { sendAction$ } from '../common/ipc';

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
      epicMiddleware
    )
  ));
  epicMiddleware.run(epics);
  return store;
};

export const store = configureStore();
