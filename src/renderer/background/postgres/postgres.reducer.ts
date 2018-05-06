import { Reducer } from 'redux';
import { PostgresAction } from './postgres.actions';
import { PostgresState } from './postgres.store';

export const postgresReducer: Reducer<PostgresState, PostgresAction> = (
  store: void | PostgresState
) => {
  if (!store) {
    store = {};
  }
  return store;
};
