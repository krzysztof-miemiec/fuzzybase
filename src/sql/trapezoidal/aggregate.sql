-- SUM Aggregate function
CREATE AGGREGATE sum(BASETYPE=trapezoidal_function, STYPE=trapezoidal_function, SFUNC=sum, INITCOND='0/0~0\\0');

-- MAX Aggregate function
CREATE OR REPLACE FUNCTION state_max(trapezoidal_function_ext, trapezoidal_function) RETURNS trapezoidal_function_ext
AS 'fuzzy', 'pg_state_max' LANGUAGE 'c';

CREATE AGGREGATE max(BASETYPE=trapezoidal_function, STYPE=trapezoidal_function_ext, SFUNC=state_max,
  FINALFUNC=to_trapezoidal_function, INITCOND='0|0');

-- MIN Aggregate function
CREATE OR REPLACE FUNCTION state_min(trapezoidal_function_ext, trapezoidal_function) RETURNS trapezoidal_function_ext
AS 'fuzzy', 'pg_state_min' LANGUAGE 'c';

CREATE AGGREGATE min(BASETYPE=trapezoidal_function, STYPE=trapezoidal_function_ext, SFUNC=state_min,
  FINALFUNC=to_trapezoidal_function, INITCOND='0|0');

-- AVG Aggregate function
CREATE OR REPLACE FUNCTION final_avg(trapezoidal_function_ext) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_final_avg' LANGUAGE 'c';

CREATE OR REPLACE FUNCTION state_avg(trapezoidal_function_ext, trapezoidal_function) RETURNS trapezoidal_function_ext
  AS 'fuzzy', 'pg_state_avg' LANGUAGE 'c';

CREATE AGGREGATE avg(BASETYPE=trapezoidal_function, STYPE=trapezoidal_function_ext, SFUNC=state_avg, FINALFUNC=final_avg, INITCOND='0|0/0~0\\0');

-- Percentage aggregate functions
CREATE OR REPLACE FUNCTION percentage_almost_none(twoint) RETURNS float8
  AS 'fuzzy', 'pg_percentage_almost_none' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION percentage_almost_all(twoint) RETURNS float8 
  AS 'fuzzy', 'pg_percentage_almost_all' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION percentage_about_a_quarter(twoint) RETURNS float8 
  AS 'fuzzy', 'pg_percentage_about_a_quarter' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION percentage_about_a_third(twoint) RETURNS float8 
  AS 'fuzzy', 'pg_percentage_about_a_third' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION percentage_about_half(twoint) RETURNS float8 
  AS 'fuzzy', 'pg_percentage_about_half' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION percentage_about_two_thirds(twoint) RETURNS float8 
  AS 'fuzzy', 'pg_percentage_about_two_thirds' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION percentage_about_three_quarters(twoint) RETURNS float8 
  AS 'fuzzy', 'pg_percentage_about_three_quarters' LANGUAGE 'c';

CREATE AGGREGATE almost_none(BASETYPE=bool, SFUNC=state_percentage, STYPE=twoint,
  FINALFUNC=percentage_almost_none, INITCOND='0,0');

CREATE AGGREGATE almost_all(BASETYPE=bool, SFUNC=state_percentage, STYPE=twoint,
  FINALFUNC=percentage_almost_all, INITCOND='0,0');

CREATE AGGREGATE about_a_quarter(BASETYPE=bool, SFUNC=state_percentage, STYPE=twoint,
  FINALFUNC=percentage_about_a_quarter, INITCOND='0,0');

CREATE AGGREGATE about_a_third(BASETYPE=bool, SFUNC=state_percentage, STYPE=twoint,
  FINALFUNC=percentage_about_a_third, INITCOND='0,0');

CREATE AGGREGATE about_half(BASETYPE=bool, SFUNC=state_percentage, STYPE=twoint,
  FINALFUNC=percentage_about_half, INITCOND='0,0');

CREATE AGGREGATE about_two_thirds(BASETYPE=bool, SFUNC=state_percentage, STYPE=twoint,
  FINALFUNC=percentage_about_two_thirds, INITCOND='0,0');

CREATE AGGREGATE about_three_quarters(BASETYPE=bool, SFUNC=state_percentage, STYPE=twoint,
  FINALFUNC=percentage_about_three_quarters, INITCOND='0,0');
