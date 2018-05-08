import { Config } from '../common/config';
import { WindowName } from '../common/window';
import './main.css';

(window as any).ELECTRON_DISABLE_SECURITY_WARNINGS = Config.IS_DEV;

switch (Config.WINDOW_NAME) {
  case WindowName.APP:
    import('./app/index');
    break;
  case WindowName.BACKGROUND:
    import('./background/index');
    break;
  default:
    throw new Error(`Invalid window name '${Config.WINDOW_NAME}'.`);
}
