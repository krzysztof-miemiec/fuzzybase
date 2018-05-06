import { History } from 'history';
import React, { Component } from 'react';
import { Provider } from 'react-redux';
import { ConnectedRouter } from 'react-router-redux';
import { Store } from 'redux';
import { Layout } from './scenes/layout';
import { IPCManager } from './utils/ipc.util';

interface Props {
  store: Store<any>;
  history: History;
}

export class App extends Component<Props> {

  componentDidMount() {
    IPCManager.subscribe();
  }

  componentWillUnmount() {
    IPCManager.unsubscribe();
  }

  render() {
    const { store, history } = this.props;
    return (
      <Provider store={store}>
        <ConnectedRouter history={history}>
          <Layout />
        </ConnectedRouter>
      </Provider>
    );
  }
}
