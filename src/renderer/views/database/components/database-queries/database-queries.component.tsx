import React from 'react';
import { connect } from 'react-redux';
import uuid from 'uuid/v4';
import { closeQuery, DatabaseConnectionState, DatabaseQueryState, setQuery } from '../../../../../common/db/store/app';
import { mapActions } from '../../../../utils/redux.util';
import { SidebarSection } from '../sidebar-section';

interface ComponentProps {
  connection: DatabaseConnectionState;
  navigateToQuery: (queryId: string) => void;
}

const mapDispatchToProps = mapActions({
  setQuery,
  closeQuery,
});

type Props =
  & ComponentProps
  & typeof mapDispatchToProps;

export class DatabaseQueriesComponent extends React.PureComponent<Props> {

  onAddClick = () => {
    const { actions, connection, navigateToQuery } = this.props;
    const queryId = uuid();
    actions.setQuery(connection.connectionId, queryId, '');
    navigateToQuery(queryId);
  };

  onCloseClick = (query: DatabaseQueryState) => {
    const { actions, connection } = this.props;
    actions.closeQuery(connection.connectionId, query.id);
  };

  onClick = (query: DatabaseQueryState) => this.props.navigateToQuery(query.id);

  render() {
    const { connection } = this.props;
    return (
      <SidebarSection
        title="Queries"
        hint="Empty query"
        addTooltipDescription="Create new query"
        mapItem={(query: DatabaseQueryState) => ({ id: query.id, name: query.query })}
        items={Object.values(connection.queries)}
        onAddClick={this.onAddClick}
        onItemClick={this.onClick}
        onCloseItemClick={this.onCloseClick}
      />
    );
  }
}

export const DatabaseQueries = connect(null, mapDispatchToProps)(DatabaseQueriesComponent);
