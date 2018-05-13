import { applyMiddleware, compose, createStore, Reducer } from 'redux';
import { combineEpics, createEpicMiddleware } from 'redux-observable';
import { mainDbEpics } from '../common/db/store/main.db.epics';
import { sendAction$ } from '../common/ipc';

// REDUCERS
const reducer: Reducer = (state) => state || {};

// EPICS
// ------------------------------------
const epics = combineEpics(
  mainDbEpics,
  sendAction$
);

// CONFIG
// ------------------------------------
const configureStore = () => {
  return createStore(reducer, compose(
    applyMiddleware(
      createEpicMiddleware(epics)
    )
  ));
};

export const store = configureStore();
