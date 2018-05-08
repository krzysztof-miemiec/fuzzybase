import { ipcRenderer } from 'electron';
import { isBoolean, isNumber, isString } from 'lodash';
import IpcMain = Electron.IpcMain;
import { Config } from './config';

const isMainProcess = process.type === 'browser';

const stringify = (data: any) => {
  if (isBoolean(data) || isNumber(data) || isString(data)) {
    return data.toString();
  } else {
    return JSON.stringify(data);
  }
};

export const Log = {
  d(message: any, window?: string) {
    if (isMainProcess) {
      console.log((window ? window + ': ' : '') + stringify(message));
    } else {
      ipcRenderer.send('Log.d', { window: Config.WINDOW_NAME, message: stringify(message) });
    }
  },
  w(message: any, window?: string) {
    if (isMainProcess) {
      console.warn((window ? window + ': ' : '') + stringify(message));
    } else {
      ipcRenderer.send('Log.w', { window: Config.WINDOW_NAME, message: stringify(message) });
    }
  },
  e(message: any, window?: string) {
    if (isMainProcess) {
      console.error((window ? window + ': ' : '') + stringify(message));
    } else {
      ipcRenderer.send('Log.e', { window: Config.WINDOW_NAME, message: stringify(message) });
    }
  },
};

export const handleLogs = (ipc: IpcMain) => {
  ipc.on('Log.d', (_event, payload) => Log.d(payload.message, payload.window));
  ipc.on('Log.w', (_event, payload) => Log.w(payload.message, payload.window));
  ipc.on('Log.e', (_event, payload) => Log.e(payload.message, payload.window));
};
