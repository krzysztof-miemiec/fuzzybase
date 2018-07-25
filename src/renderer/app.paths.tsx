export const PATHS = {
  HOME: '/',
  DATABASES: '/databases',
  DATABASE: (databaseId: string = 'new') => `/database/${databaseId}/`,
  CONNECTION: (databaseId: string, connectionId: string) => `/database/${databaseId}/connection/${connectionId}`,
};
