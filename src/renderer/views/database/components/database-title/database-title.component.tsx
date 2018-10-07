import { Menu, MenuItem, Typography } from '@material-ui/core';
import React from 'react';
import { DatabaseState } from '../../../../../common/db/store/app';
import { R } from '../../../../../common/resources';
import { View } from '../../../../shared/components/view';
import { styles } from './database-title.styles';

interface Props {
  database: DatabaseState;
  user: string;
  onCloseConnection: () => void;
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
    const { database, user, onCloseConnection } = this.props;
    const { menuAnchor } = this.state;
    return (
      <>
        <View
          style={[styles.container, menuAnchor && styles.highlightedContainer]}
          onClick={this.onTitleClick}
        >
          <div>
            <Typography className={styles.title}>
              {database.name}
            </Typography>
            <Typography className={styles.subtitle}>
              {user}
            </Typography>
          </div>
        </View>
        <Menu
          id="title-menu"
          anchorEl={menuAnchor}
          style={{
            marginTop: -R.dimen.spacing,
            marginLeft: R.dimen.spacing,
          }}
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
          <MenuItem onClick={onCloseConnection}>Close</MenuItem>
        </Menu>
      </>
    );
  }
}
