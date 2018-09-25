import { R } from '../../../../../common/resources';
import { createStyles } from '../../../../app.styles';

export const styles = createStyles({
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
