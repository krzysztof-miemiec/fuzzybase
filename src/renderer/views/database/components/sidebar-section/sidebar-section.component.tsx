import { Tooltip, Typography } from '@material-ui/core';
import classNames from 'classnames';
import React from 'react';
import { styles } from './sidebar-section.styles';

import Add from '@material-ui/icons/AddCircleOutline';
import Close from '@material-ui/icons/Close';
import { View } from '../../../../shared/components/view';

interface Item {
  id?: string;
  name: string;
}

interface Props<T extends any> {
  title: string;
  hint?: string;
  items: T[];
  mapItem: (item: T) => Item;
  onAddClick?: () => void;
  addTooltipDescription?: string;
  onItemClick: (item: T) => void;
  onCloseItemClick?: (item: T) => void;
}

export class SidebarSectionComponent<T extends any> extends React.Component<Props<T>> {
  constructor(props: Props<T>) {
    super(props);
    this.state = {};
  }

  renderItem = (item: T, index: number) => {
    const { mapItem, hint, onItemClick, onCloseItemClick } = this.props;
    const mappedItem = mapItem(item);
    const isHint = !mappedItem.name;
    return (
      <View style={styles.element} onClick={() => onItemClick(item)} key={index}>
        <Typography
          className={classNames([styles.elementText, isHint && styles.elementTextHint])}
          key={index + (mappedItem.id || mappedItem.name)}
        >
          {isHint ? hint : mappedItem.name}
        </Typography>
        {!!onCloseItemClick && (
          <Tooltip title="Close">
            <Close
              className={classNames([styles.icon, styles.elementIcon])}
              fontSize={'inherit'}
              onClick={() => onCloseItemClick(item)}
            />
          </Tooltip>
        )}
      </View>
    );
  };

  render() {
    const { title, onAddClick, addTooltipDescription, items } = this.props;
    return (
      <div className={styles.container}>
        <div className={styles.titleContainer}>
          <Typography className={styles.title}>
            {title}
          </Typography>
          {!!addTooltipDescription && !!onAddClick && (
            <Tooltip title={addTooltipDescription}>
              <Add onClick={onAddClick} className={styles.icon} fontSize={'inherit'} />
            </Tooltip>
          )}
        </div>
        {items && items.map(this.renderItem)}
      </div>
    );
  }
}

export const SidebarSection = SidebarSectionComponent;
