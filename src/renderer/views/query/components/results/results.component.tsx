import { FieldDef } from 'pg';
import React from 'react';
import { DatabaseQueryState } from '../../../../../common/db/store/db.state';

export interface ResultsComponentProps {
  headers: FieldDef[];
  data: any[][];
  query: DatabaseQueryState;
}

export class ResultsComponent extends React.PureComponent<ResultsComponentProps> {
}
