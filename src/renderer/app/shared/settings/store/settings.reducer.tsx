import { PersistConfig, persistReducer } from 'redux-persist';
import { defaultPersistConfig } from '../../../utils/persist.util';
import { select } from '../../../utils/selector.util';
import { SETTINGS_ACTIONS, SettingsAction } from './settings.actions';
import { getDatabase } from './settings.selectors';
import { initialState, SettingsState } from './settings.state';

export const persistConfig: PersistConfig = {
  key: 'settings',
  ...defaultPersistConfig,
};

const baseReducer = (state: void | SettingsState, action: SettingsAction): SettingsState => {
  if (!state) {
    state = initialState;
  }
  switch (action.type) {
    case SETTINGS_ACTIONS.SET_DATABASE:
      const databaseExists = !!select(state, getDatabase(action.database.id));
      return {
        ...state,
        databases: databaseExists
          ? state.databases.map(
            database => database.id === action.database.id ? action.database : database
          )
          : [...state.databases, action.database],
      };
    case SETTINGS_ACTIONS.REMOVE_DATABASE:
      return {
        ...state,
        databases: state.databases.filter(database => database.id !== action.databaseId),
      };
    default:
      return {
        ...state,
      };
  }
};

export const reducer = persistReducer(persistConfig, baseReducer);
