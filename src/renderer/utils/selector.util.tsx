interface Sel<S, S2, R> {
  (state: S, initialState?: S2): R;
}

export function select<S, S2, A>(
  state: S,
  s1: Sel<S, S2, A>
): A;
export function select<S, S2, A, B>(
  state: S,
  s1: Sel<S, S2, A>, s2: Sel<A, S2, B>
): B;
export function select<S, S2, A, B, C>(
  state: S,
  s1: Sel<S, S2, A>, s2: Sel<A, S2, B>, s3: Sel<B, S2, C>
): C;
export function select<S, S2, A, B, C, D>(
  state: S,
  s1: Sel<S, S2, A>, s2: Sel<A, S2, B>, s3: Sel<B, S2, C>, s4: Sel<C, S2, D>
): D;
export function select<S, S2, A, B, C, D, E>(
  state: S,
  s1: Sel<S, S2, A>, s2: Sel<A, S2, B>, s3: Sel<B, S2, C>, s4: Sel<C, S2, D>, s5: Sel<D, S2, E>
): E;
export function select<S, S2, A, B, C, D, E, F>(
  state: S,
  s1: Sel<S, S2, A>, s2: Sel<A, S2, B>, s3: Sel<B, S2, C>, s4: Sel<C, S2, D>, s5: Sel<D, S2, E>, s6: Sel<E, S2, F>
): F;
export function select<S, S2, A, B, C, D, E, F, G>(
  state: S,
  s1: Sel<S, S2, A>, s2: Sel<A, S2, B>, s3: Sel<B, S2, C>, s4: Sel<C, S2, D>, s5: Sel<D, S2, E>, s6: Sel<E, S2, F>,
  s7: Sel<F, S2, G>
): G;

export function select<S>(rootState: S, ...selectors: Sel<any, S, any>[]) {
  return selectors.reduce(
    (state, selector) => state && selector ? selector(state, rootState) : undefined,
    rootState
  );
}
