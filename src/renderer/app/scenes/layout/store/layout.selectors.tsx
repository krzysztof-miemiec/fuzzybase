import { AppState } from '../../../store';
import { LayoutState } from './layout.state';

export const getLayoutState = (state: AppState) => state.layout;

export const getSnackbarState = (state: LayoutState) => state.snackbar;

export const isDrawerOpen = (state: LayoutState) => state.isDrawerOpen;
