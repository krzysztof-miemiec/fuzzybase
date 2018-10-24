import * as path from 'path';
import { Color } from '../renderer/utils/color.util';
import { Config } from './config';

export const R = {
  color: {
    primary: '#851f42',
    accent: '#304799',
    drawer: '#1a1a1a',
    sidebar: '#333333',
    white: '#FFF',
    gray: '#646464',
    semiLightGray: Color.hexToRGB('#AEAEAE', .4),
    lightGray: '#AEAEAE',
    inputBackground: '#EEEEEE',
    background: '#FAFAFA',
  },
  dimen: {
    corner: 3,
    spacing: 8,
    drawerWidth: 68,
    drawerIconContainer: 40,
    drawerIcon: 28,
    sidebarWidth: 230,
    headerHeight: 64,
    toolbarHeight: 64,
    titleBarPadding: Config.IS_MAC ? 24 : 0,
  },
  fontSize: {
    bolder: '16px',
    normal: '13px',
  },
  string: {
    fuzzyPackage: path.join(__static, 'fuzzy.zip'),
    extension: path.join(__static, 'extension'),
    fuzzyLibrary: `fuzzy-${process.platform}-${process.arch}.${Config.IS_WINDOWS ? 'dll' : 'so'}`,
    fuzzyTargetLibrary: `fuzzy.${Config.IS_WINDOWS ? 'dll' : 'so'}`,
  },
  timing: {
    animationDuration: 350,
    snackbarDuration: 1800,
  },
};
