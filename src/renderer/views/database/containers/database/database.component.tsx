import { withStyles } from '@material-ui/core';
import React from 'react';
import { connect } from 'react-redux';
import { RouteComponentProps } from 'react-router';
import {
  connectToPostgres,
  DatabaseState,
  DatabaseTable,
  getConnection,
  getDatabase,
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
import { DatabaseConnect } from '../../components/database-connect';
import { DatabaseForm } from '../../components/database-form';
import { DatabaseTables } from '../../components/database-tables';
import { DatabaseTitle } from '../../components/database-title';
import { styles } from './database.styles';

type RouteProps = RouteComponentProps<{
  id?: string;
}>;

const mapStateToProps = (state: AppState, ownProps: RouteProps) => {
  const { id } = ownProps.match.params;
  const database = select(state, getDatabasesState, getDatabase(id));
  const connection = select(state, getDatabasesState, getFirstDatabaseConnection(id));

  return {
    database,
    connection,
    tablesQuery: connection && select(
      state, getDatabasesState, getConnection(connection.connectionId), getQuery('tables')
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
    const { actions } = this.props;
    if (database.name && database.database && database.host) {
      this.setState({ isModified: false });
      actions.setDatabase(database);
    }
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
    const { actions, database } = this.props;
    actions.removeDatabase(database.id);
  };

  onConnect = () => {
    const { actions, database } = this.props;
    actions.connectToPostgres(database);
  };

  onCancel = () => {
    this.props.history.replace(PATHS.HOME);
  };

  render() {
    const { database, tables, connection, classes } = this.props;
    const { isModified } = this.state;

    return database && !isModified ? (
      connection ? (
        <div className={classes.container}>
          <div className={classes.sidebar}>
            <DatabaseTitle database={database} />
            <DatabaseTables
              tables={tables}
              onAdd={this.onAddTable}
              onTableClick={this.onTableClick}
            />
          </div>
          <div className={classes.column}>
            <div className={classes.toolbar} />
            <div className={classes.content} />
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
