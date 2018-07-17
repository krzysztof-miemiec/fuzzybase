import { ActionsObservable, combineEpics } from 'redux-observable';
import { delay, map } from 'rxjs/operators';
import { R } from '../../../../common/resources';
import {
  hideSnackbar,
  HideSnackbarAction,
  LAYOUT_ACTIONS,
  LayoutAction,
  removeSnackbar,
  ShowSnackbarAction
} from './layout.actions';

const showSnackbar$ = (action$: ActionsObservable<LayoutAction>) => action$
  .ofType<ShowSnackbarAction>(LAYOUT_ACTIONS.SHOW_SNACKBAR)
  .pipe(
    delay(R.timing.snackbarDuration),
    map(action => hideSnackbar(action.id))
  );

const hideSnackbar$ = (action$: ActionsObservable<LayoutAction>) => action$
  .ofType<HideSnackbarAction>(LAYOUT_ACTIONS.HIDE_SNACKBAR)
  .pipe(
    delay(R.timing.animationDuration),
    map(action => removeSnackbar(action.id))
  );

export const layoutEpics = combineEpics(
  showSnackbar$,
  hideSnackbar$
);
