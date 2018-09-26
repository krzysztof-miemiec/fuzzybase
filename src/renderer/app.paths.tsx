export const PATHS = {
  HOME: '/',
  DATABASES: '/databases',
  DATABASE: (databaseId: string = 'new') => `/database/${databaseId}/`,
  QUERY: (
    databaseId = ':databaseId', connectionId = ':connectionId', queryId = ':queryId'
  ) => `/database/${databaseId}/connection/${connectionId}/query/${queryId}`,
};
