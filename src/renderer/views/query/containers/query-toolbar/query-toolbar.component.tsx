import { IconButton, Tooltip } from '@material-ui/core';
import Send from '@material-ui/icons/Send';
import React from 'react';
import { connect } from 'react-redux';
import { RouteComponentProps } from 'react-router';
import { postgresQuery } from '../../../../../common/db/store/db.actions';
import { getConnection, getDatabasesState, getQuery } from '../../../../../common/db/store/db.selectors';
import { AppState } from '../../../../store';
import { mapActions } from '../../../../utils/redux.util';
import { select } from '../../../../utils/selector.util';

type RouteProps = RouteComponentProps<{ connectionId: string, queryId: string }>;

const mapStateToProps = (state: AppState, ownProps: RouteProps) => {
  const { connectionId, queryId } = ownProps.match.params;
  const connection = select(state, getDatabasesState, getConnection(connectionId));
  const query = select(connection, getQuery(queryId));
  return {
    connection,
    query,
  };
};

const mapDispatchToProps = mapActions({
  postgresQuery,
});

type Props = ReturnType<typeof mapStateToProps> & typeof mapDispatchToProps;

class QueryToolbarComponent extends React.Component<Props> {
  executeQuery = () => {
    const { actions, connection, query } = this.props;
    actions.postgresQuery(connection.connectionId, query.id, query.query);
  };

  render() {
    return (
      <>
        <Tooltip title="Execute query">
        <IconButton onClick={this.executeQuery}>
          <Send color="inherit" fontSize="inherit" />
        </IconButton>
        </Tooltip>
      </>
    );
  }
}

export const QueryToolbar = connect(mapStateToProps, mapDispatchToProps)(QueryToolbarComponent);
