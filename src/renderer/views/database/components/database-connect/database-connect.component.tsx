import {
  Button,
  Dialog,
  DialogActions,
  DialogContent,
  DialogContentText,
  DialogTitle,
  Typography,
  WithStyles,
  withStyles
} from '@material-ui/core';
import React from 'react';
import { DatabaseState } from '../../../../../common/db/store/app';
import { Frame } from '../../../../shared/components/frame';
import { styles } from './database-connect.styles';

import Link from '@material-ui/icons/Link';

interface Props extends WithStyles<typeof styles> {
  database: DatabaseState;
  onConnect: () => void;
  onModify: () => void;
  onRemove: () => void;
}

interface State {
  removeDialog: boolean;
}

export class DatabaseConnectComponent extends React.Component<Props, State> {
  constructor(props: Props) {
    super(props);
    this.state = { removeDialog: false };
  }

  onRemove = () => {
    this.setState({ removeDialog: true });
  };

  onDialogClose = () => {
    this.setState({ removeDialog: false });
  };

  render() {
    const { classes, database, onConnect, onModify, onRemove } = this.props;
    const { removeDialog } = this.state;

    return (
      <Frame
        headline={database.name}
        footer={(
          <Typography variant="caption">
            You can also{' '}
            <span className={classes.link} onClick={onModify}>modify</span>
            {' '}or <span className={classes.link} onClick={this.onRemove}>remove</span> the connection.
          </Typography>
        )}
      >
        <Link />
        <Button onClick={onConnect}>Connect</Button>
        <Dialog
          open={removeDialog}
          onClose={this.onDialogClose}
          aria-labelledby="remove-dialog-title"
          aria-describedby="remove-dialog-description"
        >
          <DialogTitle id="remove-dialog-title">Remove database connection?</DialogTitle>
          <DialogContent>
            <DialogContentText id="remove-dialog-description">
              Do you want to remove this database connection?<br />
              This means that it's configuration within app will be lost,{' '}
              however the database itself remains untouched.
            </DialogContentText>
          </DialogContent>
          <DialogActions>
            <Button onClick={this.onDialogClose} color="primary">
              Cancel
            </Button>
            <Button onClick={onRemove} color="primary" autoFocus={true}>
              Remove
            </Button>
          </DialogActions>
        </Dialog>
      </Frame>
    );
  }
}

export const DatabaseConnect = withStyles(styles)(DatabaseConnectComponent);
