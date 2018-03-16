'use strict';
// eslint-disable global-require
const { app, BrowserWindow, Menu, shell } = require('electron');
const Raven = require('raven');
Raven.config('https://1d21dfb7203b48d4886123361c64a63f:d9539900eb7a482e825bfdad2427c78d@sentry.io/235585').install();

const isMac = process.platform === 'darwin';
let menu = null;
let mainWindow = null;

if (process.env.NODE_ENV === 'production') {
  const sourceMapSupport = require('source-map-support');
  sourceMapSupport.install();
} else if (process.env.NODE_ENV === 'development') {
  require('electron-debug')();
  const path = require('path');
  const p = path.join(__dirname, '../app/node_modules');
  require('module').globalPaths.push(p);
}

const installExtensions = () => {
  if (process.env.NODE_ENV === 'development') {
    const installer = require('electron-devtools-installer');

    const extensions = [
      'REACT_DEVELOPER_TOOLS',
      'REDUX_DEVTOOLS'
    ];
    const forceDownload = !!process.env.UPGRADE_EXTENSIONS;
    return Promise.all(extensions.map(name => installer.default(installer[name], forceDownload)));
  }
  return Promise.resolve();
};

const handleError = error => {
  if (process.env.NODE_ENV === 'production') {
    Raven.captureException(error);
  } else {
    console.error(error);
  }
};

process.on('uncaughtException', error => {
  handleError(error);
});

app.on('ready', () => installExtensions().then(() => {
  const window = mainWindow = new BrowserWindow({
    show: false,
    width: 1024,
    height: 728
  });

  window.loadURL(`file://${__dirname}/app.html`);

  window.webContents.on('crashed', (event, killed) => {
    if (!killed) {
      handleError(event);
    }
  });
  window.webContents.on('did-finish-load', () => {
    mainWindow.show();
    mainWindow.focus();
  });

  window.on('unresponsive', () => {
    handleError(new Error('An app window became unresponsive.'));
  });
  window.on('closed', () => {
    mainWindow = null;
  });

  if (process.env.NODE_ENV === 'development') {
    mainWindow.openDevTools();
    mainWindow.webContents.on('context-menu', (e, props) => {
      const { x, y } = props;

      Menu.buildFromTemplate([{
        label: 'Inspect element',
        click() {
          mainWindow.inspectElement(x, y);
        }
      }]).popup(mainWindow);
    });
  }

  const cmd = isMac ? 'Command' : 'Ctrl';
  menu = Menu.buildFromTemplate([
    isMac ? {
      label: 'Fuzzybase',
      submenu: [{
        label: 'About Fuzzybase',
        selector: 'orderFrontStandardAboutPanel:'
      }, {
        type: 'separator'
      }, {
        label: 'Services',
        submenu: []
      }, {
        type: 'separator'
      }, {
        label: 'Hide Fuzzybase',
        accelerator: 'Command+H',
        selector: 'hide:'
      }, {
        label: 'Hide Others',
        accelerator: 'Command+Shift+H',
        selector: 'hideOtherApplications:'
      }, {
        label: 'Show All',
        selector: 'unhideAllApplications:'
      }, {
        type: 'separator'
      }, {
        label: 'Quit',
        accelerator: 'Command+Q',
        click() {
          app.quit();
        }
      }]
    } : {
      label: '&File',
      submenu: [{
        label: '&Close',
        accelerator: 'Ctrl+W',
        click() {
          mainWindow.close();
        }
      }]
    },
    {
      label: 'Edit',
      submenu: [{
        label: 'Undo',
        accelerator: 'Command+Z',
        selector: 'undo:'
      }, {
        label: 'Redo',
        accelerator: 'Shift+Command+Z',
        selector: 'redo:'
      }, {
        type: 'separator'
      }, {
        label: 'Cut',
        accelerator: 'Command+X',
        selector: 'cut:'
      }, {
        label: 'Copy',
        accelerator: 'Command+C',
        selector: 'copy:'
      }, {
        label: 'Paste',
        accelerator: 'Command+V',
        selector: 'paste:'
      }, {
        label: 'Select All',
        accelerator: 'Command+A',
        selector: 'selectAll:'
      }]
    },
    {
      label: '&View',
      submenu: [
        ...(process.env.NODE_ENV === 'development') ? [{
          label: '&Reload',
          accelerator: `${cmd}+R`,
          click() {
            mainWindow.webContents.reload();
          }
        }, {
          label: 'Toggle &Developer Tools',
          accelerator: `Alt+${cmd}+I`,
          click() {
            mainWindow.toggleDevTools();
          }
        }] : [],
        {
          label: 'Toggle &Full Screen',
          accelerator: isMac ? 'Ctrl+Command+F' : 'F11',
          click() {
            mainWindow.setFullScreen(!mainWindow.isFullScreen());
          }
        }]
    },
    isMac ? {
      label: 'Window',
      submenu: [{
        label: 'Minimize',
        accelerator: 'Command+M',
        selector: 'performMiniaturize:'
      }, {
        label: 'Close',
        accelerator: 'Command+W',
        selector: 'performClose:'
      }, {
        type: 'separator'
      }, {
        label: 'Bring All to Front',
        selector: 'arrangeInFront:'
      }]
    } : {},
    {
      label: 'Help',
      submenu: [{
        label: 'Search Issues',
        click() {
          shell.openExternal('https://github.com/krzysztof-miemiec/fuzzybase/issues');
        }
      }]
    }]);
  if (isMac) {
    Menu.setApplicationMenu(menu);
  } else {
    mainWindow.setMenu(menu);
  }
}));

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') app.quit();
});
