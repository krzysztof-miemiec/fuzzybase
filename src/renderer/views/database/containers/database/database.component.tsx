import { Toolbar } from '@material-ui/core';
import React from 'react';
import { connect } from 'react-redux';
import { Route, RouteComponentProps, Switch } from 'react-router';
import {
  closeQuery,
  connectToPostgres,
  DatabaseState,
  disconnectFromPostgres,
  getConnection,
  getDatabase,
  getDatabaseConnections,
  getDatabaseList,
  getDatabaseMetadata,
  getDatabasesState,
  getFirstDatabaseConnection, getMetadata,
  getQuery,
  getTables,
  postgresQuery,
  removeDatabase,
  setQuery,
  Table
} from '../../../../../common/db/store/app';
import { setDatabase } from '../../../../../common/db/store/db.actions';
import { mapActions } from '../../../../../common/utils/redux.util';
import { select } from '../../../../../common/utils/selector.util';
import { PATHS } from '../../../../app.paths';
import { AppState } from '../../../../store';
import { Query } from '../../../query/containers/query';
import { QueryToolbar } from '../../../query/containers/query-toolbar';
import { DatabaseConnect } from '../../components/database-connect';
import { DatabaseForm } from '../../components/database-form';
import { DatabaseQueries } from '../../components/database-queries';
import { DatabaseTables } from '../../components/database-tables';
import { DatabaseTitle } from '../../components/database-title';
import { styles } from './database.styles';

type RouteProps = RouteComponentProps<{
  databaseId?: string;
  connectionId?: string;
}>;

const mapStateToProps = (state: AppState, ownProps: RouteProps) => {
  const { databaseId } = ownProps.match.params;
  const database = select(state, getDatabasesState, getDatabase(databaseId));
  const connection = select(state, getDatabasesState, getFirstDatabaseConnection(databaseId));

  return {
    database,
    databases: select(state, getDatabasesState, getDatabaseList),
    metadata: select(database, getDatabaseMetadata),
    queries: select(state, getDatabasesState, getDatabaseConnections(databaseId)),
    connection,
    tablesQuery: connection && select(
      state, getDatabasesState, getConnection(connection.connectionId), getQuery('items')
    ),
    tables: select(database, getDatabaseMetadata, getTables),
  };
};

const mapDispatchToProps = mapActions({
  setDatabase,
  connectToPostgres,
  disconnectFromPostgres,
  postgresQuery,
  setQuery,
  closeQuery,
  removeDatabase,
  getMetadata,
});

type Props =
  ReturnType<typeof mapStateToProps>
  & typeof mapDispatchToProps
  & RouteProps;

interface State {
  isModified?: boolean;
}

class DatabaseComponent extends React.PureComponent<Props, State> {
  state: State = {};

  onSubmit = (database: DatabaseState) => {
    const { actions, history } = this.props;
    if (database.name && database.database && database.host) {
      this.setState({ isModified: false });
      actions.setDatabase(database);
      history.replace(PATHS.DATABASE(database.id));
    }
  };

  navigateToQuery = (queryId: string) => {
    const { history, connection } = this.props;
    history.replace(PATHS.QUERY(connection.databaseId, connection.connectionId, queryId));
  };

  onTableClick = (_: Table) => {
    // TODO navigate to table view
  };

  onModify = () => {
    this.setState({ isModified: true });
  };

  onRemove = () => {
    const { actions, history, database, databases } = this.props;
    actions.removeDatabase(database.id);
    history.replace(PATHS.DATABASE(databases[0] && databases[0].id));
  };

  onConnect = () => {
    const { actions, database } = this.props;
    actions.connectToPostgres(database);
  };

  onDisconnect = () => {
    const { actions, connection } = this.props;
    actions.disconnectFromPostgres(connection.connectionId);
  };

  onCancel = () => {
    this.props.history.replace(PATHS.HOME);
  };

  render() {
    const { database, tables, connection, metadata } = this.props;
    const { isModified } = this.state;

    return database && !isModified ? (
      connection ? (
        <div className={styles.container}>
          <div className={styles.sidebar}>
            <DatabaseTitle
              database={database}
              connectionId={connection.connectionId}
              user={metadata.user}
              onCloseConnection={this.onDisconnect}
            />
            <div className={styles.sidebarContent}>
              <DatabaseQueries
                navigateToQuery={this.navigateToQuery}
                connection={connection}
              />
              <DatabaseTables
                tables={tables}
                onTableClick={this.onTableClick}
              />
            </div>
          </div>
          <Toolbar className={styles.toolbar}>
            <Switch>
              <Route path={PATHS.QUERY()} component={QueryToolbar} />
            </Switch>
          </Toolbar>
          <div className={styles.content}>
            <Switch>
              <Route path={PATHS.QUERY()} component={Query} />
            </Switch>
          </div>
        </div>
      ) : (
        <DatabaseConnect
          database={database}
          onConnect={this.onConnect}
          onModify={this.onModify}
          onRemove={this.onRemove}
        />
      )
    ) : (
      <DatabaseForm
        database={database}
        onSubmit={this.onSubmit}
        onCancel={this.onCancel}
      />
    );
  }
}

export const Database = connect(mapStateToProps, mapDispatchToProps)(DatabaseComponent);
