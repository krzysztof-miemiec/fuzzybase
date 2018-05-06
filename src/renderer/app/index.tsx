import React from 'react';
import { render } from 'react-dom';
import { App } from './app.component';
import { history, store } from './app.store';

const app = document.getElementById('app');
document.body.style.margin = '0';
render(<App store={store} history={history} />, app);
