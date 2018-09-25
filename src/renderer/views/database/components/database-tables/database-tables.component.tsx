import React from 'react';
import { Table } from '../../../../../common/db/store/app';
import { SidebarSection } from '../sidebar-section';

interface Props {
  tables?: { [key: string]: Table } | undefined;
  onTableClick: (table: Table) => void;
}

const displayableTableName = (table: Table) => table.schema === 'public'
  ? table.name
  : `${table.schema}.${table.name}`;

export const DatabaseTables: React.SFC<Props> = ({
  tables, onTableClick,
}) => (
  <SidebarSection
    title="Tables"
    mapItem={(item: Table) => ({ name: displayableTableName(item) })}
    items={tables ? Object.values(tables) : []}
    onItemClick={(item: any) => onTableClick(item)}
  />
);
