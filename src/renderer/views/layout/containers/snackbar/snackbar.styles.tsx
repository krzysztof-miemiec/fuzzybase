import { R } from '../../../../../common/resources';
import { createStyles, draggable } from '../../../../app.styles';

export const styles = createStyles({
  container: {
    position: 'absolute',
    bottom: 0,
    left: 0,
    display: 'flex',
    flexDirection: 'column-reverse',
  },
  snackbar: {
    position: 'relative',
    padding: R.dimen.spacing,
    display: 'flex',
    justifyContent: 'flex-start',
    left: 0,
    transform: 'none',
  },
  content: {
    flexGrow: 1,
    backgroundColor: R.color.background,
    height: '100%',
    ...draggable,
  },
});
