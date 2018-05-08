import { Add, CompareArrows } from '@material-ui/icons';
import {
  Button,
  IconButton,
  ListItem,
  ListItemSecondaryAction,
  ListItemText,
  Paper,
  Typography,
  withStyles
} from 'material-ui';
import React from 'react';
import { connect } from 'react-redux';
import { RouteComponentProps } from 'react-router';
import { connectToPostgres } from '../../../../background/postgres/postgres.actions';
import { PATHS } from '../../../app.paths';
import { getDatabaseList, getSettingsState } from '../../../shared/settings/store';
import { getDatabaseUrl } from '../../../shared/settings/store/settings.utils';
import { AppState } from '../../../store';
import { i18n } from '../../../utils/i18n.util';
import { mapActions } from '../../../utils/redux.util';
import { select } from '../../../utils/selector.util';
import { StyleProps } from '../../../utils/styles.util';
import { styles } from './database-list.styles';

const List = require('material-ui').List;

const mapStateToProps = (state: AppState) => ({
  databases: select(state, getSettingsState, getDatabaseList),
});

const mapDispatchToProps = mapActions({
  connectToPostgres,
});

type Props = ReturnType<typeof mapStateToProps> & typeof mapDispatchToProps & RouteComponentProps<{}>;

const DatabaseListComponent: React.SFC<Props & StyleProps<typeof styles>> = ({
  databases, history, classes, actions,
}) => (
  <Paper className={classes.container}>
    <Typography variant="headline">
      {i18n.t('databases.title')}
    </Typography>
    {databases.length > 0 ? (
      <List>
        {databases.map(db => {
          return (
            <ListItem key={db.id} onClick={() => history.push(PATHS.DATABASE(db.id))}>
              <ListItemText primary={db.name} secondary={getDatabaseUrl(db)} />
              <ListItemSecondaryAction>
                <IconButton aria-label="Connect" onClick={() => actions.connectToPostgres(db.id)}>
                  <CompareArrows />
                </IconButton>
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

export const DatabaseList = connect(mapStateToProps, mapDispatchToProps)(
  withStyles(styles)<Props>(DatabaseListComponent)
);
