import { ipcRenderer } from 'electron';
import { ActionsObservable } from 'redux-observable';
import { Observable, Subject } from 'rxjs';
import { ignoreElements, tap } from 'rxjs/operators';
import { CommunicationAction } from './actions';
import { Config } from './config';
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

  const destinationChannel = Config.WINDOW_NAME === WindowName.APP
    ? MAIN_BACKGROUND_CHANNEL
    : MAIN_APP_CHANNEL;

  const send = (action: CommunicationAction) => {
    ipcRenderer.send(destinationChannel, JSON.stringify(action));
  };

  const sendAction$ = (action$: ActionsObservable<any>) => action$
    .pipe(
      tap(action => {
        if (action._from !== Config.NAME) {
          send({ ...action, _from: Config.NAME });
        }
      }),
      ignoreElements()
    );

  return {
    listen,
    send,
    sendAction$,
  };
};
