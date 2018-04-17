import Raven from 'raven-js';

Raven
  .install();

export const handleError = error => {
  if (process.env.NODE_ENV === 'production') {
    Raven.captureException(error);
  } else {
    console.error(error);
  }
};
