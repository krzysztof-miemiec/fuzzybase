import { Table, TableBody, TableCell, TableHead, TableRow } from '@material-ui/core';
import React from 'react';
import uuid from 'uuid/v4';
import { styles } from './results-dom.styles';

interface Props {
  headers: { key: string, value: any }[];
  data: { key: string, value: any }[][];
}

export class ResultsDom extends React.PureComponent<Props> {

  renderRow = (row: { key: string, value: any }[], index: number) => {
    return (
      <TableRow key={index}>
        <TableCell key="index">{index}</TableCell>
        {row.map(this.renderCell)}
      </TableRow>
    );
  };

  renderCell = (cell: { key: string, value: any }) => {
    return (
      <TableCell key={cell.key}>
        {cell.value}
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
              <TableCell key={`index-${uuid()}`} />
              {headers.map(this.renderCell)}
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
