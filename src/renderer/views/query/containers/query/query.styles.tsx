import 'codemirror/lib/codemirror.css';
import 'codemirror/theme/idea.css';
import { createStyles } from '../../../../app.styles';

export const styles = createStyles({
  container: {
    display: 'grid',
    gridRow: 1,
    gridColumn: 1,
    gridTemplateRows: 'auto 1fr',
  },
  queryField: {
    gridRow: 1,
    minHeight: 160,
  },
  tableContainer: {
    position: 'relative',
    gridRow: 2,
  },
});
