import { routerActions } from 'react-router-redux';

export { RouterAction } from 'react-router-redux';

export const routerPush = routerActions.push;
export const routerBack = routerActions.goBack;
export const routerForward = routerActions.goForward;
