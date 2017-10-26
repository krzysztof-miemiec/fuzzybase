import { applyMiddleware, createStore } from 'redux';
import { createBrowserHistory } from 'history';
import { routerMiddleware } from 'react-router-redux';
import createSagaMiddleware from 'redux-saga';
import { rootReducer } from './reducers';

export const history = createBrowserHistory();
const router = routerMiddleware(history);
const sagaMiddleware = createSagaMiddleware();

interface AppState {
  walkthrough: object;
}

const initialState: AppState = {
  walkthrough: {}
};

export function configureStore() {
  const enhancer = process.env.NODE_ENV !== 'production'
    ? applyMiddleware(sagaMiddleware, router, require('logger').logger)
    : applyMiddleware(sagaMiddleware, router);
  const store = createStore(rootReducer, initialState, enhancer);
  if ((module as any).hot) {
    (module as any).hot.accept('./reducers', () =>
      store.replaceReducer(require('./reducers')) // eslint-disable-line global-require
    );
  }
  return store;
}

// sagaMiddleware.run(mySaga);
