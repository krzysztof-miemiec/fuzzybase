-- Zadeh operators

CREATE OR REPLACE FUNCTION max(float8, float8) RETURNS float8
  AS 'fuzzy', 'max' LANGUAGE 'c';

CREATE OPERATOR ||| (LEFTARG=float8, RIGHTARG=float8, PROCEDURE=max);


CREATE OR REPLACE FUNCTION min(float8, float8) RETURNS float8
  AS 'fuzzy', 'min' LANGUAGE 'c';

CREATE OPERATOR &&& (LEFTARG=float8, RIGHTARG=float8, PROCEDURE=min);


CREATE OR REPLACE FUNCTION negdm(float8) RETURNS float8
  AS 'fuzzy', 'neg_dm' LANGUAGE 'c';

CREATE OPERATOR ~ (RIGHTARG=float8, PROCEDURE=negdm);

-- Percentage

CREATE OR REPLACE FUNCTION twoint_from_string(opaque) RETURNS twoint
  AS 'fuzzy', 'twoint_from_string' LANGUAGE 'c';

CREATE OR REPLACE FUNCTION twoint_to_string(opaque) RETURNS opaque
  AS 'fuzzy', 'twoint_to_string' LANGUAGE 'c';

CREATE TYPE twoint(internallength=16, input=twoint_from_string, output=twoint_to_string);

CREATE OR REPLACE FUNCTION state_percentage (twoint, bool) RETURNS twoint
  AS 'fuzzy', 'state_percentage' LANGUAGE 'c';

CREATE OR REPLACE FUNCTION final_percentage (twoint) RETURNS float8
  AS 'fuzzy', 'final_percentage' LANGUAGE 'c';

CREATE AGGREGATE percentage(BASETYPE=bool, sfunc=state_percentage, stype=twoint,
  FINALFUNC=final_percentage, INITCOND='0,0');
