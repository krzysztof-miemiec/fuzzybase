import { combineReducers, Reducer } from 'redux';
import { routerReducer as routing } from 'react-router-redux';
import { counter, TState as TCounterState } from './counter';

export const rootReducer = combineReducers({
  counter,
  routing: routing as Reducer<any>
});

export interface IState {
  counter: TCounterState;
}
