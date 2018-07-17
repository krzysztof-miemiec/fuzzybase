import { StyleRules } from '@material-ui/core/styles';
import { R } from '../../../../../common/resources';

type Classes =
  | 'link'
  | 'inputShort'
  | 'divider';

export const styles = (): StyleRules<Classes> => ({
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
