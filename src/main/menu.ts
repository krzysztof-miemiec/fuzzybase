import { BrowserWindow, Menu, shell } from 'electron';

export const setMenu = (mainWindow: BrowserWindow) => {
  const isMac = process.platform === 'darwin';

  const cmd = isMac ? 'Command' : 'Ctrl';
  const menu = Menu.buildFromTemplate([
    isMac ? {
      label: 'Fuzzybase',
      submenu: [
        {
          label: 'About Fuzzybase',
          role: 'about',
        }, {
          type: 'separator',
        }, {
          label: 'Services',
          submenu: [],
        }, {
          type: 'separator',
        }, {
          label: 'Hide Fuzzybase',
          accelerator: 'Command+H',
          role: 'hide',
        }, {
          label: 'Hide Others',
          accelerator: 'Command+Shift+H',
          role: 'hideOthers',
        }, {
          label: 'Show SettingsActions',
          role: 'front',
        }, {
          type: 'separator',
        }, {
          label: 'Quit',
          accelerator: 'Command+Q',
          role: 'quit',
        },
      ],
    } : {
      label: '&File',
      submenu: [
        {
          label: '&Close',
          accelerator: 'Ctrl+W',
          click() {
            mainWindow.close();
          },
        },
      ],
    },
    {
      label: 'Edit',
      submenu: [
        {
          label: 'Undo',
          accelerator: 'Command+Z',
          role: 'undo',
        }, {
          label: 'Redo',
          accelerator: 'Shift+Command+Z',
          role: 'redo',
        }, {
          type: 'separator',
        }, {
          label: 'Cut',
          accelerator: 'Command+X',
          role: 'cut',
        }, {
          label: 'Copy',
          accelerator: 'Command+C',
          role: 'copy',
        }, {
          label: 'Paste',
          accelerator: 'Command+V',
          role: 'paste',
        }, {
          label: 'Select SettingsActions',
          accelerator: 'Command+A',
          role: 'selectAll',
        },
      ],
    },
    {
      label: '&View',
      submenu: [
        ...(process.env.NODE_ENV === 'development') ? [
          {
            label: '&Reload',
            accelerator: `${cmd}+R`,
            role: 'forceReload',
          }, {
            label: 'Toggle &Developer Tools',
            accelerator: `Alt+${cmd}+I`,
            role: 'toggleDevTools',
          },
        ] : [],
        {
          label: 'Toggle &Full Screen',
          accelerator: isMac ? 'Ctrl+Command+F' : 'F11',
          role: 'toggleFullScreen',
        },
      ],
    },
    isMac ? {
      label: 'Window',
      submenu: [
        {
          label: 'Minimize',
          accelerator: 'Command+M',
          role: 'minimize',
        }, {
          label: 'Close',
          accelerator: 'Command+W',
          role: 'close',
        }, {
          type: 'separator',
        }, {
          label: 'Bring SettingsActions to Front',
          role: 'front',
        },
      ],
    } : {},
    {
      label: 'Help',
      submenu: [
        {
          label: 'Search Issues',
          click() {
            shell.openExternal('https://github.com/krzysztof-miemiec/fuzzybase/issues');
          },
        },
      ],
    },
  ]);
  if (isMac) {
    Menu.setApplicationMenu(menu);
  } else {
    mainWindow.setMenu(menu);
  }
};
