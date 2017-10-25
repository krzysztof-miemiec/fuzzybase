import * as React from 'react';
import { render } from 'react-dom';
import { AppContainer } from 'react-hot-loader';
import { Root } from './containers/Root';
import './styles/main.scss';
import { configureStore, history } from './store';
const store = configureStore();

render(
  <AppContainer>
    <Root store={store} history={history}/>
  </AppContainer>,
  document.getElementById('root')
);

if ((module as any).hot) {
  (module as any).hot.accept('./containers/Root', () => {
    const NextRoot = require('./containers/Root').Root;
    render(
      <AppContainer>
        <NextRoot store={store} history={history}/>
      </AppContainer>,
      document.body
    );
  });
}
