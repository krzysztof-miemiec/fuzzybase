export interface PostgresClientConfiguration {
  id: string;
  isConnected?: boolean;
  user?: string;
  database?: string;
  password?: string;
  port?: number;
  host?: string;
  connectionString?: string;
}
