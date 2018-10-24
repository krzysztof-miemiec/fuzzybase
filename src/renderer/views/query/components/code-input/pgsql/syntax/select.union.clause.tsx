import { Context, Match, matchRegExp, PostgresSyntax, PostgresSyntaxType } from '../postgres-syntax';

export class SelectUnionClause extends PostgresSyntax {
  constructor(type: PostgresSyntaxType, match: Match, context: Context) {
    super(type, match, context);
  }
}

export const SelectUnionClauseType: PostgresSyntaxType = {
  syntaxClass: SelectUnionClause,
  name: 'UNION',
  matcher: matchRegExp(/UNION/),
};
