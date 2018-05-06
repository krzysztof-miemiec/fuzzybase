import Raven from 'raven-js';
import { Log } from '../common/log';

Raven.install();

export const handleError = error => {
  if (process.env.NODE_ENV === 'production') {
    Raven.captureException(error);
  } else {
    Log.e(error);
  }
};
