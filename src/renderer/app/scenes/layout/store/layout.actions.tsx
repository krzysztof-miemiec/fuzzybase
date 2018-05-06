export enum LAYOUT_ACTIONS {
  SHOW_SNACKBAR = 'LAYOUT/SHOW_SNACKBAR',
  HIDE_SNACKBAR = 'LAYOUT/HIDE_SNACKBAR',
  OPEN_DRAWER = 'LAYOUT/OPEN_DRAWER',
  CLOSE_DRAWER = 'LAYOUT/CLOSE_DRAWER',
}

// SHOW_SNACKBAR
export type ShowSnackbarAction = {
  type: LAYOUT_ACTIONS.SHOW_SNACKBAR;
  message: string;
  actionTitle?: string;
  action?: any;
};

export const showSnackbar = (message: string, actionTitle?: string, action?: any): ShowSnackbarAction => ({
  type: LAYOUT_ACTIONS.SHOW_SNACKBAR,
  message,
  action,
  actionTitle,
});

// HIDE_SNACKBAR
export type HideSnackbarAction = {
  type: LAYOUT_ACTIONS.HIDE_SNACKBAR;
};

export const hideSnackbar = (): HideSnackbarAction => ({
  type: LAYOUT_ACTIONS.HIDE_SNACKBAR,
});

// OPEN_DRAWER
export type OpenDrawerAction = {
  type: LAYOUT_ACTIONS.OPEN_DRAWER;
};

export const openDrawer = (): OpenDrawerAction => ({
  type: LAYOUT_ACTIONS.OPEN_DRAWER,
});

// CLOSE_DRAWER
export type CloseDrawerAction = {
  type: LAYOUT_ACTIONS.CLOSE_DRAWER;
};

export const closeDrawer = (): CloseDrawerAction => ({
  type: LAYOUT_ACTIONS.CLOSE_DRAWER,
});

export type LayoutAction =
  | ShowSnackbarAction
  | HideSnackbarAction
  | OpenDrawerAction
  | CloseDrawerAction;
