// eslint-disable global-require
import * as logger from 'electron-log';

console.log = (...args: any[]) => logger.log(args);
console.info = (...args: any[]) => logger.info(args);
console.debug = (...args: any[]) => logger.debug(args);
console.warn = (...args: any[]) => logger.warn(args);
console.error = (...args: any[]) => logger.error(args);
logger.transports.console.level = false;
logger.transports.rendererConsole.level = 'verbose';
// logger.transports.rendererConsole.format = msg => msg.data;

import { app, BrowserWindow, Menu } from 'electron';
import { Config } from '../common/config';
import { listen, setIpcReceiver } from '../common/ipc';
import { createRendererWindow } from '../common/window';
import { handleError } from './errors';
import { store } from './main.store';
import { setMenu } from './menu';

let appWindow: BrowserWindow = null;

const installExtensions = (): Promise<void> => {
  if (process.env.NODE_ENV === 'development') {
    console.log('Development environment found. Initializing devtools.');
    const { default: installExtension, REACT_DEVELOPER_TOOLS, REDUX_DEVTOOLS } = require('electron-devtools-installer');

    const extensions = [
      REACT_DEVELOPER_TOOLS,
      REDUX_DEVTOOLS,
    ];

    const forceDownload = !!process.env.UPGRADE_EXTENSIONS;
    return Promise.all(extensions.map(extension => installExtension(extension.id, forceDownload)))
      .then(() => void 0);
  }
  return Promise.resolve();
};

process.on('uncaughtException', error => {
  handleError(error);
});

const createAppWindow = () => {
  appWindow = createRendererWindow({
    window: {
      width: 1024,
      height: 728,
      title: Config.NAME,
      titleBarStyle: Config.IS_MAC ? 'hidden' : 'default',
    },
    show: true,
  });
  setIpcReceiver(appWindow.webContents);
  listen().subscribe(action => store.dispatch(action));
  setMenu(appWindow);
  appWindow.on('closed', () => {
    appWindow = null;
  });

  if (!Config.IS_DEV) {
    // Setup production app
    const sourceMapSupport = require('source-map-support');
    sourceMapSupport.install();
  } else {
    // Setup development app
    appWindow.webContents.openDevTools();
    appWindow.webContents.on('devtools-opened', () => {
      setImmediate(() => appWindow.focus());
    });
    appWindow.webContents.on('context-menu', (_e, props) => {
      const { x, y } = props;
      Menu.buildFromTemplate([
        {
          label: 'Inspect element',
          click: () => appWindow.webContents.inspectElement(x, y),
        },
      ]).popup({ window: appWindow });
    });
    require('electron-debug')();
    const path = require('path');
    const p = path.join(__dirname, './node_modules');
    require('module').globalPaths.push(p);
  }
};

app.on('ready', () => installExtensions().then(() => {
  createAppWindow();
}));

app.on('activate', () => {
  if (appWindow === null) {
    createAppWindow();
  }
});
app.on('window-all-closed', () => {
  if (!Config.IS_MAC) {
    app.quit();
  }
});
