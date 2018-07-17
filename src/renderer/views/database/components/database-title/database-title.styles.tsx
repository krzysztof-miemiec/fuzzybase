import { StyleRules } from '@material-ui/core/styles';
import { R } from '../../../../../common/resources';

type Classes =
  | 'container'
  | 'title';

export const styles = (): StyleRules<Classes> => ({
  container: {
    display: 'flex',
    flexFlow: 'column',
    padding: R.dimen.spacing * 2,
  },
  title: {
    color: R.color.white,
    fontSize: R.fontSize.bolder,
    fontWeight: 700,
  },
});
