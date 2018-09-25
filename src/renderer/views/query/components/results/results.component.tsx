import { FieldDef } from 'pg';
import React from 'react';

export interface ResultsComponentProps {
  headers: FieldDef[];
  data: any[][];
}

export class ResultsComponent extends React.PureComponent<ResultsComponentProps> {
}
