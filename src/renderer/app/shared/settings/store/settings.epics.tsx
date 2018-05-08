import { ActionsObservable, combineEpics } from 'redux-observable';
import { map } from 'rxjs/operators';
import {
  removePostgresConfiguration,
  setPostgresConfiguration
} from '../../../../background/postgres/postgres.actions';
import { RemoveDatabaseAction, SetDatabaseAction, SETTINGS_ACTIONS, SettingsAction } from './settings.actions';

const onSetDatabase$ = (action$: ActionsObservable<SettingsAction>) => action$
  .ofType<SetDatabaseAction>(SETTINGS_ACTIONS.SET_DATABASE)
  .pipe(
    map(action => setPostgresConfiguration(action.database))
  );

const onRemoveDatabase$ = (action$: ActionsObservable<SettingsAction>) => action$
  .ofType<RemoveDatabaseAction>(SETTINGS_ACTIONS.REMOVE_DATABASE)
  .pipe(
    map(action => removePostgresConfiguration(action.databaseId))
  );

export const settingsEpics = combineEpics<any>(
  onSetDatabase$,
  onRemoveDatabase$
);
