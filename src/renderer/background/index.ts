import { registerForIPC } from '../../common/ipc';

const { listen } = registerForIPC();

listen().subscribe(action => {
  console.log(action);
});
