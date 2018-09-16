import { Typography } from '@material-ui/core';
import classNames from 'classnames';
import React from 'react';
import { styles } from './sidebar-section.styles';

import Add from '@material-ui/icons/AddCircleOutline';

interface Item {
  id?: string;
  name: string;
}

interface Props<T extends any> {
  title: string;
  hint?: string;
  items: T[];
  mapItem: (item: T) => Item;
  onAdd: () => void;
  onItemClick: (item: T) => void;
}

export class SidebarSectionComponent<T extends any> extends React.Component<Props<T>> {
  constructor(props: Props<T>) {
    super(props);
    this.state = {};
  }

  renderItem = (item: T) => {
    const { mapItem, hint } = this.props;
    const mappedItem = mapItem(item);
    const isHint = !mappedItem.name;
    return (
      <Typography
        className={classNames([styles.element, isHint && styles.elementHint])}
        key={mappedItem.id || mappedItem.name}
        onClick={() => this.props.onItemClick(item)}
      >
        {isHint ? hint : mappedItem.name}
      </Typography>
    );
  };

  render() {
    const { title, onAdd, items } = this.props;
    return (
      <div className={styles.container}>
        <div className={styles.titleContainer} onClick={onAdd}>
          <Typography className={styles.title}>
            {title}
          </Typography>
          <Add className={styles.icon} fontSize={'inherit'} />
        </div>
        {items && items.map(this.renderItem)}
      </div>
    );
  }
}

export const SidebarSection = SidebarSectionComponent;
