--************************ Agregat SUM, MIN, MAX ************************************************

----tworzenie funkcji agregujacej dodajacej liczby rozmyte SUM

CREATE AGGREGATE sum(basetype = trapezoidal_function, stype = trapezoidal_function, sfunc = sum, initcond = '0/0~0\\0');

----tworzenie funkcji agregujacej wyznaczajacej maksymalna liczbe rozmyta MAX

CREATE OR REPLACE FUNCTION state_max(trapezoidal_function_ext, trapezoidal_function) RETURNS trapezoidal_function_ext
AS '../fuzzy.so', 'state_max' LANGUAGE 'c';

CREATE AGGREGATE max(basetype = trapezoidal_function, stype = trapezoidal_function_ext, sfunc = state_max,
  finalfunc = totrapezoidal_function, initcond = '0|0');

----tworzenie funkcji agregujacej wyznaczajacej minimalna liczbe rozmyta MIN

CREATE OR REPLACE FUNCTION state_min(trapezoidal_function_ext, trapezoidal_function) RETURNS trapezoidal_function_ext
AS '../fuzzy.so', 'state_min' LANGUAGE 'c';


CREATE AGGREGATE min(basetype = trapezoidal_function, stype = trapezoidal_function_ext, sfunc = state_min,
  finalfunc = totrapezoidal_function, initcond = '0|0');

--********************************* AGREGAT AVERAGE ****************************

--funkcje dla operatora AVERAGE

CREATE OR REPLACE FUNCTION final_avg(trapezoidal_function_ext) RETURNS trapezoidal_function
  AS '../fuzzy.so', 'final_avg' LANGUAGE 'c';

CREATE OR REPLACE FUNCTION state_avg(trapezoidal_function_ext, trapezoidal_function) RETURNS trapezoidal_function_ext
  AS '../fuzzy.so', 'state_avg' LANGUAGE 'c';

CREATE AGGREGATE avg(basetype = trapezoidal_function, stype = trapezoidal_function_ext, sfunc = state_avg, finalfunc = final_avg, initcond = '0|0/0~0\\0');

-- aggregaty odsetkowe
CREATE OR REPLACE FUNCTION percentage_almost_none(twoint) RETURNS float8 
  AS '../fuzzy.so', 'percentage_almost_none' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION percentage_almost_all(twoint) RETURNS float8 
  AS '../fuzzy.so', 'percentage_almost_all' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION percentage_about_a_quarter(twoint) RETURNS float8 
  AS '../fuzzy.so', 'percentage_about_a_quarter' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION percentage_about_a_third(twoint) RETURNS float8 
  AS '../fuzzy.so', 'percentage_about_a_third' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION percentage_about_half(twoint) RETURNS float8 
  AS '../fuzzy.so', 'percentage_about_half' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION percentage_about_two_thirds(twoint) RETURNS float8 
  AS '../fuzzy.so', 'percentage_about_two_thirds' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION percentage_about_three_quarters(twoint) RETURNS float8 
  AS '../fuzzy.so', 'percentage_about_three_quarters' LANGUAGE 'c';

CREATE AGGREGATE almost_none(BASETYPE = bool, sfunc = odsetek_sfunc, stype = twoint,
                              FINALFUNC = almost_none, INITCOND = '0,0');

CREATE AGGREGATE almost_all(BASETYPE = bool, sfunc = odsetek_sfunc, stype = twoint,
                              FINALFUNC = almost_all, INITCOND = '0,0');

CREATE AGGREGATE about_a_quarter(BASETYPE = bool, sfunc = odsetek_sfunc, stype = twoint,
                              FINALFUNC = about_a_quarter, INITCOND = '0,0');

CREATE AGGREGATE about_a_third(BASETYPE = bool, sfunc = odsetek_sfunc, stype = twoint,
                              FINALFUNC = about_a_third, INITCOND = '0,0');

CREATE AGGREGATE about_half(BASETYPE = bool, sfunc = odsetek_sfunc, stype = twoint,
                              FINALFUNC = percentage_about_half, INITCOND = '0,0');

CREATE AGGREGATE about_two_thirds(BASETYPE = bool, sfunc = odsetek_sfunc, stype = twoint,
                              FINALFUNC = percentage_about_two_thirds, INITCOND = '0,0');

CREATE AGGREGATE about_three_quarters(BASETYPE = bool, sfunc = odsetek_sfunc, stype = twoint,
                              FINALFUNC = percentage_about_three_quarters, INITCOND = '0,0');
