import { withStyles } from '@material-ui/core';
import React from 'react';
import { connect } from 'react-redux';
import { AppState } from '../../../../store';
import { mapActions } from '../../../../utils/redux.util';
import { select } from '../../../../utils/selector.util';
import { StyleProps } from '../../../../utils/styles.util';
import { getLayoutState, isDrawerOpen } from '../../store';
import { closeDrawer, openDrawer } from '../../store/layout.actions';
import { Drawer } from '../drawer/drawer.component';
import { styles } from './layout.styles';

const mapStateToProps = (state: AppState) => ({
  isDrawerOpen: select(state, getLayoutState, isDrawerOpen),
});

const mapDispatchToProps = mapActions({
  openDrawer,
  closeDrawer,
});

type Props = ReturnType<typeof mapStateToProps> & typeof mapDispatchToProps;

const LayoutComponent: React.SFC<Props & StyleProps<typeof styles>> = ({
  classes, children,
}) => (
  <div className={classes.container}>
    <Drawer />

    <div className={classes.content}>
      {children}
    </div>
  </div>
);

export const Layout = connect(mapStateToProps, mapDispatchToProps)(withStyles(styles)(LayoutComponent));
