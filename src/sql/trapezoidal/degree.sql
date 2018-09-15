-- Degree

-- FLOAT8, TF
CREATE OR REPLACE FUNCTION degree(float8, trapezoidal_function) RETURNS float8
  AS 'fuzzy', 'pg_degreerf' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OPERATOR ~= (leftarg=float8, rightarg=trapezoidal_function, procedure=degree);

-- TF, FLOAT8
CREATE OR REPLACE FUNCTION degree(trapezoidal_function, float8) RETURNS float8
  AS 'fuzzy', 'pg_degreefr' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OPERATOR ~= (leftarg=trapezoidal_function, rightarg=float8, procedure=degree);

-- TF, TF
CREATE OR REPLACE FUNCTION degreeff(trapezoidal_function, trapezoidal_function) RETURNS float8
  AS 'fuzzy', 'pg_degreeff' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OPERATOR ~= (leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=degreeff);
