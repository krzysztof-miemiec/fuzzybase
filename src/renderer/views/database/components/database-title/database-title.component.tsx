import { Menu, MenuItem, Typography } from '@material-ui/core';
import React from 'react';
import { DatabaseState } from '../../../../../common/db/store/app';
import { styles } from './database-title.styles';

interface Props {
  database: DatabaseState;
}

interface State {
  menuAnchor?: any;
}

export class DatabaseTitle extends React.Component<Props, State> {
  constructor(props: Props) {
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
    const { database } = this.props;
    const { menuAnchor } = this.state;
    return (
      <>
        <div
          className={styles.container}
          onClick={this.onTitleClick}
        >
          <div>
            <Typography className={styles.title}>
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
