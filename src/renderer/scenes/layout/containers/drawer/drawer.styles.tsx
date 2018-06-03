import { Theme } from '@material-ui/core';
import { StyleRules } from '@material-ui/core/styles';
import { R } from '../../../../../common/resources';

type Classes = 'drawerPaper' | 'drawerPaperClose' | 'toolbar';

export const styles = (theme: Theme): StyleRules<Classes> => ({
  drawerPaper: {
    position: 'relative',
    whiteSpace: 'nowrap',
    width: R.dimen.drawerWidth,
    transition: theme.transitions.create('width', {
      easing: theme.transitions.easing.sharp,
      duration: theme.transitions.duration.enteringScreen,
    }),
  },
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
  },
  toolbar: {
    display: 'flex',
    alignItems: 'center',
    justifyContent: 'flex-end',
    padding: '0 8px',
    ...theme.mixins.toolbar,
  },
});
