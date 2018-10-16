import { editor, languages, Position } from 'monaco-editor/esm/vs/editor/editor.api';
import { DatabaseMetadata } from '../../../../../../common/db/store/db.state';

type TextModel = editor.ITextModel;
type CompletionList = languages.CompletionList;
type CompletionItem = languages.CompletionItem;

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
    model.getOffsetAt(position);
    const beforeCursor = model.getValueInRange({
      startLineNumber: 1,
      startColumn: 1,
      endLineNumber: position.lineNumber,
      endColumn: position.column,
    });
    const afterCursor = model.getValueInRange({
      startLineNumber: position.lineNumber,
      startColumn: position.column,
      endLineNumber: model.getLineCount(),
      endColumn: model.getLineLength(model.getLineCount()),
    });
    let matchBefore: RegExpMatchArray | null = null;
    let matchAfter: RegExpMatchArray | null = null;

    const hasTables = !!this.metadata && !!this.metadata.tables;
    // const hasFuzzyTypes = !!this.databaseMetadata && !!this.databaseMetadata.fuzzyTypes;

    if (matchBefore = beforeCursor.match(/(?:FROM|JOIN)(\s*)(.*)$/i)) {
      const hasWhitespace = matchBefore[1].length > 0;
      const whitespace = hasWhitespace ? '' : ' ';
      const lastWord = matchBefore[2].substring(matchBefore[2].indexOf(',') + 1);

      return {
        isIncomplete: !hasTables,
        items: !hasTables ? [] : this.getTableNamesCompletionItems({
          whitespace,
          lastWord,
        }),
      };
    }
    if (matchBefore = beforeCursor.match(/SELECT(\s*)(.+)$/i)) {
      if (matchAfter = afterCursor.match(/^(.+)\s+FROM\s+(.+)/i)) {
      } else {
        return {
          isIncomplete: false,
          items: [
            {
              label: '*',
              kind: languages.CompletionItemKind.Field,
              insertText: '*',
            },
          ],
        };
      }
    }
    return { isIncomplete: false, items: [] };
  }

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
