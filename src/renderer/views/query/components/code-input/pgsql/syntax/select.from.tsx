import { Context, Match, matchRegExp, PostgresSyntax, PostgresSyntaxType } from '../postgres-syntax';

export class FromClause extends PostgresSyntax {
  constructor(type: PostgresSyntaxType, match: Match, context: Context) {
    super(type, match, context);
    const { elements } = match.matches;
  }
}

export const FromClauseType: PostgresSyntaxType = {
  syntaxClass: FromClause,
  matcher: matchRegExp(/^FROM\s+(.+)\s+/i, match => ({ elements: match[1] })),
  name: 'FROM',
};
