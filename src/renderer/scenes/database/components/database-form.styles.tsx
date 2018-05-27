import { Theme } from '@material-ui/core';
import { StyleRules } from '@material-ui/core/styles';

type Classes = 'container' | 'input' | 'inputShort';

export const styles = (theme: Theme): StyleRules<Classes> => ({
  container: {
    display: 'flex',
    flexDirection: 'column',
    width: 250,
  },
  input: {
    marginTop: theme.spacing.unit,
    marginBottom: theme.spacing.unit,
  },
  inputShort: {
    width: 50,
  },
});
