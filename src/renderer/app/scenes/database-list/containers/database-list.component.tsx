import { ListItem, ListItemText, Paper, Typography } from 'material-ui';
import React from 'react';
import { connect } from 'react-redux';
import { RouteComponentProps } from 'react-router';
import { PATHS } from '../../../app.paths';
import { getDatabaseList, getSettingsState } from '../../../shared/settings/store';
import { AppState } from '../../../store';
import { i18n } from '../../../utils/i18n.util';
import { select } from '../../../utils/selector.util';

const List = require('material-ui').List;

const mapStateToProps = (state: AppState) => ({
  databases: select(state, getSettingsState, getDatabaseList),
});

type Props = ReturnType<typeof mapStateToProps> & RouteComponentProps<{}>;

const DatabaseListComponent: React.SFC<Props> = ({
  databases, history,
}) => (
  <Paper>
    <Typography>{i18n.t('databases.title')}</Typography>
    <List>
      {databases.map(db => {

        return (
          <ListItem key={db.id} onClick={() => history.push(PATHS.DATABASE(db.id))}>
            <ListItemText primary={db.name} secondary={db.username + '@' + db.host + ':' + db.port} />
          </ListItem>
        );
      })}
    </List>
  </Paper>
);

export const DatabaseList = connect(mapStateToProps)(DatabaseListComponent);
