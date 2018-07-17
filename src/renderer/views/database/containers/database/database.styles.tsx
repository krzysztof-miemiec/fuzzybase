import { StyleRules } from '@material-ui/core/styles';
import { R } from '../../../../../common/resources';

type Classes =
  | 'container'
  | 'column'
  | 'sidebar'
  | 'content'
  | 'toolbar';

export const styles = (): StyleRules<Classes> => ({
  container: {
    display: 'flex',
    flexFlow: 'row nowrap',
    height: '100%',
  },
  column: {
    flex: 1,
    display: 'flex',
    flexFlow: 'column',
  },
  sidebar: {
    flex: `0 0 ${R.dimen.sidebarWidth}px`,
    backgroundColor: R.color.sidebar,
  },
  content: {
    flex: 1,
  },
  toolbar: {
    flex: `0 0 ${R.dimen.toolbarHeight}px`,
    borderBottom: `solid 1px ${R.color.lightGray}`,
  },
});
