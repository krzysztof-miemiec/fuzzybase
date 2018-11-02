import { createStyles } from '../../../../app.styles';
import { R } from '../../../../../common/resources';

const border = '1px solid #999';

export const styles = createStyles({
  container: {
    position: 'absolute',
    left: 0,
    right: 0,
    top: 0,
    bottom: 0,
    overflow: 'scroll',
  },
  table: {
    position: 'relative',
    display: 'table',
  },
  tableHeader: {
    display: 'table-header-group',
    background: '#EEE',
  },
  tableRows: {
    display: 'table-row-group',
  },
  tableRow: {
    display: 'table-row',
  },
  tableHeadRow: {
    display: 'table-header-group',
    ['& $tableCell' as any]: {
      borderTop: border,
    },
  },
  tableCell: {
    display: 'table-cell',
    padding: R.dimen.spacing / 4,
    borderBottom: border,
    borderRight: border,
    ['& :first' as any]: {
      borderLeft: border,
    },
  },
});
