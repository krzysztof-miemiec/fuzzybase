import { registerForIPC } from '../../../common/ipc';

export const { sendToBackground, listen } = registerForIPC();
