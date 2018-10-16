import { editor, Position } from 'monaco-editor/esm/vs/editor/editor.api';

type TextModel = editor.ITextModel;

interface ClauseFragmentRegExp {
  name: string;
  before: RegExp;
  beforeContextNames: string[];
  after: RegExp;
  afterContextNames: string[];
}

interface FragmentResult {
  name: string;
  wordBefore: string;
  context: Record<string, string>;
}

export interface Clause {
  name: string;
  fragments: ClauseFragmentRegExp[];
}

export const parseClause = (clause: string): Clause => {
  const name = clause.match(/^(.+)\s/)[1];
  const expression = /\[(.+)]/g;

  let exec: RegExpExecArray;
  const fragments: ClauseFragmentRegExp[] = [];
  while (exec = expression.exec(clause)) {
    const index = exec.index;
    const name = exec[1];
    const beforeText = clause.slice(0, index);
    const beforeContextNames = beforeText.match(/\[(.+)]/g).slice(1);
    const before = new RegExp((
      beforeText
        .replace(/\[(.+)]/g, '(.*)')
        .replace(/\s+/g, '\s+')
    ) + '$', 'i');
    const afterText = clause.slice(index + exec[0].length);
    const afterContextNames = afterText.match(/\[(.+)]/g).slice(1);

    const after = new RegExp('^' + (
      afterText
        .replace(/\[(.+)]/g, '(.*)')
        .replace(/\s+/g, '\s+')
    ), 'i');
    fragments.push({
      name,
      after,
      afterContextNames,
      before,
      beforeContextNames,
    });
  }
  return {
    name,
    fragments,
  };
};

export const getFragmentFor = (model: TextModel, position: Position, clauses: Clause[]): FragmentResult | undefined => {
  const textBefore = model.getValueInRange({
    startLineNumber: 1,
    startColumn: 1,
    endLineNumber: position.lineNumber,
    endColumn: position.column,
  });
  const textAfter = model.getValueInRange({
    startLineNumber: position.lineNumber,
    startColumn: position.column,
    endLineNumber: model.getLineCount(),
    endColumn: model.getLineLength(model.getLineCount()),
  });
  let nearestClause: Clause = undefined;
  let nearestClauseDistance: number = textBefore.length;
  for (let clause of clauses) {
    const distance = textBefore.lastIndexOf(clause.name) + clause.name.length;
    if (distance < nearestClauseDistance) {
      nearestClause = clause;
    }
  }
  if (!nearestClause) {
    return undefined;
  }
  for (let fragment of nearestClause.fragments) {
    const before = !fragment.before || textBefore.match(fragment.before);
    const after = !fragment.after || textAfter.match(fragment.after);
    if (after && before) {
      const context: Record<string, string> = {};
      if (before !== true) {
        for (let i = 1; i < before.length; i++) {
          context[fragment.beforeContextNames[i]] = before[i];
        }
      }
      if (after !== true) {
        for (let i = 1; i < after.length; i++) {
          context[fragment.afterContextNames[i]] = after[i];
        }
      }
      return {
        name: fragment.name,
        wordBefore: model.getWordUntilPosition(position).word,
        context,
      };
    }
  }
  return undefined;
};
