import { Theme } from '@material-ui/core';
import { StyleRules } from '@material-ui/core/styles';

type Classes = 'container' | 'input' | 'inputShort' | 'row';

export const styles = (theme: Theme): StyleRules<Classes> => ({
  container: {
    display: 'flex',
    flexFlow: 'column',
  },
  row: {
    display: 'flex',
    flexFlow: 'row wrap',
  },
  input: {
    marginTop: theme.spacing.unit,
    marginBottom: theme.spacing.unit,
  },
  inputShort: {
    width: 50,
  },
});
