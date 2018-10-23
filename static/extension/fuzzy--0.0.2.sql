-- Fuzzy Extension for PostgreSQL
-- Copyright Krzysztof Miemiec 2018
-- Based on code of Bartosz Dziedzic & Bożena Małysiak-Mrozek

\echo Use "CREATE EXTENSION fuzzy" to load this file. \quit
-- Zadeh operators

CREATE OR REPLACE FUNCTION zadeh_or(float8, float8) RETURNS float8
  AS 'fuzzy', 'pg_max' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OPERATOR ||| (LEFTARG=float8, RIGHTARG=float8, PROCEDURE=zadeh_or);

CREATE OR REPLACE FUNCTION zadeh_and(float8, float8) RETURNS float8
  AS 'fuzzy', 'pg_min' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OPERATOR &&& (LEFTARG=float8, RIGHTARG=float8, PROCEDURE=zadeh_and);

CREATE OR REPLACE FUNCTION zadeh_not(float8) RETURNS float8
  AS 'fuzzy', 'pg_neg_dm' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OPERATOR ~ (RIGHTARG=float8, PROCEDURE=zadeh_not);

-- Percentage

CREATE OR REPLACE FUNCTION twoint_in(cstring) RETURNS twoint
  AS 'fuzzy', 'pg_twoint_in' LANGUAGE 'c' IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION twoint_out(twoint) RETURNS cstring
  AS 'fuzzy', 'pg_twoint_out' LANGUAGE 'c' IMMUTABLE STRICT;

CREATE TYPE twoint(
  internallength=16,
  input=twoint_in,
  output=twoint_out
);

CREATE OR REPLACE FUNCTION state_percentage (twoint, bool) RETURNS twoint
  AS 'fuzzy', 'pg_state_percentage' LANGUAGE 'c';

CREATE OR REPLACE FUNCTION final_percentage (twoint) RETURNS float8
  AS 'fuzzy', 'pg_final_percentage' LANGUAGE 'c';

CREATE AGGREGATE percentage(BASETYPE=bool, sfunc=state_percentage, stype=twoint,
  FINALFUNC=final_percentage, INITCOND='0,0');
-- Trapezoidal Function

CREATE OR REPLACE FUNCTION trapezoidal_function_in(cstring) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_trapezoidal_function_in' LANGUAGE 'c' IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION trapezoidal_function_out(trapezoidal_function) RETURNS cstring
  AS 'fuzzy', 'pg_trapezoidal_function_out' LANGUAGE 'c' IMMUTABLE STRICT;

CREATE TYPE trapezoidal_function(
  internallength=32,
  input=trapezoidal_function_in,
  output=trapezoidal_function_out
);

-- Trapezoidal Function Extended

CREATE OR REPLACE FUNCTION trapezoidal_function_ext_in(cstring) RETURNS trapezoidal_function_ext
  AS 'fuzzy', 'pg_trapezoidal_function_extended_in' LANGUAGE 'c' IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION trapezoidal_function_ext_out(trapezoidal_function_ext) RETURNS cstring
  AS 'fuzzy', 'pg_trapezoidal_function_extended_out' LANGUAGE 'c' IMMUTABLE STRICT;

CREATE TYPE trapezoidal_function_ext(
  internallength=44,
  input=trapezoidal_function_ext_in,
  output=trapezoidal_function_ext_out
);

-- Conversion of FEXT to TF
CREATE OR REPLACE FUNCTION to_trapezoidal_function(trapezoidal_function_ext) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_trapezoidal_function_ext_to_trapezoidal_function' LANGUAGE 'c' IMMUTABLE STRICT;

-- Creation of TF out of it's values
CREATE OR REPLACE FUNCTION about(float8, float8, float8, float8) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about' LANGUAGE 'c' IMMUTABLE STRICT;

