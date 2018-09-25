import { R } from '../../../../../common/resources';
import { createStyles } from '../../../../app.styles';

export const styles = createStyles({
  container: {
    display: 'flex',
    margin: R.dimen.spacing,
    alignItems: 'center',
    flexDirection: 'column',
    '&:hover': {
      '& $iconContainer': {
        backgroundColor: R.color.lightGray,
      },
    },
  },
  iconContainer: {
    borderRadius: R.dimen.corner,
    backgroundColor: R.color.gray,
    width: R.dimen.drawerIconContainer,
    height: R.dimen.drawerIconContainer,
    display: 'flex',
    alignItems: 'center',
    justifyContent: 'center',
  },
  icon: {
    fontSize: R.dimen.drawerIcon,
  },
  text: {
    paddingTop: R.dimen.spacing / 2,
    color: R.color.white,
  },
});
