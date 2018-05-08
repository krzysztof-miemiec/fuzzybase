import { applyMiddleware, combineReducers, compose, createStore } from 'redux';
import { combineEpics, createEpicMiddleware } from 'redux-observable';
import { CommunicationActionType } from '../../common/actions';
import { IPCManager } from '../app/utils/ipc.util';
import { sendAction$ } from './ipc';
import { postgresEpics } from './postgres/postgres.epics';
import { postgresReducer } from './postgres/postgres.reducer';

// REDUCERS
const reducer = combineReducers({
  postgresReducer,
});

// EPICS
// ------------------------------------
const epics = combineEpics(
  postgresEpics,
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
setInterval(
  () => IPCManager.send({
    type: CommunicationActionType.STATE_REFLECTION,
    state: store.getState(),
  }),
  3000
);
