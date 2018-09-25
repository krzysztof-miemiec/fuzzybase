import React from 'react';
import { connect } from 'react-redux';
import { View } from '../../../../shared/components/view';
import { AppState } from '../../../../store';
import { mapActions } from '../../../../utils/redux.util';
import { select } from '../../../../utils/selector.util';
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

const LayoutComponent: React.SFC<Props> = ({
  children,
}) => (
  <View style={styles.container}>
    <Drawer />
    <View style={styles.content}>
      {children}
    </View>
  </View>
);

export const Layout = connect(mapStateToProps, mapDispatchToProps)(LayoutComponent);