-- Adding threshold (extension) to TF
CREATE OR REPLACE FUNCTION to_fext_equal(trapezoidal_function, float8) RETURNS trapezoidal_function_ext
  AS 'fuzzy', 'pg_to_fext_equal' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION to_fext_not_equal(trapezoidal_function, float8) RETURNS trapezoidal_function_ext
  AS 'fuzzy', 'pg_to_fext_not_equal' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION to_fext_greater(trapezoidal_function, float8) RETURNS trapezoidal_function_ext
  AS 'fuzzy', 'pg_to_fext_greater' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION to_fext_greater_equal(trapezoidal_function, float8) RETURNS trapezoidal_function_ext
  AS 'fuzzy', 'pg_to_fext_greater_equal' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION to_fext_lower(trapezoidal_function, float8) RETURNS trapezoidal_function_ext
  AS 'fuzzy', 'pg_to_fext_lower' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION to_fext_lower_equal(trapezoidal_function, float8) RETURNS trapezoidal_function_ext
  AS 'fuzzy', 'pg_to_fext_lower_equal' LANGUAGE 'c' IMMUTABLE STRICT;

CREATE OPERATOR *= (leftarg=trapezoidal_function, rightarg=float8, procedure=to_fext_equal);
CREATE OPERATOR *<> (leftarg=trapezoidal_function, rightarg=float8, procedure=to_fext_not_equal);
CREATE OPERATOR *> (leftarg=trapezoidal_function, rightarg=float8, procedure=to_fext_greater);
CREATE OPERATOR *>= (leftarg=trapezoidal_function, rightarg=float8, procedure=to_fext_greater_equal);
CREATE OPERATOR *< (leftarg=trapezoidal_function, rightarg=float8, procedure=to_fext_lower);
CREATE OPERATOR *<= (leftarg=trapezoidal_function, rightarg=float8, procedure=to_fext_lower_equal);
-- Negate
CREATE OR REPLACE FUNCTION minus(trapezoidal_function) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_minus_f' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OPERATOR - (rightarg=trapezoidal_function, procedure=minus);

-- Sum
CREATE OR REPLACE FUNCTION sum(trapezoidal_function, trapezoidal_function) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_f_sum_f' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION sum(trapezoidal_function, float8) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_f_sum_r' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION sum(float8, trapezoidal_function) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_r_sum_f' LANGUAGE 'c' IMMUTABLE STRICT;

CREATE OPERATOR + (leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=sum);
CREATE OPERATOR + (leftarg=trapezoidal_function, rightarg=float8, procedure=sum);
CREATE OPERATOR + (leftarg=float8, rightarg=trapezoidal_function, procedure=sum);

-- Subtract
CREATE OR REPLACE FUNCTION sub(trapezoidal_function, trapezoidal_function)
  RETURNS trapezoidal_function AS 'fuzzy', 'pg_f_sub_f' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION sub(trapezoidal_function, float8)
  RETURNS trapezoidal_function AS 'fuzzy', 'pg_f_sub_r' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION sub(float8, trapezoidal_function)
  RETURNS trapezoidal_function AS 'fuzzy', 'pg_r_sub_f' LANGUAGE 'c' IMMUTABLE STRICT;

CREATE OPERATOR - (leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=sub);
CREATE OPERATOR - (leftarg=trapezoidal_function, rightarg=float8, procedure=sub);
CREATE OPERATOR - (leftarg=float8, rightarg=trapezoidal_function, procedure=sub);

-- Multiply
CREATE OR REPLACE FUNCTION mul(trapezoidal_function, trapezoidal_function) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_f_mul_f' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION mul(trapezoidal_function, float8) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_f_mul_r' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION mul(float8, trapezoidal_function) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_r_mul_f' LANGUAGE 'c' IMMUTABLE STRICT;

CREATE OPERATOR * (leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=mul);
CREATE OPERATOR * (leftarg=trapezoidal_function, rightarg=float8, procedure=mul);
CREATE OPERATOR * (leftarg=float8, rightarg=trapezoidal_function, procedure=mul);

-- Divide
CREATE OR REPLACE FUNCTION div(trapezoidal_function, trapezoidal_function) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_f_div_f' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION div(trapezoidal_function, float8) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_f_div_r' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION div(float8, trapezoidal_function) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_r_div_f' LANGUAGE 'c' IMMUTABLE STRICT;

