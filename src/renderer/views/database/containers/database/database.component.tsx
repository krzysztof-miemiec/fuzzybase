import React from 'react';
import { connect } from 'react-redux';
import { Route, RouteComponentProps } from 'react-router';
import uuid from 'uuid/v4';
import {
  connectToPostgres,
  DatabaseQueryState,
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
  removeDatabase,
  setQuery
} from '../../../../../common/db/store/app';
import { setDatabase } from '../../../../../common/db/store/db.actions';
import { PATHS } from '../../../../app.paths';
import { AppState } from '../../../../store';
import { mapActions } from '../../../../utils/redux.util';
import { select } from '../../../../utils/selector.util';
import { Query } from '../../../query/containers/query.component';
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
  postgresQuery,
  setQuery,
  removeDatabase,
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

  onCreateQuery = () => {
    const { actions, history, connection } = this.props;
    const queryId = uuid();
    actions.setQuery(connection.connectionId, queryId, '');
    history.replace(PATHS.QUERY(connection.clientId, connection.connectionId, queryId));
  };

  onShowQuery = (query: DatabaseQueryState) => {
    const { history, connection } = this.props;
    history.replace(PATHS.QUERY(connection.clientId, connection.connectionId, query.id));
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
    const { database, tables, connection } = this.props;
    const { isModified } = this.state;
    console.log(connection);

    return database && !isModified ? (
      connection ? (
        <div className={styles.container}>
          <div className={styles.sidebar}>
            <DatabaseTitle database={database} />
            <div className={styles.sidebarContent}>
              <DatabaseQueries
                queries={Object.values(connection.queries)}
                onAdd={this.onCreateQuery}
                onQueryClick={this.onShowQuery}
              />
              <DatabaseTables
                tables={tables}
                onAdd={this.onAddTable}
                onTableClick={this.onTableClick}
              />
            </div>
          </div>
          <div className={styles.toolbar} />
          <div className={styles.content}>
            <Route path={PATHS.QUERY(':databaseId', ':connectionId', ':queryId')} component={Query} />
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
