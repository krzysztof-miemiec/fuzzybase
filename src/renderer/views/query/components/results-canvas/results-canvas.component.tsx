import { AgGridReact } from 'ag-grid-react';
import React from 'react';
import { View } from '../../../../shared/components/view';
import { ResultsComponent } from '../results/results.component';
import { styles } from './results-canvas.styles';

import './theme.scss';

export class ResultsCanvas extends ResultsComponent {

  render() {
    const { headers, data } = this.props;

    console.time('Data preparation');
    const columnDefs = headers.map((header, index) => ({
      field: index.toString(),
      headerName: header.name,
    }));
    const rowData = (data || []).map(row => row.reduce((object, value, index) => {
      object[index.toString()] = value;
      return object;
    }, {}));
    console.timeEnd('Data preparation');

    console.time('Render');
    const result = (
      <View style={[styles.container, 'ag-theme-material']}>
        <AgGridReact
          enableSorting={true}
          enableFilter={true}
          enableRangeSelection={true}
          enableColResize={true}
          columnDefs={columnDefs}
          rowData={rowData}
        />
      </View>
    );
    console.timeEnd('Render');
    return result;
  }
}
