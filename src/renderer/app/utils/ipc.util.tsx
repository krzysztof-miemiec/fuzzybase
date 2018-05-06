import { Subscription } from 'rxjs';
import { CommunicationActionType } from '../../../common/actions';
import { registerForIPC } from '../../../common/ipc';
import { store } from '../app.store';
import { handleLogAction } from './log.util';

export const { send: ipcSend, listen } = registerForIPC();

export module IPCManager {
  let subscription: Subscription;
  export const subscribe = () => {
    if (subscription) {
      return;
    }
    subscription = listen().subscribe(action => {
      switch (action.type) {
        case CommunicationActionType.LOG:
          handleLogAction(action);
          break;
        default:
          store.dispatch(action);
          break;
      }
    });
  };
  export const unsubscribe = () => {
    if (!subscription) {
      return;
    }
    subscription.unsubscribe();
    subscription = undefined;
  };
  export const send = ipcSend;
}
