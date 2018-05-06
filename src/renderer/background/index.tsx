import { log, LogMethod, LogSource } from '../../common/actions';
import { store } from './background.store';
import { listen, send } from './ipc';

console.log = (message: string, optionalParams?: any) =>
  send(log(LogSource.BACKGROUND, LogMethod.LOG, message, optionalParams));
console.warn = (message: string, optionalParams?: any) =>
  send(log(LogSource.BACKGROUND, LogMethod.WARN, message, optionalParams));
console.error = (message: string, optionalParams?: any) =>
  send(log(LogSource.BACKGROUND, LogMethod.ERROR, message, optionalParams));

listen().subscribe(action => {
  store.dispatch(action);
});
