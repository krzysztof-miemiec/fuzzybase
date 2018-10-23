import {
  Button,
  Dialog,
  DialogActions,
  DialogContent,
  DialogContentText,
  DialogTitle,
  LinearProgress
} from '@material-ui/core';
import React from 'react';
import { connect } from 'react-redux';
import { Subscription } from 'rxjs';
import { switchMap } from 'rxjs/operators';
import { getDatabase, getDatabasesState, installFuzzyExtension } from '../../../../../common/db/store/app';
import { R } from '../../../../../common/resources';
import { copy, showSaveDialog } from '../../../../../common/utils/files.util';
import { mapActions } from '../../../../../common/utils/redux.util';
import { select } from '../../../../../common/utils/selector.util';
import { AppState } from '../../../../store';

interface ComponentProps {
  databaseId: string;
  isOpen: boolean;
  onClose: () => void;
}

interface State {
  fileCopy?: {
    progress?: number
    error?: string;
  };
}

const mapStateToProps = (state: AppState, ownProps: ComponentProps) => ({
  database: select(state, getDatabasesState, getDatabase(ownProps.databaseId)),
});

const mapDispatchToProps = mapActions({
  installFuzzyExtension,
});

type Props =
  & ComponentProps
  & ReturnType<typeof mapStateToProps>
  & typeof mapDispatchToProps;

const isLocal = (host: string) => [
  '0.0.0.0', '127.0.0.1', 'localhost',
].some(part => host.indexOf(part) >= 0);

class InstallExtensionDialogComponent extends React.PureComponent<Props, State> {
  state: State = {};
  saveSubscription: Subscription;

  onCloseClick = () => {
    const { onClose } = this.props;
    this.clearSaveSubscription();
    this.setState({ fileCopy: undefined });
    onClose();
  };

  onInstallClick = () => {
    const { actions, databaseId } = this.props;
    actions.installFuzzyExtension(databaseId);
  };

  onSaveClick = () => {
    this.setState({ fileCopy: { progress: 0 } });
    this.saveSubscription = showSaveDialog({
      title: 'Save the Fuzzy extension package',
      buttonLabel: 'Save',
      filters: [{ name: 'Zip Archives', extensions: ['zip'] }],
    }).pipe(
      switchMap(filename => copy(R.string.fuzzyPackage, filename))
    ).subscribe(status => {
      this.setState({ fileCopy: { progress: status.progress } });
    }, error => {
      this.setState({ fileCopy: { error: error.message } });
    }, () => {
      this.clearSaveSubscription();
    });
  };

  clearSaveSubscription = () => {
    if (this.saveSubscription) {
      this.saveSubscription.unsubscribe();
      this.saveSubscription = null;
    }
  };

  componentWillUnmount() {
    this.clearSaveSubscription();
  }

  renderRemote = () => (
    <>
      <DialogTitle id="alert-dialog-title">
        Can't install Fuzzy extension on a non-local database.
      </DialogTitle>
      <DialogContent>
        <DialogContentText id="alert-dialog-description">
          It seems that the currently selected database is a remote one.
          Unfortunately, installing an extension is not possible on remote database.
          You can still save the package with extension and install it manually using <pre>make add</pre> command.
        </DialogContentText>
      </DialogContent>
      <DialogActions>
        <Button onClick={this.onCloseClick} color="primary">
          Close
        </Button>
        <Button onClick={this.onSaveClick} color="primary" autoFocus={true}>
          Get extension package
        </Button>
      </DialogActions>
    </>
  );

  renderFileCopy = () => {
    const { fileCopy: { progress, error } } = this.state;

    return (
      <>
        <DialogTitle id="alert-dialog-title">
          Do you wish to install Fuzzy extension locally?
        </DialogTitle>
        <DialogContent>
          <LinearProgress variant="determinate" value={progress * 100} />
          <DialogContentText id="alert-dialog-description">
            {error ? (
              error
            ) : (
              'Extracting Fuzzybase package...'
            )}
          </DialogContentText>
        </DialogContent>
        <DialogActions>
          <Button onClick={this.onCloseClick} color="primary">
            Abort
          </Button>
        </DialogActions>
      </>
    );
  };

  renderInstallation = (status: string) => (
    <>
      <DialogTitle id="alert-dialog-title">
        Installing Fuzzybase extension...
      </DialogTitle>
      <DialogContent>
        <LinearProgress variant="indeterminate" />
        <DialogContentText id="alert-dialog-description">
          {status}
        </DialogContentText>
      </DialogContent>
      <DialogActions>
        <Button onClick={this.onCloseClick} color="primary">
          Abort
        </Button>
      </DialogActions>
    </>
  );

  renderLocal = () => (
    <>
      <DialogTitle id="alert-dialog-title">
        Do you wish to install Fuzzy extension locally?
      </DialogTitle>
      <DialogContent>
        <DialogContentText id="alert-dialog-description">
          Allow Fuzzybase to install the Fuzzy extension to local PostgreSQL database.
          <br /><br />
          We'll try to automatically download all required packages that may be required
          to build and install the extension.
        </DialogContentText>
      </DialogContent>
      <DialogActions>
        <Button onClick={this.onCloseClick} color="primary">
          Cancel
        </Button>
        <Button onClick={this.onInstallClick} color="primary" autoFocus={true}>
          Install
        </Button>
      </DialogActions>
    </>
  );

  render() {
    const { isOpen, onClose, database } = this.props;
    const { fileCopy } = this.state;
    const isInstallationInProgress = false;

    return (
      <Dialog
        open={isOpen}
        onClose={onClose}
      >
        {isLocal(database.host) ? (
          isInstallationInProgress ? this.renderInstallation('blah') : this.renderLocal()
        ) : (
          fileCopy ? this.renderFileCopy() : this.renderRemote()
        )}
      </Dialog>
    );
  }
}

export const InstallExtensionDialog = connect(mapStateToProps, mapDispatchToProps)(InstallExtensionDialogComponent);