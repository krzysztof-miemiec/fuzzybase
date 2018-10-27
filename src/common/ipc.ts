import { ipcMain, ipcRenderer, IpcRenderer, WebContents } from 'electron';
import { Action } from 'redux';
import { ActionsObservable } from 'redux-observable';
import { Observable, Subject } from 'rxjs';
import { ignoreElements, tap } from 'rxjs/operators';
import { CommunicationAction } from './actions';
import { Config } from './config';

export const DIRECT_CHANNEL = 'direct';
const ipc = Config.IS_MAIN ? ipcMain : ipcRenderer;
let ipcReceiver: WebContents | IpcRenderer;
export const setIpcReceiver = (receiver?: WebContents | IpcRenderer) => ipcReceiver = receiver;

export const listen = (): Observable<Action<any>> => {
  const subject = new Subject<Action<any>>();
  ipc.on(DIRECT_CHANNEL, (_event, payload: CommunicationAction) => {
    subject.next(payload);
  });
  return subject.asObservable();
};

export const send = (action: Action<any>) => {
  if (!ipcReceiver) {
    throw new Error('Receiver not set yet.');
  }
  ipcReceiver.send(DIRECT_CHANNEL, action);
};

export const sendAction$ = (action$: ActionsObservable<any>) => action$
  .pipe(
    tap(action => {
      if (!action._from) {
        send({ ...action, _from: Config.PROCESS });
      }
    }),
    ignoreElements()
  );
