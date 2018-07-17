export const PATHS = {
  HOME: '/',
  DATABASES: '/databases',
  DATABASE: (key: string = 'new') => `/database/${key}`,
  CONNECTION: (key: string) => `/connection/${key}`,
};
