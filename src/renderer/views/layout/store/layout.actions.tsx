import uuid from 'uuid/v4';
import { createAction } from '../../../utils/redux.util';

export enum LAYOUT_ACTIONS {
  SHOW_SNACKBAR = 'LAYOUT/SHOW_SNACKBAR',
  HIDE_SNACKBAR = 'LAYOUT/HIDE_SNACKBAR',
  REMOVE_SNACKBAR = 'LAYOUT/REMOVE_SNACKBAR',
  OPEN_DRAWER = 'LAYOUT/OPEN_DRAWER',
  CLOSE_DRAWER = 'LAYOUT/CLOSE_DRAWER',
}

// SHOW_SNACKBAR
export type ShowSnackbarAction = ReturnType<typeof showSnackbar>;
export const showSnackbar = (message: string, actionTitle?: string, action?: any) =>
  createAction(LAYOUT_ACTIONS.SHOW_SNACKBAR, {
    id: uuid(),
    message,
    action,
    actionTitle,
  });

// HIDE_SNACKBAR
export type HideSnackbarAction = ReturnType<typeof hideSnackbar>;
export const hideSnackbar = (id: string) =>
  createAction(LAYOUT_ACTIONS.HIDE_SNACKBAR, { id });

export type RemoveSnackbarAction = ReturnType<typeof removeSnackbar>;
export const removeSnackbar = (id: string) =>
  createAction(LAYOUT_ACTIONS.REMOVE_SNACKBAR, { id });

// OPEN_DRAWER
export type OpenDrawerAction = ReturnType<typeof openDrawer>;
export const openDrawer = () => createAction(LAYOUT_ACTIONS.OPEN_DRAWER);

// CLOSE_DRAWER
export type CloseDrawerAction = ReturnType<typeof closeDrawer>;
export const closeDrawer = () => createAction(LAYOUT_ACTIONS.CLOSE_DRAWER);

export type LayoutAction =
  | ShowSnackbarAction
  | HideSnackbarAction
  | RemoveSnackbarAction
  | OpenDrawerAction
  | CloseDrawerAction;
