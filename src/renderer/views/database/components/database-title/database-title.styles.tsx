import { R } from '../../../../../common/resources';
import { createStyles } from '../../../../app.styles';

export const styles = createStyles({
  container: {
    display: 'flex',
    flexFlow: 'column',
    padding: R.dimen.spacing * 2,
    '&:hover': {
      backgroundColor: R.color.semiLightGray,
    },
  },
  highlightedContainer: {
    backgroundColor: R.color.semiLightGray,
  },
  title: {
    color: R.color.white,
    fontSize: R.fontSize.bolder,
    fontWeight: 700,
  },
  subtitle: {
    color: R.color.white,
    opacity: 0.6,
    fontSize: R.fontSize.normal,
    fontWeight: 400,
  },
});
