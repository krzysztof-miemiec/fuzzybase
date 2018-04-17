import { createBrowserHistory } from 'history';
import { routerMiddleware } from 'react-router-redux';
import { applyMiddleware, combineReducers, createStore } from 'redux';

const rootReducer = combineReducers({});

interface AppState {
  walkthrough: object;
}

const initialState: AppState = {
  walkthrough: {},
};

function configureStore() {

  const history = createBrowserHistory();
  const router = routerMiddleware(history);

  const enhancer = process.env.NODE_ENV !== 'production'
    ? applyMiddleware(router)
    : applyMiddleware(router);
  const store = createStore(rootReducer, initialState, enhancer);

  return { store, history };
}

export const { store, history } = configureStore();
