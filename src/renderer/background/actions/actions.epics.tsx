import { ActionsObservable, combineEpics } from 'redux-observable';
import { ignoreElements, tap } from 'rxjs/operators';
import { send } from '../ipc';

const dispatch$ = (action$: ActionsObservable<any>) => action$
  .pipe(
    tap(action => send(action)),
    ignoreElements()
  );

export const actionsEpics = combineEpics(
  dispatch$
);