CREATE OPERATOR / (leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=div);
CREATE OPERATOR / (leftarg=trapezoidal_function, rightarg=float8, procedure=div);
CREATE OPERATOR / (leftarg=float8, rightarg=trapezoidal_function, procedure=div);

-- Min/Max
CREATE OR REPLACE FUNCTION max(trapezoidal_function, trapezoidal_function) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_trapezoidal_function_max' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION min(trapezoidal_function, trapezoidal_function) RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_trapezoidal_function_min' LANGUAGE 'c' IMMUTABLE STRICT;

-- Equals
CREATE OR REPLACE FUNCTION is_equal(trapezoidal_function, trapezoidal_function) RETURNS bool
  AS 'fuzzy', 'pg_is_equal' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OPERATOR=(leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=is_equal);

-- Less Than
CREATE OR REPLACE FUNCTION is_lower(trapezoidal_function, trapezoidal_function) RETURNS bool
  AS 'fuzzy', 'pg_is_lower' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OPERATOR < (leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=is_lower);

-- Less Than or Equal
CREATE OR REPLACE FUNCTION is_lower_equal(trapezoidal_function, trapezoidal_function) RETURNS bool
  AS 'fuzzy', 'pg_is_lower_equal' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OPERATOR <= (leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=is_lower_equal);

-- Greater Than
CREATE OR REPLACE FUNCTION is_greater(trapezoidal_function, trapezoidal_function) RETURNS bool
  AS 'fuzzy', 'pg_is_greater' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OPERATOR > (leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=is_greater);

-- Greater Than or Equal
CREATE OR REPLACE FUNCTION is_greater_equal(trapezoidal_function, trapezoidal_function) RETURNS bool
  AS 'fuzzy', 'pg_is_greater_equal' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OPERATOR >= (leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=is_greater_equal);

-- Not Equal
CREATE OR REPLACE FUNCTION not_equal(trapezoidal_function, trapezoidal_function) RETURNS bool
  AS 'fuzzy', 'pg_not_equal' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OPERATOR <> (leftarg=trapezoidal_function, rightarg=trapezoidal_function, procedure=not_equal);
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
-- Defuzzification functions

-- FEXT, FLOAT8
CREATE OR REPLACE FUNCTION defuzzy(trapezoidal_function_ext, float8) RETURNS bool
  AS 'fuzzy', 'pg_defuzzy_fext_r' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OPERATOR=(leftarg=trapezoidal_function_ext, rightarg=float8, procedure=defuzzy);

CREATE OR REPLACE FUNCTION notdefuzzy(trapezoidal_function_ext, float8) RETURNS bool
  AS 'fuzzy', 'pg_not_defuzzy_fext_r' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OPERATOR <> (leftarg=trapezoidal_function_ext, rightarg=float8, procedure=notdefuzzy);

-- FLOAT8, FEXT
CREATE OR REPLACE FUNCTION defuzzy(float8, trapezoidal_function_ext) RETURNS bool
  AS 'fuzzy', 'pg_defuzzy_r_fext' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OPERATOR=(leftarg=float8 , rightarg=trapezoidal_function_ext, procedure=defuzzy);

CREATE OR REPLACE FUNCTION notdefuzzy(float8, trapezoidal_function_ext) RETURNS bool
  AS 'fuzzy', 'pg_not_defuzzy_r_fext' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OPERATOR <> (leftarg=float8, rightarg=trapezoidal_function_ext, procedure=notdefuzzy);

-- FEXT, TF
CREATE OR REPLACE FUNCTION defuzzy(trapezoidal_function_ext, trapezoidal_function) RETURNS bool
  AS 'fuzzy', 'pg_defuzzy_fext_ft' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OPERATOR=(leftarg=trapezoidal_function_ext, rightarg=trapezoidal_function, procedure=defuzzy);

CREATE OR REPLACE FUNCTION notdefuzzy(trapezoidal_function_ext, trapezoidal_function) RETURNS bool
  AS 'fuzzy', 'pg_not_defuzzy_fext_ft' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OPERATOR <> (leftarg=trapezoidal_function_ext, rightarg=trapezoidal_function, procedure=notdefuzzy);

