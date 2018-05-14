import React from 'react';
import { Route, Switch, withRouter } from 'react-router';
import { PATHS } from './app.paths';
import { Connection } from './scenes/connection/containers/connection.component';
import { Database } from './scenes/database';
import { DatabaseList } from './scenes/database-list';
import { Layout } from './scenes/layout';
import { QuickStart } from './scenes/quick-start';

export const AppNavigation = withRouter(() => (
  <Layout>
    <Switch>
      <Route exact={true} path={PATHS.DATABASES} component={DatabaseList} />
      <Route exact={true} path={PATHS.DATABASE(':id')} component={Database} />
      <Route exact={true} path={PATHS.CONNECTION(':id')} component={Connection} />
      <Route component={QuickStart} />
    </Switch>
  </Layout>
));
