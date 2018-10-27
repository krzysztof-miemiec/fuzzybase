import { Client } from 'pg';
import { Dispatch } from 'redux';
import { connectionStatusChanged, postgresQueryResult } from './store/db.actions';
import { ConnectionStatus, PostgresClientConfiguration } from './store/main';

export class PostgresConnection {
  clientId: string;
  client: Client;
  private isConnected: boolean = false;

  constructor(
    public connectionId: string,
    { id, ...config }: PostgresClientConfiguration,
    private dispatch: Dispatch<any>
  ) {
    this.clientId = id;
    this.client = new Client(config);
    this.client.on('end', this.onDisconnected);
    this.client.on('error', this.onError);
  }

  onError = (error: Error) => {
    this.isConnected = false;
    this.dispatch(connectionStatusChanged(
      this.clientId,
      this.connectionId,
      ConnectionStatus.DISCONNECTED,
      error.message
    ));
  };

  onConnected = () => {
    this.isConnected = true;
    this.dispatch(connectionStatusChanged(this.clientId, this.connectionId, ConnectionStatus.CONNECTED));
  };

  onDisconnected = (error?: Error) => {
    if (!this.isConnected) {
      return;
    }
    this.isConnected = false;
    this.dispatch(connectionStatusChanged(
      this.clientId,
      this.connectionId,
      ConnectionStatus.DISCONNECTED,
      error && error.message
    ));
  };

  reconnect = () => {
    this.client.end()
      .then(() => this.isConnected = false)
      .then(() => this.client.connect())
      .then(() => this.isConnected = true)
      .catch(this.onError);
  };

  connect = () => {
    this.dispatch(connectionStatusChanged(this.clientId, this.connectionId, ConnectionStatus.CONNECTING));
    this.client.connect()
      .then(this.onConnected)
      .catch(() => {
        // Connection error is handled in ondisconnected
      });
  };

  disconnect = () => {
    if (this.isConnected) {
      this.client.end();
    }
  };

  query = (id: string, queryString: string) => {
    if (!this.isConnected) {
      throw new Error('Client is not connected to database.');
    }
    return this.client.query({
      text: queryString,
      rowMode: 'array',
    }).then(result => {
      this.dispatch(postgresQueryResult(
        this.connectionId, id, Array.isArray(result) ? result[result.length - 1] : result
      ));
    }).catch(error => {
      this.dispatch(postgresQueryResult(this.connectionId, id, undefined, error.message));
    });
  };
}
