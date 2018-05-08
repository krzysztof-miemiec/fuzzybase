import { registerForIPC } from '../../common/ipc';

export const { listen, send, sendAction$ } = registerForIPC();
