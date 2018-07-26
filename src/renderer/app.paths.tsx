export const PATHS = {
  HOME: '/',
  DATABASES: '/databases',
  DATABASE: (databaseId: string = 'new') => `/database/${databaseId}/`,
  QUERY: (
    databaseId: string, connectionId: string, queryId: string
  ) => `/database/${databaseId}/connection/${connectionId}/query/${queryId}`,
};
