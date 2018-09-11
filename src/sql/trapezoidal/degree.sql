-- Degree

-- FLOAT8, TF
CREATE OR REPLACE FUNCTION degree(float8, trapezoidal_function) RETURNS float8
  AS '../fuzzy.so', 'degreerf' LANGUAGE 'c';
CREATE OPERATOR ~= (leftarg=float8, rightarg=trapezoidal_function, procedure=degree);

-- TF, FLOAT8
CREATE OR REPLACE FUNCTION degree(trapezoidal_function, float8) RETURNS float8
  AS '../fuzzy.so', 'degreefr' LANGUAGE 'c';
CREATE OPERATOR ~= (leftarg=trapezoidal_function, rightarg=float8, procedure=degree);

-- TF, TF
CREATE OR REPLACE FUNCTION degreeotrapezoidal_function(trapezoidal_function, trapezoidal_function) RETURNS float8
  AS '../fuzzy.so', 'degreeotrapezoidal_function' LANGUAGE 'c';
CREATE OPERATOR ~= (leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=degreeotrapezoidal_function);
