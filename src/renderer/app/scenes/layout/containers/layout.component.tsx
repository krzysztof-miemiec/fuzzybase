import { withStyles } from 'material-ui';
import React from 'react';
import { connect } from 'react-redux';
import { AppState } from '../../../store';
import { mapActions } from '../../../utils/redux.util';
import { select } from '../../../utils/selector.util';
import { StyleProps } from '../../../utils/styles.util';
import { Drawer } from '../components/drawer/drawer.component';
import { Toolbar } from '../components/toolbar/toolbar.component';
import { getLayoutState, isDrawerOpen } from '../store';
import { closeDrawer, openDrawer } from '../store/layout.actions';
import { styles } from './layout.styles';
import { Snackbar } from './snackbar.component';

const mapStateToProps = (state: AppState) => ({
  isDrawerOpen: select(state, getLayoutState, isDrawerOpen),
});

const mapDispatchToProps = mapActions({
  openDrawer,
  closeDrawer,
});

type Props = ReturnType<typeof mapStateToProps> & typeof mapDispatchToProps;

const LayoutComponent: React.SFC<Props & StyleProps<typeof styles>> = ({
  isDrawerOpen, actions, classes,
}) => (
  <div className={classes.root}>
    <Toolbar isDrawerOpen={isDrawerOpen} onMenuClicked={actions.openDrawer} />
    <Drawer isOpen={isDrawerOpen} onClose={actions.closeDrawer} />
    <Snackbar />
    <div className={classes.content}>
      <div className={classes.toolbar} />
      {require('../../../app.navigation').AppNavigation()}
    </div>
  </div>
);

export const Layout = connect(mapStateToProps, mapDispatchToProps)(withStyles(styles)(LayoutComponent));
