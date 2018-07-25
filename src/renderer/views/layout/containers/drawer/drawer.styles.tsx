import { R } from '../../../../../common/resources';
import { createStyles, draggable } from '../../../../app.styles';

export const styles = createStyles({
  container: {
    display: 'flex',
    flex: `0 0 ${R.dimen.drawerWidth}px`,
    flexDirection: 'column',
    width: R.dimen.drawerWidth,
    backgroundColor: R.color.drawer,
  },
  draggable: {
    height: R.dimen.titleBarPadding,
    ...draggable,
  },
});
