export interface SnackbarState {
  isOpen: boolean;
  message?: string;
  action?: any;
  actionTitle?: string;
}

export interface LayoutState {
  isDrawerOpen: boolean;
  snackbar: SnackbarState;
}

export const initialState: LayoutState = {
  isDrawerOpen: false,
  snackbar: {
    isOpen: false,
  },
};
