import React from 'react';
import { Route, Switch, withRouter } from 'react-router';
import { PATHS } from './app.paths';
import { Database } from './views/database';
import { Layout } from './views/layout';

export const AppNavigation = withRouter(() => (
  <Layout>
    <Switch>
      <Route path={PATHS.DATABASE(':databaseId')} component={Database} />
    </Switch>
  </Layout>
));
