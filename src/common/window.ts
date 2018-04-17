import { BrowserWindow, BrowserWindowConstructorOptions } from 'electron';
import { handleError } from '../main/errors';

export enum WindowName {
  APP = 'app',
  BACKGROUND = 'background',
}

export function getIndexLocation() {
  return process.env.NODE_ENV === 'development'
    ? `http://localhost:${process.env.ELECTRON_WEBPACK_WDS_PORT}/`
    : `${__dirname}\\index.html`;
}

type RendererWindowOptions = {
  window?: BrowserWindowConstructorOptions,
  name: WindowName;
  show: boolean;
};

export function createRendererWindow({ window: windowOptions, name, show }: RendererWindowOptions) {
  const window = new BrowserWindow({
    show,
    ...windowOptions,
  });

  const args = {
    name,
  };

  const url = getIndexLocation();
  window.loadURL(`${url}#${encodeURIComponent(JSON.stringify(args))}`);
  window.webContents.on('crashed', (event, killed) => {
    if (!killed) {
      handleError(event);
    }
  });
  if (show) {
    window.webContents.on('did-finish-load', () => {
      window.show();
      window.focus();
    });
  }

  window.on('unresponsive', () => {
    handleError(new Error('An app window became unresponsive.'));
  });

  return window;
}
