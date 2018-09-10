-- NEGATE
CREATE OR REPLACE FUNCTION minus(trapezoidal_function) RETURNS trapezoidal_function
  AS './operators.so', 'minus_f' LANGUAGE 'c';
CREATE OPERATOR - (rightarg = trapezoidal_function, procedure = minus);

-- SUM
CREATE OR REPLACE FUNCTION sum(trapezoidal_function, trapezoidal_function) RETURNS trapezoidal_function
  AS './operators.so', 'f_sum_f' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION sum(trapezoidal_function, float8) RETURNS trapezoidal_function
  AS './operators.so', 'f_sum_r' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION sum(float8, trapezoidal_function) RETURNS trapezoidal_function
  AS './operators.so', 'r_sum_f' LANGUAGE 'c';

CREATE OPERATOR + (leftarg = trapezoidal_function, rightarg = trapezoidal_function, procedure = sum);
CREATE OPERATOR + (leftarg = trapezoidal_function, rightarg = float8, procedure = sum);
CREATE OPERATOR + (leftarg = float8, rightarg = trapezoidal_function, procedure = sum);

-- SUBTRACT
CREATE OR REPLACE FUNCTION sub(trapezoidal_function, trapezoidal_function)
  RETURNS trapezoidal_function AS './operators.so', 'f_sub_f' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION sub(trapezoidal_function, float8)
  RETURNS trapezoidal_function AS './operators.so', 'f_sub_r' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION sub(float8, trapezoidal_function)
  RETURNS trapezoidal_function AS './operators.so', 'r_sub_f' LANGUAGE 'c';

CREATE OPERATOR - (leftarg = trapezoidal_function, rightarg = trapezoidal_function, procedure = sub);
CREATE OPERATOR - (leftarg = trapezoidal_function, rightarg = float8, procedure = sub);
CREATE OPERATOR - (leftarg = float8, rightarg = trapezoidal_function, procedure = sub);

-- MULTIPLY
CREATE OR REPLACE FUNCTION mul(trapezoidal_function, trapezoidal_function) RETURNS trapezoidal_function
  AS './operators.so', 'f_mul_f' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION mul(trapezoidal_function, float8) RETURNS trapezoidal_function
  AS './operators.so', 'f_mul_r' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION mul(float8, trapezoidal_function) RETURNS trapezoidal_function
  AS './operators.so', 'r_mul_f' LANGUAGE 'c';

CREATE OPERATOR * (leftarg = trapezoidal_function, rightarg = trapezoidal_function, procedure = mul);
CREATE OPERATOR * (leftarg = trapezoidal_function, rightarg = float8, procedure = mul);
CREATE OPERATOR * (leftarg = float8, rightarg = trapezoidal_function, procedure = mul);

-- DIVIDE
CREATE OR REPLACE FUNCTION div(trapezoidal_function, trapezoidal_function) RETURNS trapezoidal_function
  AS './operators.so', 'f_div_f' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION div(trapezoidal_function, float8) RETURNS trapezoidal_function
  AS './operators.so', 'f_div_r' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION div(float8, trapezoidal_function) RETURNS trapezoidal_function
  AS './operators.so', 'r_div_f' LANGUAGE 'c';

CREATE OPERATOR / (leftarg = trapezoidal_function, rightarg = trapezoidal_function, procedure = div);
CREATE OPERATOR / (leftarg = trapezoidal_function, rightarg = float8, procedure = div);
CREATE OPERATOR / (leftarg = float8, rightarg = trapezoidal_function, procedure = div);

-- MIN/MAX
CREATE OR REPLACE FUNCTION max(trapezoidal_function, trapezoidal_function) RETURNS trapezoidal_function
  AS './operators.so', 'trapezoidal_functionmax' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION min(trapezoidal_function, trapezoidal_function) RETURNS trapezoidal_function
  AS './operators.so', 'trapezoidal_functionmin' LANGUAGE 'c';
 

-- **** funkcje i operator relacyjne *************

-- EQUALS
CREATE OR REPLACE FUNCTION is_equal(trapezoidal_function, trapezoidal_function) RETURNS bool
  AS './operators.so', 'is_equal' LANGUAGE 'c';
CREATE OPERATOR = (leftarg = trapezoidal_function, rightarg = trapezoidal_function, procedure = is_equal);

-- LESS THAN
CREATE OR REPLACE FUNCTION is_lower(trapezoidal_function, trapezoidal_function) RETURNS bool
  AS './operators.so', 'is_lower' LANGUAGE 'c';
CREATE OPERATOR < (leftarg = trapezoidal_function, rightarg = trapezoidal_function, procedure = is_lower);

-- LESS THAN OR EQUAL
CREATE OR REPLACE FUNCTION is_lower_equal(trapezoidal_function, trapezoidal_function) RETURNS bool
  AS './operators.so', 'is_lower_equal' LANGUAGE 'c';
CREATE OPERATOR <= (leftarg = trapezoidal_function, rightarg = trapezoidal_function, procedure = is_lower_equal);

-- GREATER THAN
CREATE OR REPLACE FUNCTION is_greater(trapezoidal_function, trapezoidal_function) RETURNS bool
  AS './operators.so', 'is_greater' LANGUAGE 'c';
CREATE OPERATOR > (leftarg = trapezoidal_function, rightarg = trapezoidal_function, procedure = is_greater);

-- GREATER THAN OR EQUAL
CREATE OR REPLACE FUNCTION is_greater_equal(trapezoidal_function, trapezoidal_function) RETURNS bool
  AS './operators.so', 'is_greater_equal' LANGUAGE 'c';
CREATE OPERATOR >= (leftarg = trapezoidal_function, rightarg = trapezoidal_function, procedure = is_greater_equal);

-- NOT EQUAL
CREATE OR REPLACE FUNCTION not_equal(trapezoidal_function, trapezoidal_function) RETURNS bool
  AS './operators.so', 'not_equal' LANGUAGE 'c';
CREATE OPERATOR <> (leftarg = trapezoidal_function, rightarg = trapezoidal_function, procedure = not_equal);
