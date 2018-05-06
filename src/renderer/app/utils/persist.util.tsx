import autoMergeLevel2 from 'redux-persist/lib/stateReconciler/autoMergeLevel2';
import storage from 'redux-persist/lib/storage';

export type Persist = {
  version: number;
  rehydrated: boolean;
};

export const defaultPersistConfig = {
  storage,
  stateReconciler: autoMergeLevel2,
};
