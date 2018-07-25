import 'codemirror/lib/codemirror.css';
import 'codemirror/theme/idea.css';
import { R } from '../../../../common/resources';
import { createStyles } from '../../../app.styles';

export const styles = createStyles({
  container: {
    display: 'grid',
    gridRow: 1,
    gridColumn: 1,
    gridTemplateRows: 'auto 1fr',
  },
  queryField: {
    gridRow: 1,
    minHeight: 60,
    marginLeft: R.dimen.spacing,
    marginRight: R.dimen.spacing,
    marginTop: R.dimen.spacing,
  },
  table: {
    position: 'absolute',
    left: 0,
    right: 0,
    top: 0,
    bottom: 0,
    overflow: 'scroll',
  },
  tableContainer: {
    position: 'relative',
    gridRow: 2,
  },
});
