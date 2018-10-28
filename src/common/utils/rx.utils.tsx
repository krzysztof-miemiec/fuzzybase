import { OperatorFunction } from 'rxjs';
import { tap } from 'rxjs/operators';

export const debug = <T extends any>(message: string): OperatorFunction<T, T> =>
  tap((element: T) => console.warn(message, element));
