import React from 'react';
import { DatabaseQueryState } from '../../../../../common/db/store/app';
import { SidebarSection } from '../sidebar-section';

interface Props {
  queries: DatabaseQueryState[];
  onAdd: () => void;
  onQueryClick: (connection: DatabaseQueryState) => void;
}

export const DatabaseQueries: React.SFC<Props> = ({
  queries, onAdd, onQueryClick,
}) => (
  <SidebarSection
    title="Queries"
    mapItem={(query: DatabaseQueryState) => ({ id: query.id, name: query.query })}
    items={queries}
    onAdd={onAdd}
    onItemClick={onQueryClick}
  />
);
