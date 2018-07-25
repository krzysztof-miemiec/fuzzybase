import { Typography, withStyles } from '@material-ui/core';
import React from 'react';
import { StyleProps } from '../../../../utils/styles.util';
import { styles } from './sidebar-section.styles';

import Add from '@material-ui/icons/AddCircleOutline';

interface Item {
  name: string;
}

interface Props<T extends any> {
  title: string;
  items: T[];
  mapItem: (item: T) => Item;
  onAdd: () => void;
  onItemClick: (item: T) => void;
}

export class SidebarSectionComponent<T extends any>
  extends React.Component<Props<T> & StyleProps<typeof styles>> {
  constructor(props: Props<T> & StyleProps<typeof styles>) {
    super(props);
    this.state = {};
  }

  renderItem = (item: T) => {
    const { classes, mapItem } = this.props;
    const mappedItem = mapItem(item);
    return (
      <Typography
        className={classes.element}
        key={mappedItem.name}
        onClick={() => this.props.onItemClick(item)}
      >
        {mappedItem.name}
      </Typography>
    );
  };

  render() {
    const { classes, title, onAdd, items } = this.props;
    console.log(items);
    return (
      <div className={classes.container}>
        <div className={classes.titleContainer} onClick={onAdd}>
          <Typography className={classes.title}>
            {title}
          </Typography>
          <Add className={classes.icon} fontSize={'inherit'} />
        </div>
        {items && items.map(this.renderItem)}
      </div>
    );
  }
}

export const SidebarSection = withStyles(styles)(SidebarSectionComponent);
