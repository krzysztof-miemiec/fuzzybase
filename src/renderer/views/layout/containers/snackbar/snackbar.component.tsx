import { Button, IconButton, Snackbar as MaterialSnackbar } from '@material-ui/core';
import { Close } from '@material-ui/icons';
import React from 'react';
import { connect } from 'react-redux';
import { mapActions } from '../../../../../common/utils/redux.util';
import { SnackbarState } from '../../store';
import { hideSnackbar } from '../../store/layout.actions';
import { styles } from './snackbar.styles';

interface ComponentProps {
  snackbar: SnackbarState;
}

const mapDispatchToProps = mapActions({
  hideSnackbar,
});

type Props = ComponentProps & typeof mapDispatchToProps;

const SnackbarComponent: React.SFC<Props> = ({
  snackbar: { id, isOpen, message, action, actionTitle }, dispatch, actions,
}) => (
  <MaterialSnackbar
    open={isOpen}
    ContentProps={{
      'aria-describedby': 'message-id',
    }}
    className={styles.snackbar}
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
        onClick={() => actions.hideSnackbar(id)}
      >
        <Close />
      </IconButton>,
    ]}
  />
);

export const Snackbar = connect(null, mapDispatchToProps)(
  SnackbarComponent
);
