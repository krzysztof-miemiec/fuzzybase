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
          accelerator: `${cmd}+H`,
          role: 'hide',
        }, {
          label: 'Hide Others',
          accelerator: `${cmd}+Shift+H`,
          role: 'hideOthers',
        }, {
          label: 'Show SettingsActions',
          role: 'front',
        }, {
          type: 'separator',
        }, {
          label: 'Quit',
          accelerator: `${cmd}+Q`,
          role: 'quit',
        },
      ],
    } : {
      label: '&File',
      submenu: [
        {
          label: '&Close',
          accelerator: `${cmd}+W`,
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
          accelerator: `${cmd}+Z`,
          role: 'undo',
        }, {
          label: 'Redo',
          accelerator: `Shift+${cmd}+Z`,
          role: 'redo',
        }, {
          type: 'separator',
        }, {
          label: 'Cut',
          accelerator: `${cmd}+X`,
          role: 'cut',
        }, {
          label: 'Copy',
          accelerator: `${cmd}+C`,
          role: 'copy',
        }, {
          label: 'Paste',
          accelerator: `${cmd}+V`,
          role: 'paste',
        }, {
          label: 'Select All',
          accelerator: `${cmd}+A`,
          role: 'selectAll',
        },
      ],
    },
    {
      label: '&View',
      submenu: [
        {
          label: '&Reload',
          accelerator: `${cmd}+R`,
          role: 'forceReload',
        }, {
          label: 'Toggle &Developer Tools',
          accelerator: `Alt+${cmd}+I`,
          role: 'toggleDevTools',
        },
        {
          label: 'Toggle &Full Screen',
          accelerator: isMac ? 'Ctrl+Command+F' : 'F11',
          role: 'toggleFullScreen',
        },
      ],
    },
    {
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
        },
      ],
    },
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
