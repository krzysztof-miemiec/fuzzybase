import { PersistConfig, persistReducer } from 'redux-persist';
import uuid from 'uuid/v4';
import { defaultPersistConfig } from '../../../utils/persist.util';
import { SETTINGS_ACTIONS, SettingsAction } from './settings.actions';
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
    case SETTINGS_ACTIONS.ADD_DATABASE:
      return {
        ...state,
        databases: [...state.databases, { ...action.database, id: uuid() }],
      };
    case SETTINGS_ACTIONS.UPDATE_DATABASE:
      return {
        ...state,
        databases: state.databases.map(database => database.id === action.databaseId
          ? action.database
          : database),
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
