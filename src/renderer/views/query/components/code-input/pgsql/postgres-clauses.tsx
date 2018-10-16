import { Clause, parseClause } from './clause-parser';

const clauses: Clause[] = [
  parseClause(`SELECT [expression] FROM [from_items] WHERE `),
];
