import { StyleRules } from '@material-ui/core/styles';
import { R } from '../../../../common/resources';

type Classes =
  | 'container'
  | 'input'
  | 'label'
  | 'description';
export const styles = (): StyleRules<Classes> => ({
  container: {
    backgroundColor: R.color.inputBackground,
    color: R.color.gray,
    marginBottom: -3 * R.dimen.spacing,
    marginTop: R.dimen.spacing,
    borderTopLeftRadius: R.dimen.corner * 3,
    borderTopRightRadius: R.dimen.corner * 3,
    paddingTop: R.dimen.spacing,
  },
  input: {
    paddingLeft: R.dimen.spacing,
    paddingRight: R.dimen.spacing,
  },
  label: {
    paddingTop: R.dimen.spacing,
    paddingLeft: R.dimen.spacing,
  },
  description: {
    paddingLeft: R.dimen.spacing,
    marginTop: 2 * R.dimen.spacing,
    marginBottom: R.dimen.spacing,
  },
});
