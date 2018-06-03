import { GridList, GridListTile, Paper, Typography, withStyles } from '@material-ui/core';
import React from 'react';
import { connect } from 'react-redux';
import { getDatabaseList, getDatabasesState } from '../../../../common/db/store/db.selectors';
import { AppState } from '../../../store';
import { select } from '../../../utils/selector.util';
import { StyleProps } from '../../../utils/styles.util';
import { styles } from './quick-start.styles';

const mapStateToProps = (state: AppState) => ({
  databases: select(state, getDatabasesState, getDatabaseList),
});

type Props = ReturnType<typeof mapStateToProps>;

const QuickStartComponent: React.SFC<Props & StyleProps<typeof styles>> = ({
  classes, databases,
}) => (
  <div className={classes.container}>
    <Typography variant="display1">
      Quick start
    </Typography>
    <GridList className={classes.gridList} cols={3} >
      {databases.map((tile, index) => (
        <GridListTile key={tile.id} cols={index === 0 ? 2 : 1} style={{ height: 'auto' }}>
          <Paper className={classes.card}>
            <Typography variant="headline">
              {tile.name}
            </Typography>
          </Paper>
        </GridListTile>
      ))}
    </GridList>
  </div>
);

export const QuickStart = connect(mapStateToProps)(
  withStyles(styles)<Props>(QuickStartComponent)
);
