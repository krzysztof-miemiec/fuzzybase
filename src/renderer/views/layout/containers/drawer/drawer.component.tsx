import { withStyles } from '@material-ui/core';
import React from 'react';
import { connect } from 'react-redux';
import { RouteComponentProps, withRouter } from 'react-router';
import { Config } from '../../../../../common/config';
import { getDatabaseList, getDatabasesState } from '../../../../../common/db/store/db.selectors';
import { PATHS } from '../../../../app.paths';
import { AppState } from '../../../../store';
import { select } from '../../../../utils/selector.util';
import { StyleProps } from '../../../../utils/styles.util';
import { DrawerItem } from '../drawer-item/drawer-item.component';
import { styles } from './drawer.styles';

import AddIcon from '@material-ui/icons/Add';
import DatabaseIcon from '@material-ui/icons/Storage';

const mapStateToProps = (state: AppState) => ({
  databases: select(state, getDatabasesState, getDatabaseList),
});

type Props =
  & ReturnType<typeof mapStateToProps>
  & RouteComponentProps<{}>
  & StyleProps<typeof styles>;

class DrawerComponent extends React.PureComponent<Props> {

  onItemClick = (id: string | undefined) => {
    this.props.history.replace(PATHS.DATABASE(id));
  };

  renderItem = ({ id, name }) => (
    <DrawerItem key={id} id={id} name={name} icon={DatabaseIcon} onClick={this.onItemClick} />
  );

  render() {
    const { classes, databases } = this.props;
    return (
      <div className={classes.container}>
        {Config.IS_MAC && (
          <div className={classes.draggable} />
        )}
        {databases.map(this.renderItem)}
        <DrawerItem name="Add" icon={AddIcon} onClick={this.onItemClick} />
      </div>
    );
  }
}

export const Drawer = connect(mapStateToProps)(
  withStyles(styles)(
    withRouter(DrawerComponent)
  )
);
