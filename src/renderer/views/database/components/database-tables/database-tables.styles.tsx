import { StyleRules } from '@material-ui/core/styles';
import { R } from '../../../../../common/resources';

type Classes =
  | 'container'
  | 'titleContainer'
  | 'title'
  | 'icon';

export const styles = (): StyleRules<Classes> => ({
  container: {
    display: 'flex',
    flexFlow: 'column',
    padding: R.dimen.spacing * 2,
  },
  titleContainer: {
    display: 'flex',
    flexFlow: 'row nowrap',
  },
  title: {
    flex: 1,
    color: R.color.white,
    fontSize: R.fontSize.bolder,
    fontWeight: 700,
  },
  icon: {
    color: R.color.white,
  },
});
