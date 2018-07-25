import React from 'react';
import { DatabaseTable } from '../../../../../common/db/store/app';
import { SidebarSection } from '../sidebar-section';

interface Props {
  tables: DatabaseTable[];
  onAdd: () => void;
  onTableClick: (table: DatabaseTable) => void;
}

export const DatabaseTables: React.SFC<Props> = ({
  tables, onAdd, onTableClick,
}) => (
  <SidebarSection
    title="Tables"
    mapItem={(item: DatabaseTable) => item}
    items={tables}
    onAdd={onAdd}
    onItemClick={(item: any) => onTableClick(item)}
  />
);
