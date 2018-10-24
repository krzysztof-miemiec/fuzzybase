import { Menu, MenuItem, Typography } from '@material-ui/core';
import React from 'react';
import { DatabaseState } from '../../../../../common/db/store/app';
import { R } from '../../../../../common/resources';
import { View } from '../../../../shared/components/view';
import { InstallExtensionDialog } from '../../../extension/containers/install-extension-dialog';
import { styles } from './database-title.styles';

interface Props {
  database: DatabaseState;
  connectionId: string;
  user: string;
  onCloseConnection: () => void;
}

interface State {
  menuAnchor?: any;
  isExtensionDialogOpen: boolean;
}

export class DatabaseTitle extends React.Component<Props, State> {
  constructor(props: Props) {
    super(props);
    this.state = { isExtensionDialogOpen: false };
  }

  onTitleClick = event => {
    this.setState({ menuAnchor: event.currentTarget });
  };

  onOpenInstallExtensionDialog = () => {
    this.setState({ isExtensionDialogOpen: true });
    this.onMenuClose();
  };

  onCloseInstallExtensionDialog = () => {
    this.setState({ isExtensionDialogOpen: false });
  };

  onMenuClose = () => {
    this.setState({ menuAnchor: null });
  };

  render() {
    const { database, connectionId, user, onCloseConnection } = this.props;
    const { menuAnchor, isExtensionDialogOpen } = this.state;
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
          {!database.meta.hasFuzzyExtension && (
            <MenuItem onClick={this.onOpenInstallExtensionDialog}>Install Fuzzy extension</MenuItem>
          )}
          <MenuItem onClick={onCloseConnection}>Close</MenuItem>
        </Menu>
        <InstallExtensionDialog
          isOpen={isExtensionDialogOpen}
          databaseId={database.id}
          connectionId={connectionId}
          onClose={this.onCloseInstallExtensionDialog}
        />
      </>
    );
  }
}
