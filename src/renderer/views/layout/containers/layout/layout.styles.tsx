import { R } from '../../../../../common/resources';
import { createStyles, draggable } from '../../../../app.styles';

export const styles = createStyles({
  container: {
    display: 'flex',
    zIndex: 1,
    overflow: 'hidden',
    position: 'relative',
    height: '100%',
    width: '100%',
  },
  content: {
    flexGrow: 1,
    backgroundColor: R.color.background,
    height: '100%',
    ...draggable,
  },
});
