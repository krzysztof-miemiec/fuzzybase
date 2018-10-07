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

export const objectCollectionReducer = <T extends any>(object: Record<string, T>) => ({
  put: (key: string, newElementFunction: (previous: T) => T) => {
    return {
      ...object,
      [key]: newElementFunction(object[key]),
    };
  },
  remove: (key: string) => {
    const newObject = { ...object };
    delete newObject[key];
    return newObject;
  },
});

export const arrayCollectionReducer = <T extends any, K extends any>(
  array: T[],
  getElementKey: (element: T) => K
) => ({
  put: (key: K, newElementFunction: (previous: T) => T) => {
    const newArray = [...array];
    const index = array.findIndex(element => getElementKey(element) === key);
    if (index < 0) {
      newArray.push(newElementFunction(undefined));
    } else {
      newArray[index] = newElementFunction(array[index]);
    }
    return newArray;
  },
  remove: (key: K) => {
    return array.filter(element => getElementKey(element) !== key);
  },
});
