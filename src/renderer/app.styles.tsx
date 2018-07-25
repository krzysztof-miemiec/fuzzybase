import { createGenerateClassName, jssPreset } from '@material-ui/core/styles';
import { Classes, create, CreateStyleSheetOptions } from 'jss';
import { Style } from 'jss/css';

export const JSS = create(jssPreset());
export const generateClassName = createGenerateClassName();

type Styles<Name extends string = any> = Record<Name, Style | { '&:hover': Styles | Style }>;

export const createStyles = <Name extends string>(
  styles: Partial<Styles<Name>>,
  options?: CreateStyleSheetOptions<Name>
): Classes<Name> =>
  JSS.createStyleSheet(styles as any, options).attach().classes;

export const draggable: any = {
  '-webkit-app-region': 'drag',
};

export const noDraggable: any = {
  '-webkit-app-region': 'no-drag',
};