-- TF, FEXT
CREATE OR REPLACE FUNCTION defuzzy(trapezoidal_function, trapezoidal_function_ext) RETURNS bool
  AS 'fuzzy', 'pg_defuzzy_ft_fext' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OPERATOR=(leftarg=trapezoidal_function, rightarg=trapezoidal_function_ext, procedure=defuzzy);

CREATE OR REPLACE FUNCTION notdefuzzy(trapezoidal_function, trapezoidal_function_ext) RETURNS bool
  AS 'fuzzy', 'pg_not_defuzzy_ft_fext' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OPERATOR <> (leftarg=trapezoidal_function, rightarg=trapezoidal_function_ext, procedure=notdefuzzy);
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
  AS 'fuzzy', 'pg_percentage_almost_none' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION percentage_almost_all(twoint) RETURNS float8 
  AS 'fuzzy', 'pg_percentage_almost_all' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION percentage_about_a_quarter(twoint) RETURNS float8 
  AS 'fuzzy', 'pg_percentage_about_a_quarter' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION percentage_about_a_third(twoint) RETURNS float8 
  AS 'fuzzy', 'pg_percentage_about_a_third' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION percentage_about_half(twoint) RETURNS float8 
  AS 'fuzzy', 'pg_percentage_about_half' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION percentage_about_two_thirds(twoint) RETURNS float8 
  AS 'fuzzy', 'pg_percentage_about_two_thirds' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION percentage_about_three_quarters(twoint) RETURNS float8 
  AS 'fuzzy', 'pg_percentage_about_three_quarters' LANGUAGE 'c' IMMUTABLE STRICT;

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
-- Percentage linguistic functions
CREATE OR REPLACE FUNCTION almost_none() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_almost_none' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION almost_all() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_almost_all' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_a_quarter() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_a_quarter' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_a_third() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_a_third' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_half() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_half' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_two_thirds() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_two_thirds' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_three_quarters() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_three_quarters' LANGUAGE 'c' IMMUTABLE STRICT;

-- Number linguistic functions
CREATE OR REPLACE FUNCTION about_one() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_one' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_some() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_some' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_a_dozen() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_a_dozen' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_a_few_dozen() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_a_few_dozen' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_a_few_hundred() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_a_few_hundred' LANGUAGE 'c' IMMUTABLE STRICT;

-- Time linguistic functions
CREATE OR REPLACE FUNCTION about_a_minute() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_a_minute' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_a_quarter_of_an_hour() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_a_quarter_of_an_hour' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_an_hour() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_an_hour' LANGUAGE 'c' IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION seconds_to_str(trapezoidal_function) RETURNS TEXT
  AS 'fuzzy', 'pg_seconds_to_str' LANGUAGE 'c' IMMUTABLE STRICT;

-- Date linguistic functions
CREATE OR REPLACE FUNCTION about_a_week() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_a_week' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_a_month() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_a_month' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_a_year() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_a_year' LANGUAGE 'c' IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION days_to_str(trapezoidal_function) RETURNS TEXT
  AS 'fuzzy', 'pg_days_to_str' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION trapezoidal_function_abs_cmp(trapezoidal_function, trapezoidal_function) RETURNS int
  AS 'fuzzy', 'pg_trapezoidal_function_abs_cmp' LANGUAGE 'c';

CREATE OPERATOR CLASS trapezoidal_function_abs_ops DEFAULT FOR TYPE trapezoidal_function USING btree AS
  OPERATOR 1 <,
  OPERATOR 2 <=,
  OPERATOR 3 =,
  OPERATOR 4 >=,
  OPERATOR 5 >,
  FUNCTION 1 trapezoidal_function_abs_cmp(trapezoidal_function, trapezoidal_function);
CREATE SCHEMA IF NOT EXISTS fuzzy;

CREATE TABLE IF NOT EXISTS fuzzy.types (
  id   SERIAL PRIMARY KEY,
  name VARCHAR(64) UNIQUE
);

CREATE TABLE IF NOT EXISTS fuzzy.functions (
  type INT                  NOT NULL,
  fun  TRAPEZOIDAL_FUNCTION NOT NULL,
  name VARCHAR(64),
  FOREIGN KEY (type) REFERENCES fuzzy.types (id) ON DELETE CASCADE,
  UNIQUE (type, name)
);

