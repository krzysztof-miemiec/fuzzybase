import { ActionsObservable, combineEpics, StateObservable } from 'redux-observable';
import { concat, EMPTY, of } from 'rxjs';
import { filter, switchMap, withLatestFrom } from 'rxjs/operators';
import { AppState } from '../../../renderer/store';
import { showSnackbar } from '../../../renderer/views/layout/store/layout.actions';
import { select } from '../../utils/selector.util';
import {
  ConnectionStatusChangedAction,
  DB_ACTIONS,
  DbAction,
  getMetadata,
  GetMetadataAction,
  InstallationStage,
  InstallFuzzyExtensionAction,
  setMetadata
} from './db.actions';
import { getConnection, getDatabasesState } from './db.selectors';
import { ConnectionStatus } from './db.state';
import {
  createFuzzyExtension,
  getFuzzyFunctions,
  getSearchPath,
  getTables,
  getUserName,
  processCreateFuzzyExtensionResponse,
  processFuzzyFunctionsQueryResponse,
  processSearchPathQueryResponse,
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

const installExtension$ = (
  action$: ActionsObservable<DbAction>,
  state$: StateObservable<AppState>
) => action$
  .ofType<InstallFuzzyExtensionAction>(DB_ACTIONS.INSTALL_FUZZY_EXTENSION)
  .pipe(
    filter(action => action.stage === InstallationStage.CREATE_EXTENSION
      || action.stage === InstallationStage.RECREATE_EXTENSION),
    withLatestFrom(state$),
    switchMap(([action, state]) => concat(
      of(setMetadata({
        databaseId: select(state, getDatabasesState, getConnection(action.connectionId)).databaseId,
        extensionInstallation: { status: 'progress', message: 'Adding extension to the database...' },
      })),
      createFuzzyExtension(action.connectionId),
      processCreateFuzzyExtensionResponse(action$, state$, action.stage === InstallationStage.CREATE_EXTENSION)
    ))
  );

export const appDbEpics = combineEpics(
  connectionStatusChanged$,
  getMetadata$,
  installExtension$
);
