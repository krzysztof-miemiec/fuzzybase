import { editor, IRange, Range } from 'monaco-editor/esm/vs/editor/editor.api';
import { DatabaseMetadata, FuzzyFunction } from '../../../../../../common/db/store/db.state';
import { styles } from '../code-input.styles';

export class FuzzyDecorationProvider {
  private metadata: DatabaseMetadata;
  private decorations: string[];

  public setMetadata(metadata: Partial<DatabaseMetadata>) {
    this.metadata = metadata;
  }

  resetDecorations = () => {
    this.decorations = [];
  };

  updateDecorationsFor = (editor: editor.IStandaloneCodeEditor, range?: IRange) => {
    const model = editor.getModel();
    if (!range) {
      range = model.getFullModelRange();
    }
    const toRemove = this.decorations
      .filter(d => Range.areIntersectingOrTouching(model.getDecorationRange(d), range))
    ;
    this.decorations = this.decorations.filter(element => toRemove.indexOf(element) < 0);
    const newDecorations: editor.IModelDeltaDecoration[] = [];
    model.findMatches(
      /'([^']+?)'\s*\|>\s*'([^']+?)'/.source,
      true, true, true, null, true
    )
      .filter(m => {
        return Range.areIntersectingOrTouching(m.range, range);
      })
      .map((m): editor.IModelDeltaDecoration => {
        const [, typeName, funName] = m.matches;
        const type = this.metadata.fuzzyTypes[typeName];
        const fun: FuzzyFunction = type && type.functions.find(f => f.name === funName);
        const isValid = !!(type && fun);
        let hoverMessage: string;
        if (isValid) {
          const [a, b, c, d] = fun.range;
          hoverMessage = `${a}/${b}~${c}\\${d}`;
        } else {
          hoverMessage = !type
            ? `${typeName} is not a valid fuzzy type`
            : `${funName} is not a valid function of ${typeName} fuzzy type.`;
        }
        return {
          range: m.range,
          options: {
            hoverMessage: { value: hoverMessage },
            inlineClassName: styles.functionDecoration + ' ' + (isValid ? '' : styles.invalidFunctionDecoration),
          },
        };
      })
      .forEach(decoration => newDecorations.push(decoration));
    this.decorations.push(
      ...editor.deltaDecorations(toRemove, newDecorations)
    );
    console.log('remove', toRemove);
    console.log('new', newDecorations);
    console.log('current', this.decorations);
  };
}
