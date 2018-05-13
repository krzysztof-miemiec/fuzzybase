export interface SnackbarState {
  id: string;
  isOpen: boolean;
  message?: string;
  action?: any;
  actionTitle?: string;
}

export interface LayoutState {
  isDrawerOpen: boolean;
  snackbars: SnackbarState[];
}

export const initialState: LayoutState = {
  isDrawerOpen: false,
  snackbars: [],
};
