import { R } from '../../../../../common/resources';
import { createStyles, draggable, noDraggable } from '../../../../app.styles';

export const styles = createStyles({
  container: {
    ...noDraggable,
    display: 'grid',
    height: '100%',
    gridTemplateRows: `${R.dimen.toolbarHeight}px 1fr`,
    gridTemplateColumns: `${R.dimen.sidebarWidth}px 1fr`,
  },
  sidebar: {
    gridRowStart: 1,
    gridRowEnd: 3,
    gridColumn: 1,
    display: 'flex',
    flexFlow: 'column',
    flex: `0 0 ${R.dimen.sidebarWidth}px`,
    backgroundColor: R.color.sidebar,
  },
  sidebarContent: {
    flex: 1,
    overflowY: 'scroll',
  },
  content: {
    display: 'grid',
    gridTemplateColumns: '1fr',
    gridTemplateRows: '1fr',
    gridRow: 2,
    gridColumn: 2,
  },
  toolbar: {
    gridRow: 1,
    gridColumn: 2,
    borderBottom: `solid 1px ${R.color.lightGray}`,
    ...draggable,
  },
});
