import Raven from 'raven-js';
import { Config } from '../common/config';

if (!Config.IS_DEV) {
  Raven.install();
}

export const handleError = error => {
  console.error(error);
  if (!Config.IS_DEV) {
    Raven.captureException(error);
  }
};
