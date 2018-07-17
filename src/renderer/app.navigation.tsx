import React from 'react';
import { Route, Switch, withRouter } from 'react-router';
import { PATHS } from './app.paths';
import { Connection } from './views/connection/containers/connection.component';
import { Database } from './views/database';
import { Layout } from './views/layout';

export const AppNavigation = withRouter(() => (
  <Layout>
    <Switch>
      <Route exact={true} path={PATHS.DATABASE(':id')} component={Database} />
      <Route exact={true} path={PATHS.CONNECTION(':id')} component={Connection} />
    </Switch>
  </Layout>
));
