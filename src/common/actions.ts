export enum CommunicationActionType {
  LOG = 'LOG',
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

export interface Log {
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
): Log => ({
  type: CommunicationActionType.LOG,
  source,
  method,
  message,
  optionalParams,
});

export type CommunicationAction =
  | Log;
