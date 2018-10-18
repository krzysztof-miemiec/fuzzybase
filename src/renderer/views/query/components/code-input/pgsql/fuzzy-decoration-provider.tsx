import { editor, IRange, Range } from 'monaco-editor/esm/vs/editor/editor.api';
import { DatabaseMetadata, FuzzyFunction } from '../../../../../../common/db/store/db.state';
import { styles } from '../code-input.styles';

const STATIC_FUZZY_FUNCTIONS = [
  'degree',
  'defuzzy',
  'notdefuzzy',
  'to_trapezoidal_function',
  'to_fext_not_equal',
  'to_fext_equal',
  'to_fext_greater_equal',
  'to_fext_greater',
  'to_fext_lower_equal',
  'to_fext_lower',
  'trapezoidal_function_in',
  'trapezoidal_function_out',
  'trapezoidal_function_ext_in',
  'trapezoidal_function_ext_out',
  'almost_none',
  'almost_all',
  'about_a_quarter_of_an_hour',
  'about_a_quarter',
  'about_a_third',
  'about_half',
  'about_two_thirds',
  'about_three_quarters',
  'about_one',
  'about_some',
  'about_a_dozen',
  'about_a_few_dozen',
  'about_a_few_hundred',
  'about_a_minute',
  'about_a_week',
  'about_a_month',
  'about_a_year',
  'about_an_hour',
  'about',
  'seconds_to_str',
  'days_to_str',
  'add_fuzzy_type',
  'add_fuzzy_function',
  'get_fuzzy_name',
  'delete_fuzzy_function',
  'get_fuzzy_types',
  'get_fuzzy_functions',
  'get_fuzzy_type_functions',
  'delete_fuzzy_type',
];
const STATIC_FUZZY_FUNCTIONS_REGEX = '(' + STATIC_FUZZY_FUNCTIONS.join('|') + ')';

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
    const newDecorations: editor.IModelDeltaDecoration[] = [
      ...(
        model.findMatches(
          /'([^']+?)'\s*\|>\s*'([^']+?)'/.source,
          true, true, true, null, true
        )
          .filter(m => Range.areIntersectingOrTouching(m.range, range))
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
      ),
      ...(
        model.findMatches(
          STATIC_FUZZY_FUNCTIONS_REGEX, true, true, false, ' ()', true
        )
          .filter(m => Range.areIntersectingOrTouching(m.range, range))
          .map((m): editor.IModelDeltaDecoration => {
            return {
              range: m.range,
              options: {
                inlineClassName: styles.builtinFunctionDecoration,
              },
            };
          })
      ),
    ];
    this.decorations.push(
      ...editor.deltaDecorations(toRemove, newDecorations)
    );
  };
}
