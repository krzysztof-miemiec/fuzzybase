import React from 'react';
import { DatabaseConnectionState } from '../../../../../common/db/store/app';
import { SidebarSection } from '../sidebar-section';

interface Props {
  connections: DatabaseConnectionState[];
  onAdd: () => void;
  onConnectionClick: (connection: DatabaseConnectionState) => void;
}

export const DatabaseConnections: React.SFC<Props> = ({
  connections, onAdd, onConnectionClick,
}) => (
  <SidebarSection
    title="Connections"
    mapItem={(connection: DatabaseConnectionState) => ({ name: connection.connectionId })}
    items={connections}
    onAdd={onAdd}
    onItemClick={(item: any) => onConnectionClick(item)}
  />
);
