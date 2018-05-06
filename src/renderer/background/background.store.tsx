import { applyMiddleware, combineReducers, compose, createStore } from 'redux';
import { combineEpics, createEpicMiddleware } from 'redux-observable';
import { actionsEpics } from './actions/actions.epics';
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
  actionsEpics
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
