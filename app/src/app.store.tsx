import { createBrowserHistory } from 'history';
import { routerMiddleware } from 'react-router-redux';
import { applyMiddleware, combineReducers, createStore } from 'redux';
import createSagaMiddleware from 'redux-saga';

const rootReducer = combineReducers({

});

export const history = createBrowserHistory();
const router = routerMiddleware(history);
const sagaMiddleware = createSagaMiddleware();

interface AppState {
  walkthrough: object;
}

const initialState: AppState = {
  walkthrough: {},
};

export function configureStore() {
  const enhancer = process.env.NODE_ENV !== 'production'
    ? applyMiddleware(sagaMiddleware, router, require('logger').logger)
    : applyMiddleware(sagaMiddleware, router);
  return createStore(rootReducer, initialState, enhancer);
}

export const store = configureStore();
