import React from 'react';
import ReactDOM from 'react-dom';
import { AppContainer } from 'react-hot-loader';
import { App } from './app.component';

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
  (module as any).hot.accept('./app.component', () => render(App));
}
