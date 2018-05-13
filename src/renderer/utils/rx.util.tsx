import { Action } from 'redux';

const EMPTY_ACTION = 'EMPTY_ACTION';

export const emptyAction = (): Action<typeof EMPTY_ACTION> => ({ type: EMPTY_ACTION });

export const noEmptyActions = action => action.type !== EMPTY_ACTION;
