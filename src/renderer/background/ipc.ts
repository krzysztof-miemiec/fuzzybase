import { registerForIPC } from '../../common/ipc';

export const { listen, send } = registerForIPC();
