import { isBoolean, isNumber, isString } from 'lodash';
import { LogAction } from '../../../common/actions';

const stringify = (data: any): string => (isBoolean(data) || isNumber(data) || isString(data))
  ? data.toString()
  : '';

export const handleLogAction = (action: LogAction) => {
  const originalMessageString = stringify(action.message);
  const message = `${action.source}: ${originalMessageString}`;
  if (!action.optionalParams) {
    action.optionalParams = [];
  }
  if (!originalMessageString) {
    action.optionalParams.unshift(action.message);
  }
  console[action.method](message, ...action.optionalParams);
};
