import {
  Avatar,
  Divider,
  Drawer as MaterialDrawer,
  IconButton,
  List,
  ListItem,
  ListItemIcon,
  ListItemText,
  withStyles
} from '@material-ui/core';
import { ChevronLeft, ChevronRight } from '@material-ui/icons';
import classNames from 'classnames';
import React from 'react';
import { connect } from 'react-redux';
import { RouteComponentProps, withRouter } from 'react-router';
import { getConnectionList, getDatabase, getDatabasesState } from '../../../../../common/db/store/db.selectors';
import { PATHS } from '../../../../app.paths';
import { AppState } from '../../../../store';
import { select } from '../../../../utils/selector.util';
import { StyleProps } from '../../../../utils/styles.util';
import { getDrawerItems } from './drawer.items';
import { styles } from './drawer.styles';

const mapStateToProps = (state: AppState) => ({
  databases: select(state, getDatabasesState),
  connections: select(state, getDatabasesState, getConnectionList),
});

interface ComponentProps {
  isOpen: boolean;
  onClose: () => void;
}

type Props = ComponentProps & ReturnType<typeof mapStateToProps>;

export const DrawerComponent: React.SFC<Props & RouteComponentProps<{}> & StyleProps<typeof styles>> = ({
  isOpen, classes, theme, onClose, history, connections, databases,
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
        <ListItem
          button={true}
          key={path}
          onClick={() => history.push(path)}
        >
          <ListItemIcon>
            <Icon />
          </ListItemIcon>
          <ListItemText primary={title} />
        </ListItem>
      ))}
    </List>
    <Divider />
    <List>
      {Object.values(connections).map(connection => {
        const database = select(databases, getDatabase(connection.clientId));
        return (
          <ListItem
            button={true}
            key={connection.connectionId}
            onClick={() => history.push(PATHS.CONNECTION(connection.connectionId))}
          >
            <Avatar>{database.name.split(' ').map(word => word[0]).join()}</Avatar>
            <ListItemText primary={database.name} />
          </ListItem>
        );
      })}
    </List>
  </MaterialDrawer>
);

export const Drawer = connect(mapStateToProps)(
  withStyles(styles, { withTheme: true })<Props>(
    withRouter(DrawerComponent)
  )
);
