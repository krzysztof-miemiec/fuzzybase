--************************ Agregat SUM, MIN, MAX ************************************************

----tworzenie funkcji agregujacej dodajacej liczby rozmyte SUM

CREATE AGGREGATE sum( basetype = trapezoidal_function, stype = trapezoidal_function, sfunc = sum, initcond = '0/0~0\\0' ) ;

----tworzenie funkcji agregujacej wyznaczajacej maksymalna liczbe rozmyta MAX

CREATE OR REPLACE FUNCTION state_max( trapezoidal_function_ext, trapezoidal_function ) RETURNS trapezoidal_function_ext
AS '../fuzzy.so', 'state_max' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION totrapezoidal_function( trapezoidal_function_ext ) RETURNS trapezoidal_function
AS '../fuzzy.so', 'trapezoidal_function_ext_to_trapezoidal_function' LANGUAGE 'c' ;

CREATE AGGREGATE max( basetype = trapezoidal_function, stype = trapezoidal_function_ext, sfunc = state_max,
  finalfunc = totrapezoidal_function, initcond = '0|0' ) ;

----tworzenie funkcji agregujacej wyznaczajacej minimalna liczbe rozmyta MIN

CREATE OR REPLACE FUNCTION state_min( trapezoidal_function_ext, trapezoidal_function ) RETURNS trapezoidal_function_ext
AS '../fuzzy.so', 'state_min' LANGUAGE 'c' ;


CREATE AGGREGATE min( basetype = trapezoidal_function, stype = trapezoidal_function_ext, sfunc = state_min,
  finalfunc = totrapezoidal_function, initcond = '0|0' ) ;




--********************************* AGREGAT AVERAGE ****************************

--funkcje dla operatora AVERAGE

CREATE OR REPLACE FUNCTION final_avg( trapezoidal_function_ext ) RETURNS trapezoidal_function
  AS '../fuzzy.so', 'final_avg' LANGUAGE 'c' ;

CREATE OR REPLACE FUNCTION state_avg( trapezoidal_function_ext, trapezoidal_function ) RETURNS trapezoidal_function_ext
  AS '../fuzzy.so', 'state_avg' LANGUAGE 'c' ;

CREATE AGGREGATE avg( basetype = trapezoidal_function, stype = trapezoidal_function_ext, sfunc = state_avg, finalfunc = final_avg, initcond = '0|0/0~0\\0' ) ;

-- aggregaty odsetkowe
CREATE OR REPLACE FUNCTION odsetek_prawie_zaden( twoint ) RETURNS float8 
  AS '../fuzzy.so', 'odsetek_prawie_zaden' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION odsetek_prawie_wszystkie( twoint ) RETURNS float8 
  AS '../fuzzy.so', 'odsetek_prawie_wszystkie' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION odsetek_okolo_jedna_czwarta( twoint ) RETURNS float8 
  AS '../fuzzy.so', 'odsetek_okolo_jedna_czwarta' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION odsetek_okolo_jedna_trzecia( twoint ) RETURNS float8 
  AS '../fuzzy.so', 'odsetek_okolo_jedna_trzecia' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION odsetek_okolo_polowa( twoint ) RETURNS float8 
  AS '../fuzzy.so', 'odsetek_okolo_polowa' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION odsetek_okolo_dwie_trzecie( twoint ) RETURNS float8 
  AS '../fuzzy.so', 'odsetek_okolo_dwie_trzecie' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION odsetek_okolo_trzy_czwarte( twoint ) RETURNS float8 
  AS '../fuzzy.so', 'odsetek_okolo_trzy_czwarte' LANGUAGE 'c' ;

CREATE AGGREGATE prawie_zaden( BASETYPE = bool, sfunc = odsetek_sfunc, stype = twoint,
                              FINALFUNC = odsetek_prawie_zaden, INITCOND = '0,0' ) ;

CREATE AGGREGATE prawie_wszystkie( BASETYPE = bool, sfunc = odsetek_sfunc, stype = twoint,
                              FINALFUNC = odsetek_prawie_wszystkie, INITCOND = '0,0' ) ;

CREATE AGGREGATE okolo_jedna_czwarta( BASETYPE = bool, sfunc = odsetek_sfunc, stype = twoint,
                              FINALFUNC = odsetek_okolo_jedna_czwarta, INITCOND = '0,0' ) ;

CREATE AGGREGATE okolo_jedna_trzecia( BASETYPE = bool, sfunc = odsetek_sfunc, stype = twoint,
                              FINALFUNC = odsetek_okolo_jedna_trzecia, INITCOND = '0,0' ) ;

CREATE AGGREGATE okolo_polowa( BASETYPE = bool, sfunc = odsetek_sfunc, stype = twoint,
                              FINALFUNC = odsetek_okolo_polowa, INITCOND = '0,0' ) ;

CREATE AGGREGATE okolo_dwie_trzecie( BASETYPE = bool, sfunc = odsetek_sfunc, stype = twoint,
                              FINALFUNC = odsetek_okolo_dwie_trzecie, INITCOND = '0,0' ) ;

CREATE AGGREGATE okolo_trzy_czwarte( BASETYPE = bool, sfunc = odsetek_sfunc, stype = twoint,
                              FINALFUNC = odsetek_okolo_trzy_czwarte, INITCOND = '0,0' ) ;
