import { CompareArrows, Menu } from '@material-ui/icons';
import classNames from 'classnames';
import { AppBar, IconButton, Toolbar as MaterialToolbar, Tooltip, Typography } from 'material-ui';
import { withStyles } from 'material-ui/es';
import React from 'react';
import { Config } from '../../../../../common/config';
import { i18n } from '../../../../utils/i18n.util';
import { StyleProps } from '../../../../utils/styles.util';
import { styles } from '../../containers/layout.styles';

interface Props {
  isDrawerOpen: boolean;
  onMenuClicked: () => void;
}

const ToolbarComponent: React.SFC<Props & StyleProps<typeof styles>> = ({
  classes, isDrawerOpen, onMenuClicked,
}) => (
  <AppBar
    position="absolute"
    className={classNames(classes.appBar, isDrawerOpen && classes.appBarShift)}
  >
    <MaterialToolbar disableGutters={!isDrawerOpen} className={classes.toolbar}>
      <IconButton
        color="inherit"
        aria-label="open drawer"
        onClick={onMenuClicked}
        className={classNames(classes.menuButton, isDrawerOpen && classes.hide)}
      >
        <Menu />
      </IconButton>
      <Typography variant="title" color="inherit" className={classes.flex}>
        {Config.NAME}
      </Typography>
      <Tooltip title={i18n.t('connections.title')}>
        <IconButton
          aria-label={i18n.t('connections.title')}
          onClick={() => {
            console.log('click');
          }}
        >
          <CompareArrows />
        </IconButton>
      </Tooltip>
    </MaterialToolbar>
  </AppBar>
);

export const Toolbar = withStyles(styles)<Props>(ToolbarComponent);
