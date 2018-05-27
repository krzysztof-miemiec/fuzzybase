import { Theme } from '@material-ui/core';
import { CSSProperties } from '@material-ui/core/styles/withStyles';

export const styles = (theme: Theme) => ({
  container: {
    padding: theme.spacing.unit * 2,
  },
  fab: {
    position: 'absolute',
    bottom: theme.spacing.unit * 2,
    right: theme.spacing.unit * 2,
  } as CSSProperties,
});
