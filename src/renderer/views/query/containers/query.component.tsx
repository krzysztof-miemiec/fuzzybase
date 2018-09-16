import { debounce } from 'lodash';
import React from 'react';
import { connect } from 'react-redux';
import { RouteComponentProps } from 'react-router';
import { postgresQuery, setQuery } from '../../../../common/db/store/db.actions';
import { getConnection, getDatabasesState, getQuery } from '../../../../common/db/store/db.selectors';
import { CodeInput } from '../../../shared/components/code-input';
import { AppState } from '../../../store';
import { mapActions } from '../../../utils/redux.util';
import { select } from '../../../utils/selector.util';
import { ResultsDom } from '../components/results-dom';
import { styles } from './query.styles';

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
});

type Props = ReturnType<typeof mapStateToProps> & typeof mapDispatchToProps & RouteProps;

interface KeyValue {
  key: string;
  value: any;
}

interface State {
  code: string;
  headers: KeyValue[];
  data: KeyValue[][];
}

const convertRowToData = (row: object): KeyValue[] => Object.entries(row).map(([key, value]) => ({ key, value }));

class QueryComponent extends React.PureComponent<Props, State> {
  delayedSetQuery = debounce((code: string) => {
    const { connection, query, actions } = this.props;
    actions.setQuery(connection.connectionId, query.id, code);
  }, 500);
  state: State = { code: '', headers: [], data: [] };

  componentDidUpdate(oldProps: Props) {
    const { query: oldQuery } = oldProps;
    const { query } = this.props;
    if ((query.error || query.result) !== (oldQuery.error || oldQuery.result)) {
      const rows = ((query.result && query.result.rows) || [{ error: query.error }]) || [{}];
      const headers = query.result && query.result.fields.map(field => ({
        key: field.columnID.toString(), value: field.name,
      })) || [{ key: 'error', value: 'Error' }];
      this.setState({ headers, data: rows.map(convertRowToData) });
    }
    if ((oldQuery && oldQuery.id) !== (query && query.id)) {
      this.setState({ code: query ? query.query : '' });
    }
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
        <div className={styles.container}>
          Loading...
        </div>
      );
    }
    console.log(data);
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
            <ResultsDom headers={headers} data={data} />
          )}
        </div>
      </div>
    );
  }
}

export const Query = connect(mapStateToProps, mapDispatchToProps)(QueryComponent);
