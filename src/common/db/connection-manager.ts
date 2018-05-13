import { store } from '../../main/main.store';
import { PostgresConnection } from './postgres.connection';
import { PostgresClientConfiguration } from './store/app';

export module ConnectionManager {
  const connections: Record<string, PostgresConnection> = {};

  export const connect = (connectionId: string, config: PostgresClientConfiguration): PostgresConnection => {
    const client: PostgresConnection = connections[connectionId] = new PostgresConnection(
      connectionId, config, store.dispatch
    );
    client.connect();
    return client;
  };

  export const getConnection = (key: string): PostgresConnection => {
    return connections[key];
  };

  export const disconnect = (key: string): void => {
    const connection = getConnection(key);
    if (connection) {
      connection.disconnect();
      delete connections[key];
    }
  };
}
