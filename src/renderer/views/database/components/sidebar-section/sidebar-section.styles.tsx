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
    fontSize: 20,
    flex: '0 0 auto',
    color: R.color.semiLightGray,
    cursor: 'pointer',
    '&:hover': {
      color: R.color.white,
    },
  },
  element: {
    display: 'flex',
    justifyContent: 'center',
    paddingTop: R.dimen.spacing,
    paddingBottom: R.dimen.spacing,
    paddingRight: R.dimen.spacing * 2,
    paddingLeft: R.dimen.spacing * 2,
    cursor: 'pointer',
    '&:hover': {
      backgroundColor: R.color.gray,
      '& $elementIcon': {
        visibility: 'visible',
      },
    },
  },
  elementText: {
    flex: 1,
    color: R.color.lightGray,
    minHeight: '1.25em',
    whiteSpace: 'nowrap',
    overflow: 'hidden',
    textOverflow: 'ellipsis',
  },
  elementTextHint: {
    color: R.color.semiLightGray,
  },
  elementIcon: {
    visibility: 'hidden',
  },
});
