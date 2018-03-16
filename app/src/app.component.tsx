import { History } from 'history';
import * as React from 'react';
import * as Redux from 'react-redux';
import { Provider } from 'react-redux';
import { ConnectedRouter } from 'react-router-redux';
import { Layout } from './scenes/layout';

interface Props {
  store: Redux.Store<any>;
  history: History;
}

export const App: React.SFC<Props> = ({ store, history }) => (
  <Provider store={store}>
    <ConnectedRouter history={history}>
      <Layout />
    </ConnectedRouter>
  </Provider>
);
