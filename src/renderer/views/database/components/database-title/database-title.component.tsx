import { Menu, MenuItem, Typography, withStyles } from '@material-ui/core';
import React from 'react';
import { DatabaseState } from '../../../../../common/db/store/app';
import { StyleProps } from '../../../../utils/styles.util';
import { styles } from './database-title.styles';

interface Props {
  database: DatabaseState;
}

interface State {
  menuAnchor?: any;
}

export class DatabaseTitleComponent extends React.Component<Props & StyleProps<typeof styles>, State> {
  constructor(props: Props & StyleProps<typeof styles>) {
    super(props);
    this.state = {};
  }

  onTitleClick = event => {
    this.setState({ menuAnchor: event.currentTarget });
  };

  onMenuClose = () => {
    this.setState({ menuAnchor: null });

  };

  render() {
    const { classes, database } = this.props;
    const { menuAnchor } = this.state;
    return (
      <>
        <div
          className={classes.container}
          onClick={this.onTitleClick}
        >
          <div>
            <Typography className={classes.title}>
              {database.name}
            </Typography>
          </div>
        </div>
        <Menu
          id="title-menu"
          anchorEl={menuAnchor}
          getContentAnchorEl={null}
          anchorOrigin={{
            vertical: 'bottom',
            horizontal: 'left',
          }}
          open={!!menuAnchor}
          PaperProps={{
            elevation: 0,
          }}
          onClose={this.onMenuClose}
        >
          <MenuItem onClick={this.onMenuClose}>Configure</MenuItem>
        </Menu>
      </>
    );
  }
}

export const DatabaseTitle = withStyles(styles)<Props>(DatabaseTitleComponent);
