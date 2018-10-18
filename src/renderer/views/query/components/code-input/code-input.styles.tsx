import { createStyles } from '../../../../app.styles';

export const styles = createStyles({
  container: {
    position: 'relative',
  },
  input: {
    position: 'absolute',
    left: 0,
    right: 0,
    top: 0,
    bottom: 0,
    fontSize: 13,
    fontFamily: 'Fira Code',
  },
  functionDecoration: {
    color: '#309080 !important',
  },
  invalidFunctionDecoration: {
    color: 'red !important',
    textDecorationColor: 'red !important',
    textDecoration: 'line-through',
  },
});
