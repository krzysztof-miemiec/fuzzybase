import React from 'react';
import { connect } from 'react-redux';
import { RouteComponentProps, withRouter } from 'react-router';
import { Config } from '../../../../../common/config';
import { getDatabaseList, getDatabasesState } from '../../../../../common/db/store/db.selectors';
import { select } from '../../../../../common/utils/selector.util';
import { PATHS } from '../../../../app.paths';
import { AppState } from '../../../../store';
import { DrawerItem } from '../drawer-item/drawer-item.component';
import { styles } from './drawer.styles';

import AddIcon from '@material-ui/icons/Add';
import DatabaseIcon from '@material-ui/icons/Storage';

const mapStateToProps = (state: AppState) => ({
  databases: select(state, getDatabasesState, getDatabaseList),
});

type Props =
  & ReturnType<typeof mapStateToProps>
  & RouteComponentProps<{}>;

class DrawerComponent extends React.PureComponent<Props> {

  onItemClick = (id: string | undefined) => {
    this.props.history.replace(PATHS.DATABASE(id));
  };

  renderItem = ({ id, name }) => (
    <DrawerItem key={id} id={id} name={name} icon={DatabaseIcon} onClick={this.onItemClick} />
  );

  render() {
    const { databases } = this.props;
    return (
      <div className={styles.container}>
        {Config.IS_MAC && (
          <div className={styles.draggable} />
        )}
        {databases.map(this.renderItem)}
        <DrawerItem name="Add" icon={AddIcon} onClick={this.onItemClick} />
      </div>
    );
  }
}

export const Drawer = connect(mapStateToProps)(withRouter(DrawerComponent));
