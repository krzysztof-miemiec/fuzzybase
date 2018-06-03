import { Table, TableBody, TableCell, TableHead, TableRow, withStyles } from '@material-ui/core';
import React from 'react';
import { connect } from 'react-redux';
import { RouteComponentProps } from 'react-router';
import uuid from 'uuid/v4';
import { postgresQuery } from '../../../../common/db/store/db.actions';
import { getConnection, getDatabasesState, getQuery } from '../../../../common/db/store/db.selectors';
import { CodeInput } from '../../../shared/components/code-input';
import { AppState } from '../../../store';
import { mapActions } from '../../../utils/redux.util';
import { select } from '../../../utils/selector.util';
import { StyleProps } from '../../../utils/styles.util';
import { styles } from './connection.styles';

type RouteProps = RouteComponentProps<{ id: string }>;

const mapStateToProps = (state: AppState, ownProps: RouteProps) => ({
  connection: select(state, getDatabasesState, getConnection(ownProps.match.params.id)),
});

const mapDispatchToProps = mapActions({
  postgresQuery,
});

type Props = ReturnType<typeof mapStateToProps> & typeof mapDispatchToProps & RouteProps;

interface State {
  code: string;
  queryId?: string;
}

class ConnectionComponent extends React.PureComponent<Props & StyleProps<typeof styles>, State> {
  state: State = { code: 'SELECT * FROM dupa;' };

  render() {
    const { connection, classes, actions } = this.props;
    const { code, queryId } = this.state;
    const query = select(connection, getQuery(queryId));
    const rows = query && ((query.result && query.result.rows) || [{ error: query.error }]) || [{}];
    const headers = Object.keys(rows[0]);
    if (query) {
      console.log(query);
    }
    return (
      <div className={classes.container}>
        <CodeInput
          text={code}
          className={classes.queryField}
          onTextChanged={code => this.setState({ code })}
          onSendTriggered={() => this.setState({ queryId: uuid() }, () => {
            actions.postgresQuery(connection.connectionId, this.state.queryId, code);
          })}
        />
        <div className={classes.tableContainer}>
          <div className={classes.table}>
            <Table>
              <TableHead>
                <TableRow>
                  <TableCell key={`index-${uuid()}`} />
                  {headers.map(header => (
                    <TableCell key={header}>
                      {header}
                    </TableCell>
                  ))}
                </TableRow>
              </TableHead>
              <TableBody>
                {rows.map((row, index) => (
                  <TableRow key={index}>
                    <TableCell key="index">{index}</TableCell>
                    {Object.entries(row).map(([key, value]) => (
                      <TableCell key={key}>
                        {value}
                      </TableCell>
                    ))}
                  </TableRow>
                ))}
              </TableBody>
            </Table>
          </div>
        </div>
      </div>
    );
  }
}

export const Connection = connect(mapStateToProps, mapDispatchToProps)(
  withStyles(styles)<Props>(ConnectionComponent)
);
