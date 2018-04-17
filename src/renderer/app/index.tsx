import React from 'react';
import { render } from 'react-dom';
import { App } from './app.component';
import { history, store } from './app.store';

render(<App store={store} history={history} />, document.getElementById('app'));
