import { PostgresClient } from './postgres.client';
import { PostgresClientConfiguration } from './postgres.interface';

export module PostgresClientManager {
  const clients: Record<string, PostgresClient> = {};

  export const setClients = (configs: PostgresClientConfiguration[]): void => {
    Object.keys(clients)
      .forEach(removeClient);
    configs
      .map(config => new PostgresClient(config))
      .forEach(client => {
        clients[client.id] = client;
      });
  };

  export const setClient = (config: PostgresClientConfiguration): PostgresClient => {
    return clients[config.id] = new PostgresClient(config);
  };

  export const getClient = (key: string): PostgresClient => {
    return clients[key];
  };

  export const removeClient = (key: string): void => {
    const client = clients[key];
    if (client) {
      client.disconnect();
      delete clients[key];
    }
  };
}
