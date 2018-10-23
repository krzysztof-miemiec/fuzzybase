import { ActionsObservable, combineEpics, StateObservable } from 'redux-observable';
import { concat, EMPTY, of } from 'rxjs';
import { switchMap } from 'rxjs/operators';
import { AppState } from '../../../renderer/store';
import { showSnackbar } from '../../../renderer/views/layout/store/layout.actions';
import { ConnectionStatusChangedAction, DB_ACTIONS, DbAction, getMetadata, GetMetadataAction } from './db.actions';
import { ConnectionStatus } from './db.state';
import {
  getFuzzyFunctions, getSearchPath,
  getTables,
  getUserName, processFuzzyFunctionsQueryResponse, processSearchPathQueryResponse,
  processTablesQueryResponse,
  processUserNameQueryResponse
} from './db.system.epics';

const connectionStatusChanged$ = (action$: ActionsObservable<DbAction>) => action$
  .ofType<ConnectionStatusChangedAction>(DB_ACTIONS.CONNECTION_STATUS_CHANGED)
  .pipe(
    switchMap(action => {
      if (action.error) {
        return of(showSnackbar(action.error, 'Error'));
      }
      switch (action.status) {
        case ConnectionStatus.CONNECTED:
          return concat(
            of(showSnackbar('Successfully connected to the database.')),
            of(getMetadata(action.connectionId))
          );
        case ConnectionStatus.DISCONNECTED:
          return of(showSnackbar('Disconnected from the database.'));
        case ConnectionStatus.CONNECTING:
          return of(showSnackbar('Connecting to the database'));
        default:
          return EMPTY;
      }
    })
  );

const getMetadata$ = (action$: ActionsObservable<DbAction>, state$: StateObservable<AppState>) => action$
  .ofType<GetMetadataAction>(DB_ACTIONS.GET_METADATA)
  .pipe(
    switchMap(action => concat(
      getUserName(action.connectionId),
      getTables(action.connectionId),
      getFuzzyFunctions(action.connectionId),
      getSearchPath(action.connectionId),
      processUserNameQueryResponse(action$, state$),
      processTablesQueryResponse(action$, state$),
      processFuzzyFunctionsQueryResponse(action$, state$),
      processSearchPathQueryResponse(action$, state$)
    ))
  );

export const appDbEpics = combineEpics(
  connectionStatusChanged$,
  getMetadata$
);
