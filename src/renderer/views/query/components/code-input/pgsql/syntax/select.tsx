import { Context, Match, matchRegExp, PostgresSyntax, PostgresSyntaxType } from '../postgres-syntax';
import { ConditionExpression } from './condition';
import { ExpressionElement } from './expression';
import { AllClause } from './select.all';
import { DistinctClause } from './select.distinct';
import { FromClause } from './select.from';

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
  // groupBy?: GroupByClause[];
  having?: ConditionExpression[];
  // window?: WindowExpression[];
  union?: SelectClause;
  intersect?: SelectClause;
  except?: SelectClause;

  constructor(type: PostgresSyntaxType, match: Match, context: Context) {
    super(type, match, context);
  }
}

export const SelectQueryType: PostgresSyntaxType = {
  syntaxClass: SelectClause,
  matcher: matchRegExp(/^SELECT/),
  name: 'SELECT',
};
