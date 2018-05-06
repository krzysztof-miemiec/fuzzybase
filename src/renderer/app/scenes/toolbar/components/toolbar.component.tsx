import { CompareArrows } from '@material-ui/icons';
import { IconButton, Toolbar as MaterialToolbar } from 'material-ui';
import React from 'react';
import { i18n } from '../../../utils/i18n.util';

export const Toolbar: React.SFC = () => (
  <MaterialToolbar>
    <IconButton>
      <CompareArrows />
      {i18n.t('toolbar.connections')}
    </IconButton>
  </MaterialToolbar>
);
