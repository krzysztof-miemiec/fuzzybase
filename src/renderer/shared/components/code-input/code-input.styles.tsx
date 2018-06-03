import { Theme } from '@material-ui/core';
import { StyleRules } from '@material-ui/core/styles';

type Classes =  'container' | 'input';

export const styles = (_: Theme): StyleRules<Classes> => ({
  container: {
    height: '100%',
    width: '100%',
  },
  input: {
    height: '100%',
    width: '100%',
    fontSize: 13,
  },
});
