import { WindowName } from '../common/window';

process.on('uncaughtException', error => {
  console.error(error);
});

const args = JSON.parse(decodeURIComponent(window.location.hash.replace(/^#/, '')));
const windowName = process.env.windowName = args.name;

switch (windowName) {
  case WindowName.APP:
    import('./app/index');
    break;
  case WindowName.BACKGROUND:
    import('./background/index');
    break;
  default:
    throw new Error(`Invalid window name '${windowName}'.`);
}
console.log(windowName);
