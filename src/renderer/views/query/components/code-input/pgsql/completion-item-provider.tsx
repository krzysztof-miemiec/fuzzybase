import { editor, languages, Position, Range } from 'monaco-editor/esm/vs/editor/editor.api';
import { DatabaseMetadata, FuzzyType } from '../../../../../../common/db/store/db.state';

type TextModel = editor.ITextModel;
type CompletionList = languages.CompletionList;
type CompletionItem = languages.CompletionItem;

/*const getTableByName = (tableName: string, metadata: DatabaseMetadata) => {
  const parts = tableName.replace(/"/g, '').split('.');
  while (parts.length < 3) {
    parts.unshift('');
  }
  const foundTable = Object.keys(metadata.tables)
    .find(table => {
      const tableParts = table.split('.');
      return (tableParts[2] === parts[2])
        && (parts[1] && tableParts[1] === parts[1])
        && (parts[0] && tableParts[0] === parts[0]);
    });
  return metadata.tables[foundTable];
};*/

const normalizeTableName = (fullTableName: string, metadata: DatabaseMetadata) => {
  const [, schema, table] = fullTableName.split('.');
  const normalizedTable = table.match(/[A-Z]/) ? `"${table}"` : table;
  if (metadata.searchPath.indexOf(schema) < 0) {
    const normalizedSchema = schema.match(/[A-Z]/) ? `"${schema}"` : schema;
    return normalizedSchema + '.' + normalizedTable;
  }
  return normalizedTable;
};

export class PostgresCompletionItemProvider implements languages.CompletionItemProvider {
  public readonly triggerCharacters: string[] = ['.'];
  private metadata: DatabaseMetadata;

  public setMetadata(metadata: Partial<DatabaseMetadata>) {
    this.metadata = metadata;
  }

  public provideCompletionItems(model: TextModel, position: Position): CompletionList {
    const currentWord = model.getWordUntilPosition(position);
    const currentWordRange: Range = new Range(
      position.lineNumber,
      currentWord.startColumn,
      position.lineNumber,
      currentWord.endColumn
    );
    const beforeCursor = model.getValueInRange({
      startLineNumber: 1,
      startColumn: 1,
      endLineNumber: position.lineNumber,
      endColumn: position.column,
    });

    if (this.metadata && this.metadata.hasFuzzyExtension) {
      const items = this.getFuzzyTypeFunctionsCompletion(beforeCursor, currentWordRange)
        || this.getFuzzyTypesCompletion(beforeCursor, currentWordRange);
      if (items) {
        return { isIncomplete: false, items };
      }
    }

    return { isIncomplete: false, items: [] };
  }

  getFuzzyTypeFunctionsCompletion = (beforeText: string, rangeToReplace: Range): CompletionItem[] | null => {
    const match = beforeText.match(/([(\s]*)'([^']+)'([\s)]*)\|>[\s(]*('?)([^\s')]*)$/);
    if (!match) {
      return null;
    }
    const [, typeBraceStart, typeName, typeBraceEnd, functionQuote, functionName] = match;
    if ((typeBraceStart.match(/\(/g) || []).length < (typeBraceEnd.match(/\)/g) || []).length) {
      return null;
    }
    const type: FuzzyType = this.metadata.fuzzyTypes[typeName];
    if (!type) {
      return null;
    }
    const quote = functionQuote ? '' : '\'';
    return type.functions
      .filter(fun => fun.name.indexOf(functionName) >= 0)
      .map(fun => {
        const [a, b, c, d] = fun.range;
        return {
          label: fun.name,
          filterText: functionName,
          kind: languages.CompletionItemKind.Method,
          range: rangeToReplace,
          detail: `${a}/${b}~${c}\\${d}`,
          insertText: quote + fun.name + quote,
        };
      });
  };

  getFuzzyTypesCompletion = (beforeText: string, rangeToReplace: Range): CompletionItem[] | null => {
    const match = beforeText.match(/~=[(\s]*('?)([^\s']*)$/);
    if (!match) {
      return null;
    }
    const [, typeQuote, typeName] = match;
    const quote = typeQuote ? '' : '\'';
    return Object.keys(this.metadata.fuzzyTypes)
      .filter(type => type.indexOf(typeName) >= 0)
      .map(type => this.metadata.fuzzyTypes[type])
      .map((type: FuzzyType) => ({
        label: type.name,
        filterText: typeName,
        kind: languages.CompletionItemKind.Class,
        range: rangeToReplace,
        detail: type.functions.map(fun => fun.name).join('\n'),
        insertText: quote + type.name + quote,
      }));
  };

  getTableNamesCompletionItems(options: {
    whitespace: string,
    lastWord: string,
  }): CompletionItem[] {
    const { tables } = this.metadata;

    return Object.keys(tables)
      .filter(table => table.indexOf(options.lastWord) >= 0)
      .map(tableName => {
        const name = normalizeTableName(tableName, this.metadata);
        return {
          label: name,
          // filterText: options.lastWord,
          kind: languages.CompletionItemKind.Class,
          insertText: options.whitespace + name,
        };
      });
  }

  public resolveCompletionItem(item: CompletionItem): CompletionItem {
    return item;
  }

}
