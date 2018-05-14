export const PATHS = {
  HOME: '/',
  DATABASES: '/databases',
  DATABASE: (key: string) => `/database/${key}`,
  CONNECTION: (key: string) => `/connection/${key}`,
};
