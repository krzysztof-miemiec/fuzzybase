import { StyleRules } from '@material-ui/core/styles';
import { R } from '../../../../../common/resources';

type Classes = 'container' | 'draggable';

export const styles = (): StyleRules<Classes> => ({
  container: {
    display: 'flex',
    flex: `0 0 ${R.dimen.drawerWidth}px`,
    flexDirection: 'column',
    width: R.dimen.drawerWidth,
    backgroundColor: R.color.drawer,
  },
  draggable: {
    height: R.dimen.titleBarPadding,
    '-webkit-app-region': 'drag',
  },
});
