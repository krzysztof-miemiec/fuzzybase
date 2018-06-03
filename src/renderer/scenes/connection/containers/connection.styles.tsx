import { Theme } from '@material-ui/core';
import { StyleRules } from '@material-ui/core/styles';
import 'codemirror/lib/codemirror.css';
import 'codemirror/theme/idea.css';

type Classes = 'container' | 'queryField' | 'table' | 'tableContainer';

export const styles = (_: Theme): StyleRules<Classes> => ({
  container: {
    display: 'flex',
    flexDirection: 'column',
    width: '100%',
    height: '100%',
  },
  queryField: {
    flex: '0 0 120px',
  },
  table: {
    width: 'auto',
  },
  tableContainer: {
    flex: 1,
    overflow: 'scroll',
  },
});
