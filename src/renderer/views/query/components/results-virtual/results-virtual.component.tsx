import { ColumnApi, GridApi, GridColumnsChangedEvent, GridReadyEvent } from 'ag-grid-community';
import { AgGridReact } from 'ag-grid-react';
import React from 'react';
import { View } from '../../../../shared/components/view';
import { ResultsComponent } from '../results/results.component';
import { styles } from './results-virtual.styles';

import './theme.scss';

export class ResultsVirtual extends ResultsComponent {
  api: GridApi;
  columnApi: ColumnApi;

  onGridReady = (event: GridReadyEvent) => {
    this.api = event.api;
    this.columnApi = event.columnApi;
  };

  onGridColumnsChanged = (event: GridColumnsChangedEvent) => {
    event.columnApi.autoSizeAllColumns();
  };

  render() {
    const { headers, data } = this.props;

    console.time('Data preparation');
    const columnDefs = headers
      ? headers.map((header, index) => ({
        field: index.toString(),
        headerName: header.name,
      }))
      : [];
    const rowData = data
      ? data.map(row => row.reduce((object, value, index) => {
        object[index.toString()] = value;
        return object;
      }, {}))
      : undefined;
    console.timeEnd('Data preparation');

    console.time('Render');
    const result = (
      <View style={[styles.container, 'ag-theme-fresh']}>
        <AgGridReact
          onGridColumnsChanged={this.onGridColumnsChanged}
          onGridReady={this.onGridReady}
          suppressColumnVirtualisation={true}
          reactNext={true}
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
