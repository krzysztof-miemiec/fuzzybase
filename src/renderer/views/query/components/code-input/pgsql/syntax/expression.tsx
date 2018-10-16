import { Context, PostgresSyntax, PostgresSyntaxType } from '../postgres-syntax';

export class ExpressionElement extends PostgresSyntax {

  constructor(_: RegExpExecArray, context: Context) {
    super(context);
  }
}

export const ExpressionQueryType: PostgresSyntaxType = {
  build: (match: RegExpExecArray, context: Context) => new ExpressionElement(match, context),
  matcher: /^/,
  name: 'expression',
  priority: 3,
};
