import { ActionsObservable, combineEpics } from 'redux-observable';
import { filter, map } from 'rxjs/operators';
import { showSnackbar } from '../../../renderer/scenes/layout/store/layout.actions';
import { noEmptyActions } from '../../../renderer/utils/rx.util';
import { ConnectionStatusChangedAction, DB_ACTIONS, DbAction } from './db.actions';
import { ConnectionStatus } from './db.state';

const connectionStatusChanged$ = (action$: ActionsObservable<DbAction>) => action$
  .ofType<ConnectionStatusChangedAction>(DB_ACTIONS.CONNECTION_STATUS_CHANGED)
  .pipe(
    map(action => {
      if (action.error) {
        return showSnackbar(action.error, 'Error');
      }
      switch (action.status) {
        case ConnectionStatus.CONNECTED:
          return showSnackbar('Successfully connected to the database.');
        case ConnectionStatus.DISCONNECTED:
          return showSnackbar('Disconnected from the database.');
        case ConnectionStatus.CONNECTING:
        default:
          return showSnackbar('Connecting to the database');
      }
    }),
    filter(noEmptyActions)
  );

export const appDbEpics = combineEpics(
  connectionStatusChanged$
);
