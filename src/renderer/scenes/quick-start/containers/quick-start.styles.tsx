import { Theme } from '@material-ui/core';
import { StyleRules } from '@material-ui/core/es/styles';

type Classes = 'container' | 'gridList' | 'card';

export const styles = (theme: Theme): StyleRules<Classes> => ({
  container: {
    padding: theme.spacing.unit * 2,
    display: 'flex',
    flexDirection: 'column',
    height: '100%',
  },
  gridList: {
    flex: 1,
  },
  card: {
    margin: theme.spacing.unit,
    padding: theme.spacing.unit,
    height: '160px',
  },
});
