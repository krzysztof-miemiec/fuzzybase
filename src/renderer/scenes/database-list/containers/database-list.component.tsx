import {
  Button,
  CircularProgress,
  ExpansionPanel,
  ExpansionPanelDetails,
  ExpansionPanelSummary,
  IconButton,
  Typography,
  withStyles
} from '@material-ui/core';
import { Add, Close, CompareArrows, ExpandMore } from '@material-ui/icons';
import React from 'react';
import { connect } from 'react-redux';
import { RouteComponentProps } from 'react-router';
import {
  ConnectionStatus,
  disconnectFromPostgres,
  getDatabaseList,
  getDatabasesState,
  getFirstDatabaseConnection,
  getStatus,
  setDatabase
} from '../../../../common/db/store/app';
import { connectToPostgres } from '../../../../common/db/store/db.actions';
import { createDatabaseState, getDatabaseUrl } from '../../../../common/db/store/db.utils';
import { AppState } from '../../../store';
import { i18n } from '../../../utils/i18n.util';
import { mapActions } from '../../../utils/redux.util';
import { select } from '../../../utils/selector.util';
import { StyleProps } from '../../../utils/styles.util';
import { DatabaseForm } from '../../database/components/database-form.component';
import { styles } from './database-list.styles';

const List = require('@material-ui/core').List;

const mapStateToProps = (state: AppState) => ({
  dbState: select(state, getDatabasesState),
});

const mapDispatchToProps = mapActions({
  connectToPostgres,
  disconnectFromPostgres,
  setDatabase,
});

type Props = ReturnType<typeof mapStateToProps> & typeof mapDispatchToProps & RouteComponentProps<{}>;

interface State {
  expanded?: string;
}

class DatabaseListComponent extends React.PureComponent<Props & StyleProps<typeof styles>, State> {

  state = { expanded: null };

  handleChange = id => (_, expanded) => this.setState({ expanded: expanded ? id : null });

  render() {
    const { dbState, classes, actions } = this.props;
    const { expanded } = this.state;
    const databases = select(dbState, getDatabaseList);
    return (
      <div>
        <Typography variant="display1">
          {i18n.t('databases.title')}
        </Typography>
        {databases.length > 0 ? (
          <List>
            {databases.map(db => {
              const connection = select(dbState, getFirstDatabaseConnection(db.id));
              const status = select(connection, getStatus);
              return (
                <ExpansionPanel key={db.id} expanded={expanded === db.id} onChange={this.handleChange(db.id)}>
                  <ExpansionPanelSummary expandIcon={<ExpandMore />}>
                    <Typography className={classes.heading}>{db.name}</Typography>
                    <Typography className={classes.secondaryHeading}>{getDatabaseUrl(db)}</Typography>
                  </ExpansionPanelSummary>
                  <ExpansionPanelDetails>
                    <DatabaseForm
                      database={db}
                      onSubmit={actions.setDatabase}
                    />
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
                  </ExpansionPanelDetails>
                </ExpansionPanel>
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
          onClick={() => {
            const database = createDatabaseState();
            actions.setDatabase(database);
            this.setState({ expanded: database.id });
          }}
        >
          <Add />
        </Button>
      </div>
    );
  }
}

export const DatabaseList = connect(mapStateToProps, mapDispatchToProps)(
  withStyles(styles)<Props>(DatabaseListComponent)
);
