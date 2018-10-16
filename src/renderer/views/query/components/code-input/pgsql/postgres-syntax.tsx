export interface Context {
  types: PostgresSyntaxType[];
}

export interface Match {
  start: number;
  end: number;
  value: string;
  matches?: Record<string, string>;
}

export const matchRegExp = (
  regExp: RegExp,
  extractMatches?: (match: RegExpMatchArray) => Record<string, string>
) => (input: string) => {
  const match = input.match(regExp);
  if (!match) {
    return null;
  }
  let matches: Record<string, string>;
  if (extractMatches) {
    matches = extractMatches(match);
  }
  return {
    start: match.index,
    end: match.index + match[0].length,
    value: match[0],
    matches,
  };
};

export abstract class PostgresSyntax {
  protected constructor(
    public readonly type: PostgresSyntaxType,
    public readonly match: Match,
    public readonly context: Context
  ) {
  }

  parse = (input: string, types: PostgresSyntaxType[]): PostgresSyntax[] => {
    const elements: PostgresSyntax[] = [];
    let position = 0;
    while (position < input.length) {
      let nearestType: PostgresSyntaxType;
      let nearestMatch: Match;
      for (let type of types) {
        let match = type.matcher(input);
        if (match && (!nearestMatch || match.start < nearestMatch.start)) {
          nearestMatch = match;
          nearestType = type;
        }
      }
      if (!nearestType) {
        break;
      }
      elements.push(new nearestType.syntaxClass(nearestType, nearestMatch, this.context));
      position = nearestMatch.end;
    }
    return elements;
  };
}

export interface PostgresSyntaxType {
  syntaxClass: (new (type: PostgresSyntaxType, match: Match, context: Context) => PostgresSyntax);
  name: string;
  matcher: (input: string) => Match | null;
}