-- Add Fuzzy type
DROP FUNCTION IF EXISTS add_fuzzy_type(
  type_name VARCHAR(64)
);
CREATE OR REPLACE FUNCTION add_fuzzy_type(
  type_name VARCHAR(64)
) RETURNS fuzzy.types.id%TYPE AS $$
  INSERT INTO fuzzy.types (name) VALUES (type_name) ON CONFLICT DO NOTHING;
  SELECT id FROM fuzzy.types WHERE name=type_name;
$$ LANGUAGE sql VOLATILE;

-- Get fuzzy type by name
DROP FUNCTION IF EXISTS get_fuzzy_type(
  type_name VARCHAR(64)
);
CREATE OR REPLACE FUNCTION get_fuzzy_type(
  type_name VARCHAR(64)
) RETURNS fuzzy.types.id%TYPE AS $$
DECLARE
  type_id fuzzy.types.id%TYPE;
BEGIN
  type_id := (SELECT id FROM fuzzy.types WHERE name=type_name);
  IF type_id IS NULL THEN
    RAISE EXCEPTION 'Can''t find specified fuzzy type. The type "%" does not exist.', type_name
      USING HINT = 'Check if you specified the correct fuzzy type name. See available types by SELECT * FROM get_fuzzy_types();';
  END IF;
  RETURN type_id;
END;
$$ LANGUAGE plpgsql IMMUTABLE STRICT;

-- Add fuzzy function
DROP FUNCTION IF EXISTS add_fuzzy_function(
  type_name VARCHAR(64),
  fuzzy_function TRAPEZOIDAL_FUNCTION,
  range_name VARCHAR(64)
);
CREATE FUNCTION add_fuzzy_function(
  type_name VARCHAR(64),
  fuzzy_function TRAPEZOIDAL_FUNCTION,
  range_name VARCHAR(64) DEFAULT NULL
) RETURNS RECORD AS $$
DECLARE
  type_id fuzzy.types.id%TYPE;
BEGIN
  type_id := (SELECT add_fuzzy_type(type_name));
  INSERT INTO fuzzy.functions VALUES (
    type_id,
    fuzzy_function,
    range_name
  );
  RETURN (type_id, fuzzy_function, range_name);
END;
$$ LANGUAGE plpgsql VOLATILE;

-- Delete fuzzy function by range name
DROP FUNCTION IF EXISTS delete_fuzzy_function(
  type_name VARCHAR(64),
  range_name VARCHAR(64)
);
CREATE FUNCTION delete_fuzzy_function(
  type_name VARCHAR(64),
  range_name VARCHAR(64)
) RETURNS RECORD AS $$
DECLARE
  type_id fuzzy.types.id%TYPE;
BEGIN
  type_id := get_fuzzy_type(type_name);
  DELETE FROM fuzzy.functions WHERE type=type_id AND name=range_name;
  RETURN (type_id, range_name);
END;
$$ LANGUAGE plpgsql VOLATILE;

-- Delete fuzzy function by function value
DROP FUNCTION IF EXISTS delete_fuzzy_function(
  type_name VARCHAR(64),
  func TRAPEZOIDAL_FUNCTION
);
CREATE FUNCTION delete_fuzzy_function(
  type_name VARCHAR(64),
  func TRAPEZOIDAL_FUNCTION
) RETURNS RECORD AS $$
DECLARE
  type_id fuzzy.types.id%TYPE;
BEGIN
  type_id := get_fuzzy_type(type_name);
  DELETE FROM fuzzy.functions WHERE type=type_id AND fun=func;
  RETURN (type_id, func);
END;
$$ LANGUAGE plpgsql VOLATILE;

-- Delete fuzzy function by function value
DROP FUNCTION IF EXISTS delete_fuzzy_type(
  type_name VARCHAR(64)
);
CREATE FUNCTION delete_fuzzy_type(
  type_name VARCHAR(64)
) RETURNS VARCHAR(64) AS $$
DECLARE
  type_id fuzzy.types.id%TYPE;
