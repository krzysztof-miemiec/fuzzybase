export enum CommunicationActionType {
  LOG = 'LOG',
  STATE_REFLECTION = 'STATE_REFLECTION',
}

export enum LogSource {
  BACKGROUND = 'B',
  MAIN = 'M',
}

export enum LogMethod {
  LOG = 'log',
  WARN = 'warn',
  ERROR = 'error',
}

export interface LogAction {
  type: CommunicationActionType.LOG;
  source: LogSource;
  method: LogMethod;
  message: string;
  optionalParams?: any[];
}

export const log = (
  source: LogSource,
  method: LogMethod,
  message: string,
  optionalParams?: any
): LogAction => ({
  type: CommunicationActionType.LOG,
  source,
  method,
  message,
  optionalParams,
});

export interface StateReflectionAction {
  type: CommunicationActionType.STATE_REFLECTION;
  state: any;
}

export type CommunicationAction =
  | LogAction
  | StateReflectionAction;
