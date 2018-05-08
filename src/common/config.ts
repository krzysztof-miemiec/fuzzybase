import packageJson from '../../package.json';

const args = ((global as any).window && JSON.parse(decodeURIComponent(window.location.hash.replace(/^#/, ''))))
  || {};

export const Config = {
  NAME: packageJson.productName,
  WINDOW_NAME: args.name,
  IS_DEV: process.env.NODE_ENV === 'development',
};
