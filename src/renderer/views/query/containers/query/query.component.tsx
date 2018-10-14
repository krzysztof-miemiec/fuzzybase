import { Typography } from '@material-ui/core';
import { debounce } from 'lodash';
import { FieldDef } from 'pg';
import React from 'react';
import { connect } from 'react-redux';
import { RouteComponentProps } from 'react-router';
import { getMetadata, postgresQuery, setQuery } from '../../../../../common/db/store/db.actions';
import { getConnection, getDatabasesState, getQuery } from '../../../../../common/db/store/db.selectors';
import { mapActions } from '../../../../../common/utils/redux.util';
import { select } from '../../../../../common/utils/selector.util';
import { AppState } from '../../../../store';
import { CodeInput } from '../../components/code-input';
import { ResultsVirtual } from '../../components/results-virtual';
import { styles } from './query.styles';

const ERROR_HEADER: FieldDef = {
  columnID: 0,
  tableID: 0,
  format: '',
  dataTypeID: 0,
  dataTypeModifier: 0,
  dataTypeSize: 4,
  name: 'Error',
};

type RouteProps = RouteComponentProps<{ connectionId: string, queryId: string }>;

const mapStateToProps = (state: AppState, ownProps: RouteProps) => {
  const { connectionId, queryId } = ownProps.match.params;
  const connection = select(state, getDatabasesState, getConnection(connectionId));
  return {
    connection,
    query: select(connection, getQuery(queryId)),
  };
};

const mapDispatchToProps = mapActions({
  postgresQuery,
  setQuery,
  getMetadata,
});

type Props = ReturnType<typeof mapStateToProps> & typeof mapDispatchToProps & RouteProps;

interface State {
  code: string;
  headers: FieldDef[];
  data: any[][];
}

class QueryComponent extends React.PureComponent<Props, State> {
  delayedSetQuery = debounce((code: string) => {
    const { connection, query, actions } = this.props;
    actions.setQuery(connection.connectionId, query.id, code);
  }, 500);

  constructor(props: Props) {
    super(props);
    this.state = { code: '', headers: [], data: [], ...this.getStateUpdate() };
  }

  getStateUpdate = (oldProps?: Props) => {
    const state: State = {} as State;
    const { query: oldQuery = undefined } = oldProps || {};
    const { query, actions, connection } = this.props;
    const value = query && (query.error || query.result);
    const oldValue = oldQuery && (oldQuery.error || oldQuery.result);

    if (value !== oldValue) {
      if (!value) {
        return {} as any;
      }
      state.data = (query.result && query.result.rows) || [[query.error]];
      state.headers = (query.result && query.result.fields) || (query.error && [ERROR_HEADER]);
      actions.getMetadata(connection.connectionId);
    }

    if ((oldQuery && oldQuery.id) !== (query && query.id)) {
      state.code = query ? query.query : '';
    }

    return state;
  };

  componentDidUpdate(oldProps: Props) {
    this.setState(this.getStateUpdate(oldProps));
  }

  componentWillUnmount() {
    const { connection, query, actions } = this.props;
    const { code } = this.state;
    actions.setQuery(connection.connectionId, query.id, code);
  }

  setCode = (code: string) => {
    this.setState({ code });
    this.delayedSetQuery(code);
  };

  executeQuery = () => {
    const { actions, connection, query } = this.props;
    const { code } = this.state;
    actions.postgresQuery(connection.connectionId, query.id, code);
  };

  render() {
    const { query } = this.props;
    const { code, data, headers } = this.state;
    if (!query) {
      return (
        <div className={styles.emptyContainer}>
          <Typography variant="body1">
            There is no selected query at the moment. You can open or create new query by using a sidebar.
          </Typography>
        </div>
      );
    }
    return (
      <div className={styles.container}>
        <CodeInput
          text={code}
          className={styles.queryField}
          onTextChanged={this.setCode}
          onSendTriggered={this.executeQuery}
        />
        <div className={styles.tableContainer}>
          {data && (
            <ResultsVirtual headers={headers} data={data} />
          )}
        </div>
        <div className={styles.statusBar}>
          <Typography variant="caption">
            {data
              ? (query.end && query.start) || (!query.end && !query.start)
                ? `Rows: ${data.length.toLocaleString()}, Execution time: ${
                  (query.end - query.start || 0).toLocaleString()} ms`
                : 'Query in progress...'
              : 'No query data.'
            }
          </Typography>
        </div>
      </div>
    );
  }
}

export const Query = connect(mapStateToProps, mapDispatchToProps)(QueryComponent);
