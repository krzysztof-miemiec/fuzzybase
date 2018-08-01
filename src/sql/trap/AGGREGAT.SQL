--************************ Agregat SUM, MIN, MAX ************************************************

----tworzenie funkcji agregujacej dodajacej liczby rozmyte SUM

CREATE AGGREGATE sum( basetype = ftrapezium, stype = ftrapezium, sfunc = sum, initcond = '0/0~0\\0' ) ;

----tworzenie funkcji agregujacej wyznaczajacej maksymalna liczbe rozmyta MAX

CREATE OR REPLACE FUNCTION statemax( ftrapeziumext, ftrapezium ) RETURNS ftrapeziumext
AS '/fuzzy/ftrapezium/ftrapezium.so', 'statemax' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION toftrapezium( ftrapeziumext ) RETURNS ftrapezium
AS '/fuzzy/ftrapezium/ftrapezium.so', 'ftrapeziumext_to_ftrapezium' LANGUAGE 'c' ;

CREATE AGGREGATE max( basetype = ftrapezium, stype = ftrapeziumext, sfunc = statemax, 
  finalfunc = toftrapezium, initcond = '0|0' ) ;

----tworzenie funkcji agregujacej wyznaczajacej minimalna liczbe rozmyta MIN

CREATE OR REPLACE FUNCTION statemin( ftrapeziumext, ftrapezium ) RETURNS ftrapeziumext
AS '/fuzzy/ftrapezium/ftrapezium.so', 'statemin' LANGUAGE 'c' ;


CREATE AGGREGATE min( basetype = ftrapezium, stype = ftrapeziumext, sfunc = statemin, 
  finalfunc = toftrapezium, initcond = '0|0' ) ;




--********************************* AGREGAT AVERAGE ****************************

--funkcje dla operatora AVERAGE

CREATE OR REPLACE FUNCTION finalavg( ftrapeziumext ) RETURNS ftrapezium 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'finalavg' LANGUAGE 'c' ;

CREATE OR REPLACE FUNCTION stateavg( ftrapeziumext, ftrapezium ) RETURNS ftrapeziumext 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'stateavg' LANGUAGE 'c' ;

CREATE AGGREGATE avg( basetype = ftrapezium, stype = ftrapeziumext, sfunc = stateavg, finalfunc = finalavg, initcond = '0|0/0~0\\0' ) ;

-- aggregaty odsetkowe
CREATE OR REPLACE FUNCTION odsetek_prawie_zaden( twoint ) RETURNS float8 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'odsetek_prawie_zaden' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION odsetek_prawie_wszystkie( twoint ) RETURNS float8 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'odsetek_prawie_wszystkie' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION odsetek_okolo_jedna_czwarta( twoint ) RETURNS float8 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'odsetek_okolo_jedna_czwarta' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION odsetek_okolo_jedna_trzecia( twoint ) RETURNS float8 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'odsetek_okolo_jedna_trzecia' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION odsetek_okolo_polowa( twoint ) RETURNS float8 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'odsetek_okolo_polowa' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION odsetek_okolo_dwie_trzecie( twoint ) RETURNS float8 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'odsetek_okolo_dwie_trzecie' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION odsetek_okolo_trzy_czwarte( twoint ) RETURNS float8 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'odsetek_okolo_trzy_czwarte' LANGUAGE 'c' ;

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
