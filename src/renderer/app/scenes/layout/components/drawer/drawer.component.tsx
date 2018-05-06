import { ChevronLeft, ChevronRight } from '@material-ui/icons';
import classNames from 'classnames';
import {
  Avatar,
  Divider,
  Drawer as MaterialDrawer,
  IconButton,
  List,
  ListItem,
  ListItemText,
  withStyles
} from 'material-ui';
import React from 'react';
import { RouteComponentProps, withRouter } from 'react-router';
import { StyleProps } from '../../../../utils/styles.util';
import { getDrawerItems } from './drawer.items';
import { styles } from './drawer.styles';

interface Props {
  isOpen: boolean;
  onClose: () => void;
}

export const DrawerComponent: React.SFC<Props & RouteComponentProps<{}> & StyleProps<typeof styles>> = ({
  isOpen, classes, theme, onClose, history,
}) => (
  <MaterialDrawer
    variant="permanent"
    classes={{
      paper: classNames(classes.drawerPaper, !isOpen && classes.drawerPaperClose),
    }}
    open={isOpen}
  >
    <div className={classes.toolbar}>
      <IconButton onClick={onClose}>
        {theme.direction === 'rtl' ? <ChevronRight /> : <ChevronLeft />}
      </IconButton>
    </div>
    <Divider />
    <List>
      {getDrawerItems().map(({ path, icon: Icon, title }) => (
        <ListItem key={path} onClick={() => history.push(path)}>
          <Avatar>
            <Icon />
          </Avatar>
          <ListItemText primary={title} />
        </ListItem>
      ))}
    </List>
    <Divider />

  </MaterialDrawer>
);

export const Drawer = withStyles(styles, { withTheme: true })<Props>(withRouter(DrawerComponent));
