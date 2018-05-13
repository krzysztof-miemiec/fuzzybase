import React from 'react';
import { Provider } from 'react-redux';
import { ConnectedRouter } from 'react-router-redux';
import { PersistGate } from 'redux-persist/integration/react';
import { AppNavigation } from './app.navigation';
import { history, persistor, store } from './app.store';
import { IPCManager } from './utils/ipc.util';

export class App extends React.Component {

  componentDidMount() {
    IPCManager.subscribe();
  }

  componentWillUnmount() {
    IPCManager.unsubscribe();
  }

  render() {
    return (
      <Provider store={store}>
        <PersistGate loading={null} persistor={persistor}>
          <ConnectedRouter history={history}>
            <AppNavigation />
          </ConnectedRouter>
        </PersistGate>
      </Provider>
    );
  }
}
