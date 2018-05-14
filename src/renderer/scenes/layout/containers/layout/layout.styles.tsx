import { Theme } from 'material-ui';
import { CSSProperties } from 'material-ui/styles/withStyles';
import { R } from '../../../../../common/resources';

export const styles = (theme: Theme) => ({
  root: {
    flexGrow: 1,
    zIndex: 1,
    overflow: 'hidden',
    position: 'relative',
    display: 'flex',
  } as CSSProperties,
  snackbarContainer: {
    position: 'absolute',
    bottom: 0,
    left: 0,
    display: 'flex',
    flexDirection: 'column-reverse',
  } as CSSProperties,
  snackbar: {
    position: 'relative',
    padding: theme.spacing.unit,
    display: 'flex',
    justifyContent: 'flex-start',
    left: 0,
    transform: 'none',
  } as CSSProperties,
  content: {
    flexGrow: 1,
    backgroundColor: theme.palette.background.default,
    padding: theme.spacing.unit * 3,
  } as CSSProperties,
  toolbar: {
    display: 'flex',
    alignItems: 'center',
    justifyContent: 'flex-end',
    padding: '0 8px',
    ...theme.mixins.toolbar,
  } as CSSProperties,
  flex: {
    flex: 1,
  } as CSSProperties,
  appBar: {
    zIndex: theme.zIndex.drawer + 1,
    transition: theme.transitions.create(['width', 'margin'], {
      easing: theme.transitions.easing.sharp,
      duration: theme.transitions.duration.leavingScreen,
    }),
  } as CSSProperties,
  appBarShift: {
    marginLeft: R.dimen.drawerWidth,
    width: `calc(100% - ${R.dimen.drawerWidth}px)`,
    transition: theme.transitions.create(['width', 'margin'], {
      easing: theme.transitions.easing.sharp,
      duration: theme.transitions.duration.enteringScreen,
    }),
  } as CSSProperties,
  menuButton: {
    marginLeft: 12,
    marginRight: 36,
  } as CSSProperties,
  hide: {
    display: 'none',
  } as CSSProperties,
});
