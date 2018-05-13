import React from 'react';
import { connect } from 'react-redux';
import { RouteComponentProps } from 'react-router';
import { getDatabase, getDatabasesState } from '../../../../common/db/store/app';
import { setDatabase } from '../../../../common/db/store/db.actions';
import { createDatabaseState } from '../../../../common/db/store/db.utils';
import { AppState } from '../../../store';
import { mapActions } from '../../../utils/redux.util';
import { select } from '../../../utils/selector.util';
import { DatabaseForm } from '../components/database-form.component';

type ComponentProps = RouteComponentProps<{ id: string }>;

const mapStateToProps = (state: AppState, ownProps: ComponentProps) => ({
  database: select(state, getDatabasesState, getDatabase(ownProps.match.params.id)) || createDatabaseState(),
});

const mapDispatchToProps = mapActions({
  setDatabase,
});

type Props = typeof mapDispatchToProps & ReturnType<typeof mapStateToProps> & ComponentProps;

const DatabaseComponent: React.SFC<Props> = ({
  database, actions, history,
}) => (
  <DatabaseForm
    database={database}
    onSubmit={database => {
      actions.setDatabase(database);
      history.goBack();
    }}
  />
);

export const Database = connect(mapStateToProps, mapDispatchToProps)(DatabaseComponent);
