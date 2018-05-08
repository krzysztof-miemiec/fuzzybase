import * as redux from 'redux';

declare module 'redux' {
  // TODO Remove the hack for Redux 4 Devtools
  export type GenericStoreEnhancer = any;
}
