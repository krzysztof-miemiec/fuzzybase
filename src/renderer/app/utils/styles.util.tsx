import { WithStyles } from 'material-ui';

export type StyleProps<Styles> = Styles extends ((...args: any[]) => any)
  ? WithStyles<keyof ReturnType<Styles>>
  : WithStyles<keyof Styles>;
