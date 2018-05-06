import { Client } from 'pg';
import { PostgresClientConfiguration } from './postgres.interface';

export class PostgresClient {
  id: string;
  client: Client;
  isConnected: boolean = false;

  constructor({ id, isConnected, ...config }: PostgresClientConfiguration) {
    this.id = id;
    this.client = new Client(config);
    this.client.on('end', () => this.isConnected = false);
    if (isConnected) {
      this.connect();
    }
  }

  connect = () => {
    this.client.connect()
      .then(
        () => this.isConnected = true,
        () => this.isConnected = false
      );
  };

  disconnect = () => {
    this.client.end()
      .then(() => this.isConnected = false);
  };

  query = (queryString: string) => {
    if (!this.isConnected) {
      throw new Error('Client is not connected to database.');
    }
    return this.client.query(queryString);
  };
}
