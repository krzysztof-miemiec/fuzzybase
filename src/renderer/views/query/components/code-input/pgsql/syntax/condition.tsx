import { matchRegExp, PostgresSyntax, PostgresSyntaxType } from '../postgres-syntax';

export class ConditionExpression extends PostgresSyntax {

}

export const ConditionExpressionType:PostgresSyntaxType = {
  syntaxClass: ConditionExpression,
  matcher: matchRegExp(/^(.+)/i),
  name: 'condition',
};
