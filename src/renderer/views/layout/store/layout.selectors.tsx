import { AppState } from '../../../store';
import { LayoutState } from './layout.state';

export const getLayoutState = (state: AppState) => state.layout;

export const getSnackbarsState = (state: LayoutState) => state.snackbars;

export const isDrawerOpen = (state: LayoutState) => state.isDrawerOpen;
