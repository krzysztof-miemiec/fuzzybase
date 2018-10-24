import { omit } from 'lodash';
import { Reducer } from 'redux';
import { PersistConfig, persistReducer } from 'redux-persist';
import { defaultPersistConfig } from '../../../renderer/utils/persist.util';
import { arrayCollectionReducer, objectCollectionReducer } from '../../utils/redux.util';
import { DB_ACTIONS, DbAction } from './db.actions';
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
    case DB_ACTIONS.SET_QUERY: {
      return {
        ...state,
        queries: objectCollectionReducer(state.queries).put(action.queryId, query => ({
          ...query,
          id: action.queryId,
          query: action.query,
          isSystemQuery: action.isSystemQuery,
        })),
      };
    }
    case DB_ACTIONS.CLOSE_QUERY: {
      return {
        ...state,
        queries: objectCollectionReducer(state.queries).remove(action.queryId),
      };
    }
    case DB_ACTIONS.QUERY: {
      return {
        ...state,
        queries: objectCollectionReducer(state.queries).put(action.queryId, () => ({
          id: action.queryId,
          start: Date.now(),
          end: 0,
          query: action.query,
          result: null,
          error: null,
          isSystemQuery: action.isSystemQuery,
        })),
      };
    }
    case DB_ACTIONS.QUERY_RESULT: {
      return {
        ...state,
        queries: objectCollectionReducer(state.queries).put(action.queryId, query => ({
          ...query,
          end: Date.now(),
          result: action.result,
          error: action.error,
        })),
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
      return {
        ...state,
        databases: arrayCollectionReducer(state.databases, db => db.id)
          .put(action.database.id, () => action.database),
      };
    }
    case DB_ACTIONS.SET_METADATA: {
      const metadata = omit(action, ['type', 'databaseId']);
      return {
        ...state,
        databases: arrayCollectionReducer(state.databases, db => db.id)
          .put(action.databaseId, db => {
            const database = {
              ...db,
              meta: {
                ...db.meta,
                ...metadata,
              },
            };
            database.meta.searchPath = database.meta.searchPath
              ? database.meta.searchPath.map(path => path
                .replace(/\$user/g, database.meta.user)
                .trim()
              )
              : undefined;
            return database;
          }),
      };
    }
    case DB_ACTIONS.REMOVE_DATABASE:
      return {
        ...state,
        databases: arrayCollectionReducer(state.databases, db => db.id)
          .remove(action.databaseId),
      };
    case DB_ACTIONS.CONNECTION_STATUS_CHANGED:
    case DB_ACTIONS.QUERY:
    case DB_ACTIONS.SET_QUERY:
    case DB_ACTIONS.CLOSE_QUERY:
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

export const reducer: Reducer<DbState> = persistReducer(persistConfig, baseReducer) as any;
