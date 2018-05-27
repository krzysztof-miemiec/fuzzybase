import { Add, Close, CompareArrows } from '@material-ui/icons';
import {
  Button, CircularProgress,
  IconButton,
  ListItem,
  ListItemSecondaryAction,
  ListItemText,
  Paper,
  Typography,
  withStyles
} from '@material-ui/core';
import React from 'react';
import { connect } from 'react-redux';
import { RouteComponentProps } from 'react-router';
import {
  ConnectionStatus,
  disconnectFromPostgres,
  getDatabaseList,
  getDatabasesState,
  getFirstDatabaseConnection,
  getStatus
} from '../../../../common/db/store/app';
import { connectToPostgres } from '../../../../common/db/store/db.actions';
import { getDatabaseUrl } from '../../../../common/db/store/db.utils';
import { PATHS } from '../../../app.paths';
import { AppState } from '../../../store';
import { i18n } from '../../../utils/i18n.util';
import { mapActions } from '../../../utils/redux.util';
import { select } from '../../../utils/selector.util';
import { StyleProps } from '../../../utils/styles.util';
import { styles } from './database-list.styles';

const List = require('@material-ui/core').List;

const mapStateToProps = (state: AppState) => ({
  dbState: select(state, getDatabasesState),
});

const mapDispatchToProps = mapActions({
  connectToPostgres,
  disconnectFromPostgres,
});

type Props = ReturnType<typeof mapStateToProps> & typeof mapDispatchToProps & RouteComponentProps<{}>;

const DatabaseListComponent: React.SFC<Props & StyleProps<typeof styles>> = ({
  dbState, history, classes, actions,
}) => {
  const databases = select(dbState, getDatabaseList);
  return (
    <Paper className={classes.container}>
      <Typography variant="headline">
        {i18n.t('databases.title')}
      </Typography>
      {databases.length > 0 ? (
        <List>
          {databases.map(db => {
            const connection = select(dbState, getFirstDatabaseConnection(db.id));
            const status = select(connection, getStatus);
            return (
              <ListItem key={db.id} onClick={() => history.push(PATHS.DATABASE(db.id))}>
                <ListItemText primary={db.name} secondary={getDatabaseUrl(db)} />
                <ListItemSecondaryAction>
                  {(!status || status === ConnectionStatus.DISCONNECTED) && (
                    <IconButton aria-label="Connect" onClick={() => actions.connectToPostgres(db)}>
                      <CompareArrows />
                    </IconButton>
                  )}
                  {status === ConnectionStatus.CONNECTING && (
                    <CircularProgress />
                  )}
                  {status === ConnectionStatus.CONNECTED && (
                    <IconButton
                      aria-label="Disconnect"
                      onClick={() => actions.disconnectFromPostgres(connection.connectionId)}
                    >
                      <Close />
                    </IconButton>
                  )}
                </ListItemSecondaryAction>
              </ListItem>
            );
          })}
        </List>
      ) : (
        <Typography>There are no databases defined at the moment.</Typography>
      )}
      <Button
        variant="fab"
        className={classes.fab}
        color="secondary"
        onClick={() => history.push(PATHS.DATABASE(null))}
      >
        <Add />
      </Button>
    </Paper>
  );
};

export const DatabaseList = connect(mapStateToProps, mapDispatchToProps)(
  withStyles(styles)<Props>(DatabaseListComponent)
);
