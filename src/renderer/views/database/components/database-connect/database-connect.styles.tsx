import { R } from '../../../../../common/resources';
import { createStyles } from '../../../../app.styles';

export const styles = createStyles({
  link: {
    textDecoration: 'underline',
    '&:hover': {
      color: R.color.accent,
    },
  },
  divider: {
    marginTop: R.dimen.spacing,
    marginBottom: R.dimen.spacing,
    borderBottom: `dashed 1px ${R.color.lightGray}`,
  },
  inputShort: {
    width: 100,
  },
});
