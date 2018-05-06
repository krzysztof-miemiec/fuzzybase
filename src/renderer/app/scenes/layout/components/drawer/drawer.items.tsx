import { Dns, Home } from '@material-ui/icons';
import { SvgIconProps } from 'material-ui/SvgIcon/SvgIcon';
import * as React from 'react';
import { PATHS } from '../../../../app.paths';
import { i18n } from '../../../../utils/i18n.util';

interface DrawerItem {
  icon: React.ComponentType<SvgIconProps>;
  title: string;
  path: string;
}

export const getDrawerItems = (): DrawerItem[] => ([
  {
    icon: Home,
    title: i18n.t('drawer.home'),
    path: PATHS.HOME,
  },
  {
    icon: Dns,
    title: i18n.t('drawer.databases'),
    path: PATHS.DATABASES,
  },
]);
