-- Zadeh operators

CREATE OR REPLACE FUNCTION max(float8, float8) RETURNS float8
  AS './general.so', 'max' LANGUAGE 'c' ;

CREATE OPERATOR ||| (LEFTARG = float8, RIGHTARG = float8, PROCEDURE = max);


CREATE OR REPLACE FUNCTION min(float8, float8) RETURNS float8
  AS './general.so', 'min' LANGUAGE 'c' ;

CREATE OPERATOR &&& (LEFTARG = float8, RIGHTARG = float8, PROCEDURE = min);


CREATE OR REPLACE FUNCTION negdm(float8) RETURNS float8
  AS './general.so', 'neg_dm' LANGUAGE 'c' ;

CREATE OPERATOR ~ (RIGHTARG = float8, PROCEDURE = negdm);

-- Percentage

CREATE OR REPLACE FUNCTION twoint_from_string(opaque) RETURNS twoint
  AS './general.so', 'twoint_from_string' LANGUAGE 'C';

CREATE OR REPLACE FUNCTION twoint_to_string(opaque) RETURNS opaque
  AS './general.so', 'twoint_to_string' LANGUAGE 'C';


CREATE TYPE twoint(internallength = 16, input = twoint_from_string, output = twoint_to_string);

CREATE OR REPLACE FUNCTION percentage_sfunc (twoint, bool) RETURNS twoint
  AS '/general.so', 'percentage_sfunc' LANGUAGE 'c' ;

CREATE OR REPLACE FUNCTION percentage_final_func (twoint) RETURNS float8
  AS '/general.so', 'percentage_final_func' LANGUAGE 'c' ;

CREATE AGGREGATE percentage(BASETYPE = bool, sfunc = percentage_sfunc, stype = twoint,
                              FINALFUNC = percentage_final_func, INITCOND = '0,0' ) ;

