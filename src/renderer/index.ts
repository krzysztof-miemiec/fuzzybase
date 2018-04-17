import { WindowName } from '../common/window';

const args = JSON.parse(decodeURIComponent(window.location.hash.replace(/^#/, '')));

switch (args.name) {
  case WindowName.APP:
    import('./app/index');
    break;
  case WindowName.BACKGROUND:
    import('./background/index');
    break;
  default:
    throw new Error(`Invalid window name '${args.name}'.`);
}
console.log(args.name);
