import { ipcRenderer } from 'electron';
import { BehaviorSubject } from 'rxjs/BehaviorSubject';
import { Observable } from 'rxjs/Observable';

export enum CommunicationActionType {
  READY = 'READY',
}

interface CommunicationAction {
  type: CommunicationActionType;
}

const DIRECT_CHANNEL = 'direct';
const MAIN_CHANNEL = 'main';

export const registerForIPC = () => {
  let backgroundWindowId: number;
  let appWindowId: number;
  let hasWindowIds: boolean = false;

  ipcRenderer.on(MAIN_CHANNEL, (_event, payload) => {
    backgroundWindowId = payload.backgroundWindowId;
    appWindowId = payload.appWindowId;
    hasWindowIds = true;
    ipcRenderer.send(MAIN_CHANNEL, {type: CommunicationActionType.READY});
  });

  return {
    listen: (): Observable<CommunicationAction> => {
      const subject = new BehaviorSubject<CommunicationAction>(null);
      ipcRenderer.on(DIRECT_CHANNEL, (_event, payload) => {
        subject.next(payload);
      });
      return subject.asObservable();
    },
    sendToApp: (action: CommunicationAction) => {
      if (!hasWindowIds) {
        throw new Error('Window IDs are not present.');
      }
      ipcRenderer.sendTo(appWindowId, DIRECT_CHANNEL, action);
    },
    sendToBackground: (action: CommunicationAction) => {
      if (!hasWindowIds) {
        throw new Error('Window IDs are not present.');
      }
      ipcRenderer.sendTo(backgroundWindowId, DIRECT_CHANNEL, action);
    },
  };
};
