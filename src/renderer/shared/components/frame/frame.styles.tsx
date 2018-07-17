import { StyleRules } from '@material-ui/core/styles';
import { R } from '../../../../common/resources';

type Classes =
  | 'container'
  | 'frame'
  | 'footer'
  | 'link'
  | 'content'
  | 'header'
  | 'headerText';

export const styles = (): StyleRules<Classes> => ({
  container: {
    display: 'flex',
    flexFlow: 'column',
    alignItems: 'center',
    justifyContent: 'center',
    padding: R.dimen.spacing * 4,
  },
  frame: {
    display: 'flex',
    flexFlow: 'column',
    background: R.color.white,
    borderRadius: R.dimen.corner,
    margin: R.dimen.spacing * 4,
    '-webkit-app-region': 'no-drag',
  },
  link: {
    textDecoration: 'underline',
    '&:hover': {
      color: R.color.accent,
    },
  },
  header: {
    display: 'flex',
    flex: `0 0 ${R.dimen.headerHeight}px`,
    paddingLeft: R.dimen.spacing * 3,
    paddingRight: R.dimen.spacing * 3,
    backgroundColor: R.color.primary,
    borderTopLeftRadius: R.dimen.corner,
    borderTopRightRadius: R.dimen.corner,
    alignItems: 'center',
    justifyContent: 'center',
  },
  headerText: {
    color: R.color.white,
  },
  content: {
    flex: 1,
    display: 'flex',
    flexFlow: 'column',
    padding: R.dimen.spacing * 2,
  },
  footer: {

  },
});
