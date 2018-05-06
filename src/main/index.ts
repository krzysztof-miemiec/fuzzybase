// eslint-disable global-require
import { app, ipcMain, Menu } from 'electron';
import { DIRECT_CHANNEL, MAIN_APP_CHANNEL, MAIN_BACKGROUND_CHANNEL } from '../common/ipc';
import { handleLogs, Log } from '../common/log';
import { createRendererWindow, WindowName } from '../common/window';
import { handleError } from './errors';
import { setMenu } from './menu';
import BrowserWindow = Electron.BrowserWindow;

let appWindow: BrowserWindow = null;
let backgroundWindow: BrowserWindow = null;

const installExtensions = (): Promise<void> => {
  if (process.env.NODE_ENV === 'development') {
    Log.d('Development environment found. Initializing devtools.');
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

app.on('ready', () => installExtensions().then(() => {
  handleLogs(ipcMain);
  backgroundWindow = createRendererWindow({
    name: WindowName.BACKGROUND,
    show: false,
  });
  appWindow = createRendererWindow({
    window: {
      width: 1024,
      height: 728,
    },
    show: true,
    name: WindowName.APP,
  });
  ipcMain.on(MAIN_APP_CHANNEL, (_event, payload) => {
    appWindow.webContents.send(DIRECT_CHANNEL, payload);
  });
  ipcMain.on(MAIN_BACKGROUND_CHANNEL, (_event, payload) => {
    backgroundWindow.webContents.send(DIRECT_CHANNEL, payload);
  });
  setMenu(appWindow);
  appWindow.on('closed', () => {
    appWindow = null;
    backgroundWindow = null;
  });
  if (process.env.NODE_ENV === 'production') {
    const sourceMapSupport = require('source-map-support');
    sourceMapSupport.install();
  } else if (process.env.NODE_ENV === 'development') {
    appWindow.webContents.openDevTools();
    appWindow.webContents.on('context-menu', (_e, props) => {
      const { x, y } = props;
      Menu.buildFromTemplate([
        {
          label: 'Inspect element',
          click: () => appWindow.webContents.inspectElement(x, y),
        },
      ]).popup(appWindow);
    });
    require('electron-debug')();
    const path = require('path');
    const p = path.join(__dirname, './node_modules');
    require('module').globalPaths.push(p);
  }
}));

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});
