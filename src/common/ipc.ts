import { ipcRenderer } from 'electron';
import { Observable, Subject } from 'rxjs';
import { CommunicationAction } from './actions';
import { WindowName } from './window';

export const MAIN_APP_CHANNEL = 'app';
export const MAIN_BACKGROUND_CHANNEL = 'background';
export const DIRECT_CHANNEL = 'direct';

export const registerForIPC = () => {
  const listen = (): Observable<CommunicationAction> => {
    const subject = new Subject<CommunicationAction>();
    ipcRenderer.on(DIRECT_CHANNEL, (_event, payloadString) => {
      const payload: CommunicationAction = JSON.parse(payloadString);
      subject.next(payload);
    });
    return subject.asObservable();
  };

  const destinationChannel = process.env.windowName === WindowName.APP
    ? MAIN_BACKGROUND_CHANNEL
    : MAIN_APP_CHANNEL;

  const send = (action: CommunicationAction) => {
    ipcRenderer.send(destinationChannel, JSON.stringify(action));
  };

  return {
    listen,
    send,
  };
};
