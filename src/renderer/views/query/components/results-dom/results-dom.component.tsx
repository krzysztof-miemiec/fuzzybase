import React from 'react';
import uuid from 'uuid/v4';
import { ResultsComponent } from '../results/results.component';
import { styles } from './results-dom.styles';

const INDEX_KEY = `index-${uuid()}`;

export class ResultsDom extends ResultsComponent {

  renderRow = (row: any[], index: number) => {
    return (
      <div className={styles.tableRow} key={index}>
        <div className={styles.tableCell} key={INDEX_KEY}>{index}</div>
        {row.map(this.renderCell)}
      </div>
    );
  };

  renderCell = (value: any, index: number) => {
    return (
      <div className={styles.tableCell} key={index}>
        {`${value}`}
      </div>
    );
  };

  render() {
    const { data, headers, query } = this.props;
    const time = Date.now();
    const result = (
      <div className={styles.container}>
        <div className={styles.table}>
          <div className={styles.tableHeader}>
            <div className={styles.tableRow}>
              <div className={styles.tableCell} key={INDEX_KEY}/>
              {headers.map((header, index) => this.renderCell(header.name, index))}
            </div>
          </div>
          <div className={styles.tableRows}>
            {data.map(this.renderRow)}
          </div>
        </div>
      </div>
    );
    if (query.end - query.start > 0) {
      console.log('DOM:\t' + (Date.now() - time) + '\tQ:\t' + (query.end - query.start) + '\tIPC:\t' + query.ipcTime);
    }
    return result;
  }
}
