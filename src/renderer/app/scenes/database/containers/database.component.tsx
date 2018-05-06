import React from 'react';
import { connect } from 'react-redux';
import { RouteComponentProps } from 'react-router';
import { getDatabase, getSettingsState } from '../../../shared/settings/store';
import { setDatabase } from '../../../shared/settings/store/settings.actions';
import { AppState } from '../../../store';
import { mapActions } from '../../../utils/redux.util';
import { select } from '../../../utils/selector.util';
import { DatabaseForm } from '../components/database-form.component';

type ComponentProps = RouteComponentProps<{ id: string }>;

const mapStateToProps = (state: AppState, ownProps: ComponentProps) => ({
  database: select(state, getSettingsState, getDatabase(ownProps.match.params.id)),
});

const mapDispatchToProps = mapActions({
  setDatabase,
});

type Props = typeof mapDispatchToProps & ReturnType<typeof mapStateToProps> & ComponentProps;

const DatabaseComponent: React.SFC<Props> = ({
  database, actions,
}) => (
  <DatabaseForm database={database} onSubmit={actions.setDatabase} />
);

export const Database = connect(mapStateToProps, mapDispatchToProps)(DatabaseComponent);
