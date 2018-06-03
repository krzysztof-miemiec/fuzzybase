import Raven from 'raven-js';
import { Config } from '../common/config';

if (!Config.IS_DEV) {
  Raven.install();
}

export const handleError = error => {
  if (Config.IS_DEV) {
    console.error(error);
  } else {
    Raven.captureException(error);
  }
};
