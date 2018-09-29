import { MuiThemeProvider } from '@material-ui/core';
import React from 'react';
import JssProvider from 'react-jss/lib/JssProvider';
import { Provider } from 'react-redux';
import { ConnectedRouter } from 'react-router-redux';
import { PersistGate } from 'redux-persist/integration/react';
import { AppNavigation } from './app.navigation';
import { history, persistor, store } from './app.store';
import { generateClassName, JSS, materialUiTheme } from './app.styles';
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
      <MuiThemeProvider theme={materialUiTheme}>
      <Provider store={store}>
        <PersistGate loading={null} persistor={persistor}>
          <ConnectedRouter history={history}>
            <JssProvider jss={JSS} generateClassName={generateClassName}>
              <AppNavigation />
            </JssProvider>
          </ConnectedRouter>
        </PersistGate>
      </Provider>
      </MuiThemeProvider>
    );
  }
}
