import { Theme } from '@material-ui/core';
import { StyleRules } from '@material-ui/core/styles';
import { R } from '../../../../../common/resources';

type Classes =
  | 'root'
  | 'snackbarContainer'
  | 'snackbar'
  | 'content'
  | 'toolbar'
  | 'flex'
  | 'appBar'
  | 'appBarShift'
  | 'menuButton'
  | 'hide';

export const styles = (theme: Theme): StyleRules<Classes> => ({
  root: {
    flexGrow: 1,
    zIndex: 1,
    overflow: 'hidden',
    position: 'relative',
    display: 'flex',
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
  },
  toolbar: {
    display: 'flex',
    alignItems: 'center',
    justifyContent: 'flex-end',
    padding: '0 8px',
    ...theme.mixins.toolbar,
  },
  flex: {
    flex: 1,
  },
  appBar: {
    zIndex: theme.zIndex.drawer + 1,
    transition: theme.transitions.create(['width', 'margin'], {
      easing: theme.transitions.easing.sharp,
      duration: theme.transitions.duration.leavingScreen,
    }),
  },
  appBarShift: {
    marginLeft: R.dimen.drawerWidth,
    width: `calc(100% - ${R.dimen.drawerWidth}px)`,
    transition: theme.transitions.create(['width', 'margin'], {
      easing: theme.transitions.easing.sharp,
      duration: theme.transitions.duration.enteringScreen,
    }),
  },
  menuButton: {
    marginLeft: 12,
    marginRight: 36,
  },
  hide: {
    display: 'none',
  },
});
