import { Theme } from '@material-ui/core';
import { StyleRules } from '@material-ui/core/styles';

type Classes =
  | 'container'
  | 'content'
  | 'snackbarContainer'
  | 'snackbar';

export const styles = (theme: Theme): StyleRules<Classes> => ({
  container: {
    display: 'flex',
    zIndex: 1,
    overflow: 'hidden',
    position: 'relative',
    height: '100%',
    width: '100%',
  },
  snackbarContainer: {
    position: 'absolute',
    bottom: 0,
    left: 0,
    display: 'flex',
    flexDirection: 'column-reverse',
  },
  snackbar: {
    position: 'relative',
    padding: theme.spacing.unit,
    display: 'flex',
    justifyContent: 'flex-start',
    left: 0,
    transform: 'none',
  },
  content: {
    flexGrow: 1,
    backgroundColor: theme.palette.background.default,
    height: '100%',
    '-webkit-app-region': 'drag',
  },
});
