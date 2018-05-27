import { withStyles } from '@material-ui/core';
import React from 'react';
import { connect } from 'react-redux';
import { AppState } from '../../../../store/index';
import { select } from '../../../../utils/selector.util';
import { StyleProps } from '../../../../utils/styles.util';
import { getLayoutState, getSnackbarsState } from '../../store/index';
import { styles } from '../layout/layout.styles';
import { Snackbar } from './snackbar.component';

const mapStateToProps = (state: AppState) => ({
  snackbars: select(state, getLayoutState, getSnackbarsState),
});

type Props = ReturnType<typeof mapStateToProps>;

const SnackbarsComponent: React.SFC<Props & StyleProps<typeof styles>> = ({
  snackbars, classes,
}) => (
  <div className={classes.snackbarContainer}>
    {snackbars.map(snackbar => (
      <Snackbar key={snackbar.id} snackbar={snackbar} />
    ))}
  </div>
);

export const Snackbars = connect(mapStateToProps)(withStyles(styles)(SnackbarsComponent));
