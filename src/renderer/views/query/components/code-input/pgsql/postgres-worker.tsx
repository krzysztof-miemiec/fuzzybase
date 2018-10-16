import { Context } from './postgres-syntax';
import { SelectQueryType } from './syntax/select';

export class PostgresWorker {
  context: Context;

  constructor() {
    this.context = {
      types: [
        SelectQueryType,
      ],
    };
  }

}
