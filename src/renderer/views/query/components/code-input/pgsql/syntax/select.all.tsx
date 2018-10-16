import { Context, Match, matchRegExp, PostgresSyntax, PostgresSyntaxType } from '../postgres-syntax';

export class AllClause extends PostgresSyntax {
  constructor(type: PostgresSyntaxType, match: Match, context: Context) {
    super(type, match, context);
  }
}

export const AllClauseType: PostgresSyntaxType = {
  syntaxClass: AllClause,
  matcher: matchRegExp(/^ALL\s*/i),
  name: 'ALL',
};
