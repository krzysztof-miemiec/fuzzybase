import 'electron-log';

import { webFrame } from 'electron';
import React from 'react';
import ReactDOM from 'react-dom';
import { AppContainer } from 'react-hot-loader';
import { Config } from '../common/config';
import { App } from './app.component';
import './main.scss';

(window as any).ELECTRON_DISABLE_SECURITY_WARNINGS = Config.IS_DEV;

webFrame.setVisualZoomLevelLimits(1, 1);
webFrame.setLayoutZoomLevelLimits(1, 1);

const render = Component => {
  ReactDOM.render(
    <AppContainer>
      <Component />
    </AppContainer>,
    document.getElementById('app')
  );
};

render(App);

// Webpack Hot Module Replacement API
if ((module as any).hot) {
  (module as any).hot.accept('./app.component', () => {
    const NextApp = require('./app.component').App;
    render(NextApp);
  });
}
