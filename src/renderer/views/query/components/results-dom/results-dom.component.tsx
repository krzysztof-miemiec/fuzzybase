import { Table, TableBody, TableCell, TableHead, TableRow } from '@material-ui/core';
import React from 'react';
import uuid from 'uuid/v4';
import { ResultsComponent } from '../results/results.component';
import { styles } from './results-dom.styles';

const INDEX_KEY = `index-${uuid()}`;

export class ResultsDom extends ResultsComponent {

  renderRow = (row: any[], index: number) => {
    return (
      <TableRow key={index}>
        <TableCell key={INDEX_KEY}>{index}</TableCell>
        {row.map(this.renderCell)}
      </TableRow>
    );
  };

  renderCell = (value: any, index: number) => {
    return (
      <TableCell key={index}>
        {`${value}`}
      </TableCell>
    );
  };

  render() {
    const { data, headers } = this.props;
    console.log('resultsdom render');
    return (
      <div className={styles.table}>
        <Table>
          <TableHead>
            <TableRow>
              <TableCell key={INDEX_KEY} />
              {headers.map((header, index) => this.renderCell(header.name, index))}
            </TableRow>
          </TableHead>
          <TableBody>
            {data.map(this.renderRow)}
          </TableBody>
        </Table>
      </div>
    );
  }
}
