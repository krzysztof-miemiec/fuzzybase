// eslint-disable global-require
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

app.on('ready', () => installExtensions().then(() => {
  appWindow = createRendererWindow({
    window: {
      width: 1024,
      height: 728,
      title: Config.NAME,
    },
    show: true,
  });
  setIpcReceiver(appWindow.webContents);
  listen().subscribe(action => store.dispatch(action));
  setMenu(appWindow);
  appWindow.on('closed', () => {
    appWindow = null;
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
      ]).popup({ window: appWindow });
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
