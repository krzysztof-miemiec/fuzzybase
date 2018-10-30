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
    const { headers, data, query } = this.props;

    const time = Date.now();
    const columnDefs = headers
      ? headers.map((header, index) => ({
        field: index.toString(),
        headerName: header.name,
      }))
      : [];
    const rowData = data;

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
    if (rowData && query.end - query.start > 0) {
      console.log('VDOM:\t' + (Date.now() - time) + '\tQ:\t' + (query.end - query.start) + '\tIPC:\t' + query.ipcTime);
    }
    return result;
  }
}
