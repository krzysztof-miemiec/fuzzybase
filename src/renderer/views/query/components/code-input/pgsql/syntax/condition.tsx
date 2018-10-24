import { Context, Match, matchRegExp, PostgresSyntax, PostgresSyntaxType } from '../postgres-syntax';

export class ConditionExpression extends PostgresSyntax {
  constructor(type: PostgresSyntaxType, match: Match, context: Context) {
    super(type, match, context);
  }
}

export const ConditionExpressionType: PostgresSyntaxType = {
  syntaxClass: ConditionExpression,
  matcher: matchRegExp(/^(.+)/i),
  name: 'condition',
};
