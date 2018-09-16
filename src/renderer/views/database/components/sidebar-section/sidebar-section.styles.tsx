import { R } from '../../../../../common/resources';
import { createStyles } from '../../../../app.styles';

export const styles = createStyles({
  container: {
    display: 'flex',
    flexFlow: 'column',
  },
  titleContainer: {
    display: 'flex',
    flexFlow: 'row nowrap',
    alignItems: 'center',
    paddingTop: R.dimen.spacing,
    paddingBottom: R.dimen.spacing,
    paddingRight: R.dimen.spacing * 2,
    paddingLeft: R.dimen.spacing * 2,
    '&:hover': {
      '& $title,$icon': {
        color: R.color.white,
      },
    },
  },
  title: {
    flex: 1,
    color: R.color.lightGray,
    fontSize: R.fontSize.bolder,
    whiteSpace: 'nowrap',
    overflow: 'hidden',
    textOverflow: 'ellipsis',
    fontWeight: 700,
  },
  icon: {
    color: R.color.lightGray,
    fontSize: 20,
  },
  element: {
    paddingTop: R.dimen.spacing,
    paddingBottom: R.dimen.spacing,
    paddingRight: R.dimen.spacing * 2,
    paddingLeft: R.dimen.spacing * 2,
    color: R.color.lightGray,
    '&:hover': {
      backgroundColor: R.color.gray,
    },
    minHeight: '1.25em',
    whiteSpace: 'nowrap',
    overflow: 'hidden',
    textOverflow: 'ellipsis',
  },
  elementHint: {
    color: R.color.semiLightGray,
  },
});
