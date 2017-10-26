import * as React from 'react';
import { Route, Switch } from 'react-router';
import { App } from './containers/App';
import { MainPage } from './containers/Main';

export const Routes = () => (
  <App>
    <Switch>
      <Route path='/' component={MainPage}/>
    </Switch>
  </App>
);
