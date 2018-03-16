import * as React from 'react';
import { render } from 'react-dom';
import { AppContainer } from 'react-hot-loader';
import { App } from './app.component';
import { configureStore, history } from './app.store';
const store = configureStore();

render(
  <AppContainer>
    <App store={store} history={history}/>
  </AppContainer>,
  document.getElementById('root')
);

if ((module as any).hot) {
  (module as any).hot.accept('./app.component', () => {
    const NextRoot = require('./app.component').Root;
    render(
      <AppContainer>
        <NextRoot store={store} history={history}/>
      </AppContainer>,
      document.body
    );
  });
}
