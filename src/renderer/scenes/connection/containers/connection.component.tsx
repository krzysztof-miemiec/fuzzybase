import React from 'react';
import { connect } from 'react-redux';
import { RouteComponentProps } from 'react-router';
import { getConnection, getDatabasesState } from '../../../../common/db/store/db.selectors';
import { AppState } from '../../../store';
import { select } from '../../../utils/selector.util';

type RouteProps = RouteComponentProps<{ id: string }>;

const mapStateToProps = (state: AppState, ownProps: RouteProps) => ({
  connection: select(state, getDatabasesState, getConnection(ownProps.match.params.id)),
});

type Props = ReturnType<typeof mapStateToProps> & RouteProps;

const ConnectionComponent: React.SFC<Props> = ({
  connection,
}) => (
  <div>
    {JSON.stringify(connection)}
  </div>
);

export const Connection = connect(mapStateToProps)(
  ConnectionComponent
);
