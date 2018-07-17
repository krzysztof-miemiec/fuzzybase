import { WithStyles } from '@material-ui/core';

export type StyleProps<Styles> = Styles extends ((...args: any[]) => any)
  ? WithStyles<keyof ReturnType<Styles> & string>
  : WithStyles<keyof Styles & string>;
