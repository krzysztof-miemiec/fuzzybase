import { Typography, withStyles } from '@material-ui/core';
import { SvgIconProps } from '@material-ui/core/SvgIcon/SvgIcon';
import React from 'react';
import { R } from '../../../../../common/resources';
import { StyleProps } from '../../../../utils/styles.util';
import { styles } from './drawer-item.styles';

export interface Props {
  id?: string;
  name: string;
  icon: React.ComponentType<SvgIconProps>;
  onClick: (id: string) => void;
}

class DrawerItemComponent extends React.PureComponent<Props & StyleProps<typeof styles>> {

  onClick = () => {
    this.props.onClick(this.props.id);
  };

  render() {
    const { classes, name, icon: Icon } = this.props;
    return (
      <div
        className={classes.container}
        onClick={this.onClick}
      >
        <div className={classes.iconContainer}>
          <Icon style={{ fontSize: R.dimen.drawerIcon, color: R.color.white }} />
        </div>
        <Typography variant="caption" className={classes.text}>{name}</Typography>
      </div>
    );
  }

}

export const DrawerItem = withStyles(styles)<Props>(DrawerItemComponent);
