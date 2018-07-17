import { Typography, withStyles } from '@material-ui/core';
import React from 'react';
import { DatabaseTable } from '../../../../../common/db/store/app';
import { StyleProps } from '../../../../utils/styles.util';
import { styles } from './database-tables.styles';

import Add from '@material-ui/icons/AddCircleOutline';

interface Props {
  tables: DatabaseTable[];
  onAdd: () => void;
  onTableClick: (table: DatabaseTable) => void;
}

export class DatabaseTablesComponent extends React.Component<Props & StyleProps<typeof styles>> {
  constructor(props: Props & StyleProps<typeof styles>) {
    super(props);
    this.state = {};
  }

  renderTable = (table: DatabaseTable) => {
    return (
      <Typography
        key={table.name}
        onClick={() => this.props.onTableClick(table)}
      >
        {table.name}
      </Typography>
    );
  };

  render() {
    const { classes, onAdd, tables } = this.props;
    console.log(tables);
    return (
      <div className={classes.container}>
        <div className={classes.titleContainer} onClick={onAdd}>
          <Typography className={classes.title}>
            Tables
          </Typography>
          <Add className={classes.icon} />
        </div>
        {tables && tables.map(this.renderTable)}
      </div>
    );
  }
}

export const DatabaseTables = withStyles(styles)<Props>(DatabaseTablesComponent);
