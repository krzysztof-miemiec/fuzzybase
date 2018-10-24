import { Context, Match, matchRegExp, PostgresSyntax, PostgresSyntaxType } from '../postgres-syntax';

export class ExpressionElement extends PostgresSyntax {
  constructor(type: PostgresSyntaxType, match: Match, context: Context) {
    super(type, match, context);
  }
}

export const ExpressionQueryType: PostgresSyntaxType = {
  syntaxClass: ExpressionElement,
  matcher: matchRegExp(/^/),
  name: 'expression',
};
