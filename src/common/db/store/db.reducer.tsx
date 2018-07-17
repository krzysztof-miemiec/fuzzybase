import { PersistConfig, persistReducer } from 'redux-persist';
import { defaultPersistConfig } from '../../../renderer/utils/persist.util';
import { select } from '../../../renderer/utils/selector.util';
import { DB_ACTIONS, DbAction } from './db.actions';
import { getDatabaseIndex } from './db.selectors';
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
            error: null,
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
            error: action.error,
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
    case DB_ACTIONS.SET_DATABASE: {
      const databaseIndex = select(state, getDatabaseIndex(action.database.id));
      const databases = [...state.databases];
      if (databaseIndex < 0) {
        databases.push(action.database);
      } else {
        databases[databaseIndex] = action.database;
      }
      return { ...state, databases };
    }
    case DB_ACTIONS.SET_TABLES_METADATA: {
      const databaseIndex = select(state, getDatabaseIndex(action.databaseId));
      if (databaseIndex < 0) {
        return state;
      }
      const databases = [...state.databases];
      const database = databases[databaseIndex];
      databases[databaseIndex] = {
        ...database,
        meta: {
          ...database.meta,
          tables: action.tables,
        },
      };
      return { ...state, databases };
    }
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
      return state;
  }
};

export const reducer = persistReducer(persistConfig, baseReducer);
