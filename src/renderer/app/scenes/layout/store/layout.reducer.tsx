import { LAYOUT_ACTIONS, LayoutAction } from './layout.actions';
import { initialState, LayoutState } from './layout.state';

const baseReducer = (state: void | LayoutState, action: LayoutAction): LayoutState => {
  if (!state) {
    state = initialState;
  }
  switch (action.type) {
    case LAYOUT_ACTIONS.SHOW_SNACKBAR:
      return {
        ...state,
        snackbar: { isOpen: true, action: action.action, actionTitle: action.actionTitle, message: action.message },
      };
    case LAYOUT_ACTIONS.HIDE_SNACKBAR:
      return {
        ...state,
        snackbar: { isOpen: false },
      };
    case LAYOUT_ACTIONS.OPEN_DRAWER:
      return {
        ...state,
        isDrawerOpen: true,
      };
    case LAYOUT_ACTIONS.CLOSE_DRAWER:
      return {
        ...state,
        isDrawerOpen: false,
      };
    default:
      return {
        ...state,
      };
  }
};

export const reducer = baseReducer;
