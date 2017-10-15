import { actionCreatorVoid } from './helpers';

export const increment = actionCreatorVoid('INCREMENT_COUNTER');
export const decrement = actionCreatorVoid('DECREMENT_COUNTER');

export function incrementIfOdd() {
  return (dispatch: (f: any) => any, getState: () => any) => {
    const { counter } = getState();

    if (counter % 2 === 0) {
      return;
    }

    dispatch(increment());
  };
}

export function incrementAsync(delay: number = 1000) {
  return (dispatch: (f: any) => void) => {
    setTimeout(() => {
      dispatch(increment());
    }, delay);
  };
}
