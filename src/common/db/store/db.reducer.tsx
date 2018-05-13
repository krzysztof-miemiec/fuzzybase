import { PersistConfig, persistReducer } from 'redux-persist';
import { defaultPersistConfig } from '../../../renderer/utils/persist.util';
import { select } from '../../../renderer/utils/selector.util';
import { DB_ACTIONS, DbAction } from './db.actions';
import { getDatabase } from './db.selectors';
import { ConnectionStatus, DatabaseConnectionState, DbState, initialState } from './db.state';

export const persistConfig: PersistConfig = {
  key: 'databases',
  blacklist: ['connections'],
  ...defaultPersistConfig,
};

const connectionReducer = (state: void | DatabaseConnectionState, action: DbAction): DatabaseConnectionState => {
  if (!state) {
    state = {
      clientId: '',
      connectionId: '',
      status: ConnectionStatus.DISCONNECTED,
      queries: {},
    };
  }
  switch (action.type) {
    case DB_ACTIONS.CONNECTION_STATUS_CHANGED: {
      return {
        ...state,
        clientId: action.clientId,
        connectionId: action.connectionId,
        status: action.status,
        error: action.error,
      };
    }
    case DB_ACTIONS.QUERY: {
      return {
        ...state,
        queries: {
          ...state.queries,
          [action.queryId]: {
            id: action.queryId,
            start: Date.now(),
            end: 0,
            query: action.query,
            result: null,
          },
        },
      };
    }
    case DB_ACTIONS.QUERY_RESULT: {
      return {
        ...state,
        queries: {
          ...state.queries,
          [action.queryId]: {
            ...state.queries[action.queryId],
            end: Date.now(),
            result: action.result,
          },
        },
      };
    }
    default:
      return state;
  }
};

const baseReducer = (state: void | DbState, action: DbAction): DbState => {
  if (!state) {
    state = initialState;
  }
  switch (action.type) {
    case DB_ACTIONS.SET_DATABASE:
      const databaseExists = !!select(state, getDatabase(action.database.id));
      return {
        ...state,
        databases: databaseExists
          ? state.databases.map(
            database => database.id === action.database.id ? action.database : database
          )
          : [...state.databases, action.database],
      };
    case DB_ACTIONS.REMOVE_DATABASE:
      return {
        ...state,
        databases: state.databases.filter(database => database.id !== action.databaseId),
      };
    case DB_ACTIONS.CONNECTION_STATUS_CHANGED:
    case DB_ACTIONS.QUERY:
    case DB_ACTIONS.QUERY_RESULT: {
      const connection = connectionReducer(state.connections[action.connectionId], action);
      const connections = { ...state.connections };
      if (connection.status === ConnectionStatus.DISCONNECTED) {
        delete connections[action.connectionId];
        return {
          ...state,
          connections,
        };
      }
      return {
        ...state,
        connections: {
          ...state.connections,
          [action.connectionId]: connection,
        },
      };
    }
    default:
      return {
        ...state,
      };
  }
};

export const reducer = persistReducer(persistConfig, baseReducer);
