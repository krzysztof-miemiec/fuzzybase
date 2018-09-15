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
