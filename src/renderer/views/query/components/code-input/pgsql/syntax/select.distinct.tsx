import { Context, Match, matchRegExp, PostgresSyntax, PostgresSyntaxType } from '../postgres-syntax';
import { ExpressionElement } from './expression';

export class DistinctClause extends PostgresSyntax {
  on?: ExpressionElement[];

  constructor(type: PostgresSyntaxType, match: Match, context: Context) {
    super(type, match, context);
  }
}

export const DistinctType: PostgresSyntaxType = {
  syntaxClass: DistinctClause,
  matcher: matchRegExp(/^DISTINCT(?:\s+ON .+)/i),
  name: 'DISTINCT',
};
