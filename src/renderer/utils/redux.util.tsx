import { Dispatch } from 'redux';

export const mapActions: <T extends object>(actions: T) => {
  actions: T, dispatch: Dispatch<any>
} = (actions => dispatch => {
  const result: any = { actions: {}, dispatch };
  for (const element in actions) {
    if (actions.hasOwnProperty(element)) {
      result.actions[element] = (...args) => dispatch(actions[element](...args));
    }
  }
  return result;
}) as any;

export const createAction = <Type extends string, Payload extends object>(
  type: Type, payload?: Payload
): { type: Type } & Payload => ({
  type,
  ...payload as object,
} as any);
