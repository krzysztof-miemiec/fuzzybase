import React from 'react';
import { Route, Switch } from 'react-router';
import { PATHS } from './app.paths';
import { Database } from './scenes/database';
import { DatabaseList } from './scenes/database-list';
import { QuickStart } from './scenes/quick-start';

export const AppNavigation = () => (
  <Switch>
    <Route exact={true} path={PATHS.DATABASES} component={DatabaseList} />
    <Route exact={true} path={PATHS.DATABASE(':id')} component={Database} />
    <Route component={QuickStart} />
  </Switch>
);
