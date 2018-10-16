import { Context, PostgresSyntax, PostgresSyntaxType } from '../postgres-syntax';
import { ExpressionElement } from './expression';
import { AllClause } from './select.all';
import { DistinctClause } from './select.distinct';
import { FromClause } from './select.from';
import { ConditionExpression } from './condition';

/**
 * SELECT [ ALL | DISTINCT [ ON ( expression [, ...] ) ] ]
 *   [ * | expression [ [ AS ] output_name ] [, ...] ]
 *   [ FROM from_item [, ...] ]
 *   [ WHERE condition ]
 *   [ GROUP BY grouping_element [, ...] ]
 *   [ HAVING condition [, ...] ]
 *   [ WINDOW window_name AS ( window_definition ) [, ...] ]
 *   [ { UNION | INTERSECT | EXCEPT } [ ALL | DISTINCT ] select ]
 *   [ ORDER BY expression [ ASC | DESC | USING operator ] [ NULLS { FIRST | LAST } ] [, ...] ]
 *   [ LIMIT { count | ALL } ]
 *   [ OFFSET start [ ROW | ROWS ] ]
 *   [ FETCH { FIRST | NEXT } [ count ] { ROW | ROWS } ONLY ]
 *   [ FOR { UPDATE | NO KEY UPDATE | SHARE | KEY SHARE } [ OF table_name [, ...] ] [ NOWAIT | SKIP LOCKED ] [...] ]
 */

export class SelectClause extends PostgresSyntax {
  all?: AllClause;
  distinct?: DistinctClause;
  select: ExpressionElement[];
  from?: FromClause[];
  where?: ConditionExpression[];
  groupBy?: GroupingElement[];
  having?: ConditionElement[];
  window?: WindowElement[];
  union?: SelectClause;
  intersect?: SelectClause;
  except?: SelectClause;

  constructor(match: RegExpExecArray, context: Context) {
    super(context);
    this.parse(match.)
  }
}

export const SelectQueryType: PostgresSyntaxType = {
  build: (match: RegExpExecArray, context: Context) => new SelectClause(match, context),
  matcher: /^SELECT (?<D>.+) (FROM)/,
  name: 'SELECT',
  priority: 0,
};
