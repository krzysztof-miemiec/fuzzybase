import { Theme } from '@material-ui/core';
import { CSSProperties } from '@material-ui/core/styles/withStyles';
import { R } from '../../../../../common/resources';

export const styles = (theme: Theme) => ({
  drawerPaper: {
    position: 'relative',
    whiteSpace: 'nowrap',
    width: R.dimen.drawerWidth,
    transition: theme.transitions.create('width', {
      easing: theme.transitions.easing.sharp,
      duration: theme.transitions.duration.enteringScreen,
    }),
  } as CSSProperties,
  drawerPaperClose: {
    overflowX: 'hidden',
    transition: theme.transitions.create('width', {
      easing: theme.transitions.easing.sharp,
      duration: theme.transitions.duration.leavingScreen,
    }),
    width: theme.spacing.unit * 7,
    [theme.breakpoints.up('sm')]: {
      width: theme.spacing.unit * 9,
    },
  } as CSSProperties,
  toolbar: {
    display: 'flex',
    alignItems: 'center',
    justifyContent: 'flex-end',
    padding: '0 8px',
    ...theme.mixins.toolbar,
  } as CSSProperties,
});
