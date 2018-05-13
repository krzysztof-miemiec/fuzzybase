import { Close } from '@material-ui/icons';
import { Button, IconButton, Snackbar as MaterialSnackbar, withStyles } from 'material-ui';
import React from 'react';
import { connect } from 'react-redux';
import { mapActions } from '../../../utils/redux.util';
import { StyleProps } from '../../../utils/styles.util';
import { SnackbarState } from '../store';
import { hideSnackbar } from '../store/layout.actions';
import { styles } from './layout.styles';

interface ComponentProps {
  snackbar: SnackbarState;
}

const mapDispatchToProps = mapActions({
  hideSnackbar,
});

type Props = ComponentProps & typeof mapDispatchToProps;

const SnackbarComponent: React.SFC<Props & StyleProps<typeof styles>> = ({
  snackbar: { id, isOpen, message, action, actionTitle }, dispatch, actions, classes,
}) => (
  <MaterialSnackbar
    open={isOpen}
    ContentProps={{
      'aria-describedby': 'message-id',
    }}
    className={classes.snackbar}
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
  withStyles(styles)(SnackbarComponent)
);
