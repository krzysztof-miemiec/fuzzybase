import { withStyles } from '@material-ui/core';
import React from 'react';
import { connect } from 'react-redux';
import { Route, RouteComponentProps } from 'react-router';
import {
  connectToPostgres,
  DatabaseConnectionState,
  DatabaseState,
  DatabaseTable,
  getConnection,
  getDatabase,
  getDatabaseConnections,
  getDatabaseList,
  getDatabaseMetadata,
  getDatabasesState,
  getFirstDatabaseConnection,
  getQuery,
  getTables,
  postgresQuery,
  removeDatabase
} from '../../../../../common/db/store/app';
import { setDatabase } from '../../../../../common/db/store/db.actions';
import { PATHS } from '../../../../app.paths';
import { AppState } from '../../../../store';
import { mapActions } from '../../../../utils/redux.util';
import { select } from '../../../../utils/selector.util';
import { StyleProps } from '../../../../utils/styles.util';
import { Connection } from '../../../connection/containers/connection.component';
import { DatabaseConnect } from '../../components/database-connect';
import { DatabaseConnections } from '../../components/database-connections';
import { DatabaseForm } from '../../components/database-form';
import { DatabaseTables } from '../../components/database-tables';
import { DatabaseTitle } from '../../components/database-title';
import { styles } from './database.styles';

type RouteProps = RouteComponentProps<{
  databaseId?: string;
}>;

const mapStateToProps = (state: AppState, ownProps: RouteProps) => {
  console.log(ownProps);
  const { databaseId } = ownProps.match.params;
  const database = select(state, getDatabasesState, getDatabase(databaseId));
  const connection = select(state, getDatabasesState, getFirstDatabaseConnection(databaseId));

  return {
    database,
    databases: select(state, getDatabasesState, getDatabaseList),
    connections: select(state, getDatabasesState, getDatabaseConnections(databaseId)),
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
  postgresQuery,
  removeDatabase,
});

type Props = ReturnType<typeof mapStateToProps> & typeof mapDispatchToProps & RouteProps;

interface State {
  isModified?: boolean;
}

class DatabaseComponent extends React.PureComponent<Props & StyleProps<typeof styles>, State> {
  state: State = {};

  onSubmit = (database: DatabaseState) => {
    const { actions, history } = this.props;
    if (database.name && database.database && database.host) {
      this.setState({ isModified: false });
      actions.setDatabase(database);
      history.replace(PATHS.DATABASE(database.id));
    }
  };

  onCreateConnection = () => {
    // TODO create new connection
  };

  onShowConnection = (connection: DatabaseConnectionState) => {
    const { history } = this.props;
    console.log(connection);
    history.replace(PATHS.CONNECTION(connection.clientId, connection.connectionId));
  };

  onAddTable = () => {
    // TODO navigate to new table view
  };

  onTableClick = (_: DatabaseTable) => {
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

  onCancel = () => {
    this.props.history.replace(PATHS.HOME);
  };

  render() {
    const { database, tables, connection, connections, classes } = this.props;
    const { isModified } = this.state;

    return database && !isModified ? (
      connection ? (
        <div className={classes.container}>
          <div className={classes.sidebar}>
            <DatabaseTitle database={database} />
            <div className={classes.sidebarContent}>
              <DatabaseConnections
                connections={connections}
                onAdd={this.onCreateConnection}
                onConnectionClick={this.onShowConnection}
              />
              <DatabaseTables
                tables={tables}
                onAdd={this.onAddTable}
                onTableClick={this.onTableClick}
              />
            </div>
          </div>
          <div className={classes.toolbar} />
          <div className={classes.content}>
            <Route path={PATHS.CONNECTION(':databaseId', ':connectionId')} component={Connection} />
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

export const Database = connect(mapStateToProps, mapDispatchToProps)(
  withStyles(styles)(DatabaseComponent)
);
