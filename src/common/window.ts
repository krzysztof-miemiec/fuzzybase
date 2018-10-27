import { BrowserWindow, BrowserWindowConstructorOptions } from 'electron';
import * as path from 'path';
import { format as formatUrl } from 'url';
import { handleError } from '../main/errors';
import { Config } from './config';

export function getIndexLocation() {
  return Config.IS_DEV
    ? `http://localhost:${process.env.ELECTRON_WEBPACK_WDS_PORT}/`
    : formatUrl({
      pathname: path.join(__dirname, 'index.html'),
      protocol: 'file',
      slashes: true,
    });
}

type RendererWindowOptions = {
  window?: BrowserWindowConstructorOptions,
  show: boolean;
};

export function createRendererWindow({ window: windowOptions, show }: RendererWindowOptions) {
  const window = new BrowserWindow({
    show,
    ...windowOptions,
  });

  const url = getIndexLocation();
  window.loadURL(url);
  window.webContents.on('crashed', (event, killed) => {
    if (!killed) {
      handleError(event);
    }
  });
  if (show) {
    window.webContents.on('did-finish-load', () => {
      window.show();
    });
  }

  window.on('unresponsive', () => {
    handleError(new Error('An app window became unresponsive.'));
  });

  return window;
}
