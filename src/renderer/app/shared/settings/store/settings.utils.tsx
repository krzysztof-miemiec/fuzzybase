import uuid from 'uuid/v4';
import { DatabaseState } from './settings.state';

export const createDatabaseState = (): DatabaseState => ({
  id: uuid(),
  name: '',
  host: '',
  port: 5432,
});

export const getDatabaseUrl = (db: DatabaseState): string =>
  db.username ? `${db.username}@` : ''
+ db.host + ':' + db.port;
