-- Negate
CREATE OR REPLACE FUNCTION minus(trapezoidal_function) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_minus_f' LANGUAGE 'c';
CREATE OPERATOR - (rightarg=trapezoidal_function, procedure=minus);

-- Sum
CREATE OR REPLACE FUNCTION sum(trapezoidal_function, trapezoidal_function) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_f_sum_f' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION sum(trapezoidal_function, float8) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_f_sum_r' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION sum(float8, trapezoidal_function) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_r_sum_f' LANGUAGE 'c';

CREATE OPERATOR + (leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=sum);
CREATE OPERATOR + (leftarg=trapezoidal_function, rightarg=float8, procedure=sum);
CREATE OPERATOR + (leftarg=float8, rightarg=trapezoidal_function, procedure=sum);

-- Subtract
CREATE OR REPLACE FUNCTION sub(trapezoidal_function, trapezoidal_function)
  RETURNS trapezoidal_function AS 'fuzzy', 'pg_f_sub_f' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION sub(trapezoidal_function, float8)
  RETURNS trapezoidal_function AS 'fuzzy', 'pg_f_sub_r' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION sub(float8, trapezoidal_function)
  RETURNS trapezoidal_function AS 'fuzzy', 'pg_r_sub_f' LANGUAGE 'c';

CREATE OPERATOR - (leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=sub);
CREATE OPERATOR - (leftarg=trapezoidal_function, rightarg=float8, procedure=sub);
CREATE OPERATOR - (leftarg=float8, rightarg=trapezoidal_function, procedure=sub);

-- Multiply
CREATE OR REPLACE FUNCTION mul(trapezoidal_function, trapezoidal_function) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_f_mul_f' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION mul(trapezoidal_function, float8) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_f_mul_r' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION mul(float8, trapezoidal_function) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_r_mul_f' LANGUAGE 'c';

CREATE OPERATOR * (leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=mul);
CREATE OPERATOR * (leftarg=trapezoidal_function, rightarg=float8, procedure=mul);
CREATE OPERATOR * (leftarg=float8, rightarg=trapezoidal_function, procedure=mul);

-- Divide
CREATE OR REPLACE FUNCTION div(trapezoidal_function, trapezoidal_function) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_f_div_f' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION div(trapezoidal_function, float8) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_f_div_r' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION div(float8, trapezoidal_function) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_r_div_f' LANGUAGE 'c';

CREATE OPERATOR / (leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=div);
CREATE OPERATOR / (leftarg=trapezoidal_function, rightarg=float8, procedure=div);
CREATE OPERATOR / (leftarg=float8, rightarg=trapezoidal_function, procedure=div);

-- Min/Max
CREATE OR REPLACE FUNCTION max(trapezoidal_function, trapezoidal_function) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_trapezoidal_function_max' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION min(trapezoidal_function, trapezoidal_function) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_trapezoidal_function_min' LANGUAGE 'c';

-- Equals
CREATE OR REPLACE FUNCTION is_equal(trapezoidal_function, trapezoidal_function) RETURNS bool
  AS 'fuzzy', 'pg_is_equal' LANGUAGE 'c';
CREATE OPERATOR=(leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=is_equal);

-- Less Than
CREATE OR REPLACE FUNCTION is_lower(trapezoidal_function, trapezoidal_function) RETURNS bool
  AS 'fuzzy', 'pg_is_lower' LANGUAGE 'c';
CREATE OPERATOR < (leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=is_lower);

-- Less Than or Equal
CREATE OR REPLACE FUNCTION is_lower_equal(trapezoidal_function, trapezoidal_function) RETURNS bool
  AS 'fuzzy', 'pg_is_lower_equal' LANGUAGE 'c';
CREATE OPERATOR <= (leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=is_lower_equal);

-- Greater Than
CREATE OR REPLACE FUNCTION is_greater(trapezoidal_function, trapezoidal_function) RETURNS bool
  AS 'fuzzy', 'pg_is_greater' LANGUAGE 'c';
CREATE OPERATOR > (leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=is_greater);

-- Greater Than or Equal
CREATE OR REPLACE FUNCTION is_greater_equal(trapezoidal_function, trapezoidal_function) RETURNS bool
  AS 'fuzzy', 'pg_is_greater_equal' LANGUAGE 'c';
CREATE OPERATOR >= (leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=is_greater_equal);

-- Not Equal
CREATE OR REPLACE FUNCTION not_equal(trapezoidal_function, trapezoidal_function) RETURNS bool
  AS 'fuzzy', 'pg_not_equal' LANGUAGE 'c';
CREATE OPERATOR <> (leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=not_equal);
