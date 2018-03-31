import * as React from 'react';
import { render } from 'react-dom';
import { App } from './app.component';
import { configureStore, history } from './app.store';

const store = configureStore();

render(<App store={store} history={history} /> as any, document.getElementById('root'));
