import { Typography } from '@material-ui/core';
import { SvgIconProps } from '@material-ui/core/SvgIcon/SvgIcon';
import React from 'react';
import { R } from '../../../../../common/resources';
import { styles } from './drawer-item.styles';

export interface Props {
  id?: string;
  name: string;
  icon: React.ComponentType<SvgIconProps>;
  onClick: (id: string) => void;
}

export class DrawerItem extends React.PureComponent<Props> {

  onClick = () => {
    this.props.onClick(this.props.id);
  };

  render() {
    const { name, icon: Icon } = this.props;
    return (
      <div
        className={styles.container}
        onClick={this.onClick}
      >
        <div className={styles.iconContainer}>
          <Icon style={{ fontSize: R.dimen.drawerIcon, color: R.color.white }} />
        </div>
        <Typography variant="caption" className={styles.text}>{name}</Typography>
      </div>
    );
  }

}