BEGIN
  type_id := get_fuzzy_type(type_name);
  DELETE FROM fuzzy.types CASCADE WHERE id=type_id;
  RETURN type_name;
END;
$$ LANGUAGE plpgsql VOLATILE;

-- Get all functions for specified fuzzy type
DROP FUNCTION IF EXISTS get_fuzzy_type_functions(
  type_name VARCHAR(64)
);
CREATE FUNCTION get_fuzzy_type_functions(
  type_name VARCHAR(64)
) RETURNS TABLE (
  func  TRAPEZOIDAL_FUNCTION,
  range_name VARCHAR(64)
) AS $$
DECLARE
  type_id fuzzy.types.id%TYPE;
BEGIN
  type_id := get_fuzzy_type(type_name);
  RETURN QUERY SELECT fun, name FROM fuzzy.functions WHERE fuzzy.functions.type=type_id;
END;
$$ LANGUAGE plpgsql IMMUTABLE STRICT;

-- Get the name of the best fitting fuzzy function for specified type and value (the "range name")
DROP FUNCTION IF EXISTS get_fuzzy_name(
  type_name VARCHAR(64),
  input FLOAT8
);
CREATE FUNCTION get_fuzzy_name(
  input FLOAT8,
  type_name VARCHAR(64)

) RETURNS VARCHAR(64) AS $$
DECLARE
  type_id fuzzy.types.id%TYPE;
  deg FLOAT8;
  result_name VARCHAR(64);
BEGIN
  type_id := get_fuzzy_type(type_name);
  SELECT
      degree(input, fun) AS d, name
    INTO
      deg, result_name
    FROM fuzzy.functions
    WHERE type=type_id
    ORDER BY d DESC LIMIT 1;
  IF deg=0 THEN
    RETURN NULL;
  END IF;
  RETURN result_name;
END;
$$ LANGUAGE plpgsql IMMUTABLE STRICT;

CREATE OPERATOR ~> (
  PROCEDURE = get_fuzzy_name,
  LEFTARG = FLOAT8,
  RIGHTARG = VARCHAR(64)
);

-- Get fuzzy function
DROP FUNCTION IF EXISTS get_fuzzy_function(
  type_name VARCHAR(64),
  function_name VARCHAR(64)
);
CREATE FUNCTION get_fuzzy_function(
  type_name VARCHAR(64),
  function_name VARCHAR(64)
) RETURNS TRAPEZOIDAL_FUNCTION AS $$
DECLARE
  type_id fuzzy.types.id%TYPE;
BEGIN
  type_id := get_fuzzy_type(type_name);
  RETURN (SELECT fun
          FROM fuzzy.functions
          WHERE type = type_id AND function_name = name);
END;
$$ LANGUAGE plpgsql IMMUTABLE STRICT;

CREATE OPERATOR |> (
  PROCEDURE = get_fuzzy_function,
  LEFTARG = VARCHAR(64),
  RIGHTARG = VARCHAR(64)
);

-- Get all fuzzy types
DROP FUNCTION IF EXISTS get_fuzzy_types();
CREATE FUNCTION get_fuzzy_types() RETURNS TABLE (
  type_name VARCHAR(64),
  range_names VARCHAR[]
) AS $$
  SELECT
        fts.name AS type_name,
        array_agg(ffs.name) AS range_names
  FROM
       fuzzy.types fts
  LEFT JOIN
      fuzzy.functions ffs ON ffs.type=fts.id
  GROUP BY fts.name;
$$ LANGUAGE sql IMMUTABLE STRICT;

DROP FUNCTION IF EXISTS get_fuzzy_functions();
CREATE FUNCTION get_fuzzy_functions() RETURNS TABLE (
  type_id INT,
  type_name VARCHAR(64),
  name VARCHAR(64),
  fun TRAPEZOIDAL_FUNCTION
) AS $$
  SELECT
    fts.id as type_id,
    fts.name as type_name,
    ffs.name as name,
    ffs.fun as fun
  FROM
    fuzzy.types fts, fuzzy.functions ffs
  WHERE ffs.type=fts.id;
$$ LANGUAGE sql IMMUTABLE STRICT;
