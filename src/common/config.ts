import packageJson from '../../package.json';

const IS_MAIN = !(global as any).window;

export const Config = {
  NAME: packageJson.productName,
  PROCESS: IS_MAIN ? 'main' : 'app',
  IS_MAIN,
  IS_APP: !IS_MAIN,
  IS_DEV: process.env.NODE_ENV === 'development',
};
