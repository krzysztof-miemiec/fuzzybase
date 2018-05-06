import { Close } from '@material-ui/icons';
import { Button, IconButton, Snackbar as MaterialSnackbar } from 'material-ui';
import React from 'react';
import { connect } from 'react-redux';
import { AppState } from '../../../store';
import { mapActions } from '../../../utils/redux.util';
import { select } from '../../../utils/selector.util';
import { getLayoutState, getSnackbarState } from '../store';
import { hideSnackbar } from '../store/layout.actions';

const mapStateToProps = (state: AppState) => ({
  snackbar: select(state, getLayoutState, getSnackbarState),
});

const mapDispatchToProps = mapActions({
  hideSnackbar,
});

type Props = ReturnType<typeof mapStateToProps> & typeof mapDispatchToProps;

const SnackbarComponent: React.SFC<Props> = ({
  snackbar: { isOpen, message, action, actionTitle }, dispatch, actions,
}) => (
  <MaterialSnackbar
    anchorOrigin={{
      vertical: 'bottom',
      horizontal: 'left',
    }}
    open={isOpen}
    autoHideDuration={6000}
    ContentProps={{
      'aria-describedby': 'message-id',
    }}
    message={<span id="message-id">{message}</span>}
    action={[
      action && <Button
        key="action"
        color="secondary"
        size="small"
        onClick={() => dispatch(action)}
      >
        {actionTitle}
      </Button>,
      <IconButton
        key="close"
        aria-label="Close"
        color="inherit"
        onClick={actions.hideSnackbar}
      >
        <Close />
      </IconButton>,
    ]}
  />
);

export const Snackbar = connect(mapStateToProps, mapDispatchToProps)(SnackbarComponent);
