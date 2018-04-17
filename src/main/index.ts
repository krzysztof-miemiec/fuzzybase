// eslint-disable global-require
import { app, ipcMain, Menu } from 'electron';
import { createRendererWindow, WindowName } from '../common/window';
import { handleError } from './errors';
import { setMenu } from './menu';

let mainWindow = null;
let backgroundWindow = null;

const installExtensions = (): Promise<void> => {
  if (process.env.NODE_ENV === 'development') {
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
  backgroundWindow = createRendererWindow({
    name: WindowName.BACKGROUND,
    show: false,
  });
  mainWindow = createRendererWindow({
    window: {
      width: 1024,
      height: 728,
    },
    show: true,
    name: WindowName.APP,
  });
  setMenu(mainWindow);
  mainWindow.on('closed', () => {
    mainWindow = null;
    backgroundWindow = null;
  });
  if (process.env.NODE_ENV === 'production') {
    const sourceMapSupport = require('source-map-support');
    sourceMapSupport.install();
  } else if (process.env.NODE_ENV === 'development') {
    mainWindow.openDevTools();
    mainWindow.webContents.on('context-menu', (_e, props) => {
      const { x, y } = props;
      Menu.buildFromTemplate([
        {
          label: 'Inspect element',
          click: () => mainWindow.webContents.inspectElement(x, y),
        },
      ]).popup(mainWindow);
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

ipcMain.on('renderer', (event, payload) => {
  console.log(event);
  console.log(payload);
  mainWindow.webContents.send('main', payload);
});

ipcMain.on('background', (event, payload) => {
  console.log(event);
  console.log(payload);
  backgroundWindow.webContents.send('main', payload);
});
