import { debounce } from 'lodash';
import { FieldDef } from 'pg';
import React from 'react';
import { connect } from 'react-redux';
import { RouteComponentProps } from 'react-router';
import { postgresQuery, setQuery } from '../../../../../common/db/store/db.actions';
import { getConnection, getDatabasesState, getQuery } from '../../../../../common/db/store/db.selectors';
import { AppState } from '../../../../store';
import { mapActions } from '../../../../utils/redux.util';
import { select } from '../../../../utils/selector.util';
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
    const { query } = this.props;
    const value = query && (query.error || query.result);
    const oldValue = oldQuery && (oldQuery.error || oldQuery.result);

    if (value !== oldValue) {
      state.data = (query.result && query.result.rows) || [[query.error]];
      state.headers = (query.result && query.result.fields) || (query.error && [ERROR_HEADER]);
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
        <div className={styles.container}>
          Loading...
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
      </div>
    );
  }
}

export const Query = connect(mapStateToProps, mapDispatchToProps)(QueryComponent);
