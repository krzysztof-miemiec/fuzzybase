CREATE OR REPLACE FUNCTION trapezoidal_function_abs_cmp(trapezoidal_function, trapezoidal_function) RETURNS int
  AS 'fuzzy', 'pg_trapezoidal_function_abs_cmp' LANGUAGE 'c';

CREATE OPERATOR CLASS trapezoidal_function_abs_ops DEFAULT FOR TYPE trapezoidal_function USING btree AS
  OPERATOR 1 <,
  OPERATOR 2 <=,
  OPERATOR 3 =,
  OPERATOR 4 >=,
  OPERATOR 5 >,
  FUNCTION 1 trapezoidal_function_abs_cmp(trapezoidal_function, trapezoidal_function);
