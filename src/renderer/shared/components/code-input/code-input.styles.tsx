import { R } from '../../../../common/resources';
import { createStyles } from '../../../app.styles';

export const styles = createStyles({
  container: {
    border: `2px solid ${R.color.gray}`,
    borderRadius: R.dimen.corner,
    display: 'flex',
    flexFlow: 'row nowrap',
  },
  input: {
    flex: '1 0 100px',
    display: 'grid',
    padding: R.dimen.spacing,
    background: 'transparent',
    fontSize: 13,
  },
  button: {
    flex: '0 0 48px',
    height: '100%',
    margin: 0,
    padding: R.dimen.spacing,
    fontSize: 20,
    display: 'flex',
    alignItems: 'flex-end',
    color: R.color.gray,
  },
});
