import React from 'react';
import { connect } from 'react-redux';
import { select } from '../../../../../common/utils/selector.util';
import { AppState } from '../../../../store';
import { getLayoutState, getSnackbarsState } from '../../store';
import { Snackbar } from './snackbar.component';
import { styles } from './snackbar.styles';

const mapStateToProps = (state: AppState) => ({
  snackbars: select(state, getLayoutState, getSnackbarsState),
});

type Props = ReturnType<typeof mapStateToProps>;

const SnackbarsComponent: React.SFC<Props> = ({
  snackbars,
}) => (
  <div className={styles.container}>
    {snackbars.map(snackbar => (
      <Snackbar key={snackbar.id} snackbar={snackbar} />
    ))}
  </div>
);

export const Snackbars = connect(mapStateToProps)(SnackbarsComponent);
