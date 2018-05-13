import { ipcRenderer } from 'electron';
import { Subscription } from 'rxjs';
import { listen, sendAction$, setIpcReceiver } from '../../common/ipc';
import { store } from '../app.store';

export { send } from '../../common/ipc';

setIpcReceiver(ipcRenderer);

export module IPCManager {
  let subscription: Subscription;
  export const subscribe = () => {
    if (subscription) {
      return;
    }
    subscription = listen().subscribe(action => store.dispatch(action));
  };
  export const unsubscribe = () => {
    if (!subscription) {
      return;
    }
    subscription.unsubscribe();
    subscription = undefined;
  };
  export const sendActionEpic = sendAction$;
}
