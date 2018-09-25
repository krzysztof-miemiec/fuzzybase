import { FieldDef } from 'pg';
import uuid from 'uuid/v4';
import { DatabaseState } from './db.state';

export const createDatabaseState = (): DatabaseState => ({
  id: uuid(),
  name: '',
  database: '',
  host: '',
  port: 5432,
  meta: {},
});

export const getDatabaseUrl = (db: DatabaseState): string =>
  db.username ? `${db.username}@` : '' + db.host + ':' + db.port;

export const findFieldByName = (fields: FieldDef[]) => (name: string) => {
  const fieldIndex = fields.findIndex(row => row.name === name);
  return (row: any[]) => fieldIndex >= 0
    ? row[fieldIndex]
    : undefined;
};
