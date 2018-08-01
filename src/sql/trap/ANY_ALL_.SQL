--**************funkcje ogolne wykorzystywane przez zapytania zagniezdzone***********
--rozszerzanie typu ftrapezium o stopien defuzyfikacji


CREATE OR REPLACE FUNCTION to_fext_equal( ftrapezium, float8) RETURNS ftrapeziumext 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'to_fext_equal' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION to_fext_not_equal( ftrapezium, float8) RETURNS ftrapeziumext 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'to_fext_not_equal' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION to_fext_greater( ftrapezium, float8) RETURNS ftrapeziumext 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'to_fext_greater' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION to_fext_greater_equal( ftrapezium, float8) RETURNS ftrapeziumext 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'to_fext_greater_equal' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION to_fext_lower( ftrapezium, float8) RETURNS ftrapeziumext 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'to_fext_lower' LANGUAGE 'c' ;
CREATE OR REPLACE FUNCTION to_fext_lower_equal( ftrapezium, float8) RETURNS ftrapeziumext 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'to_fext_lower_equal' LANGUAGE 'c' ;

CREATE OPERATOR *= ( leftarg = ftrapezium, rightarg = float8, procedure = to_fext_equal ) ;
CREATE OPERATOR *<> ( leftarg = ftrapezium, rightarg = float8, procedure = to_fext_not_equal ) ;
CREATE OPERATOR *> ( leftarg = ftrapezium, rightarg = float8, procedure = to_fext_greater ) ;
CREATE OPERATOR *>= ( leftarg = ftrapezium, rightarg = float8, procedure = to_fext_greater_equal ) ;
CREATE OPERATOR *< ( leftarg = ftrapezium, rightarg = float8, procedure = to_fext_lower ) ;
CREATE OPERATOR *<= ( leftarg = ftrapezium, rightarg = float8, procedure = to_fext_lower_equal ) ;


--*****************************zapytania z operatoarami ALL, ANY, IN typu (fext, real)********************
-- A
CREATE OR REPLACE FUNCTION defuzzy( ftrapeziumext, float8 ) RETURNS bool 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'defuzzy_A' LANGUAGE 'c' ;
CREATE OPERATOR = ( leftarg = ftrapeziumext, rightarg = float8, procedure = defuzzy ) ;

CREATE OR REPLACE FUNCTION notdefuzzy( ftrapeziumext, float8 ) RETURNS bool 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'not_defuzzy_A' LANGUAGE 'c' ;
CREATE OPERATOR <> ( leftarg = ftrapeziumext, rightarg = float8, procedure = notdefuzzy ) ;


--*****************************zapytania z operatoarami ALL, ANY, IN typu (real, fext)********************
-- B
CREATE OR REPLACE FUNCTION defuzzy( float8, ftrapeziumext ) RETURNS bool 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'defuzzy_B' LANGUAGE 'c' ;
CREATE OPERATOR = ( leftarg = float8 , rightarg = ftrapeziumext, procedure = defuzzy ) ;

CREATE OR REPLACE FUNCTION notdefuzzy( float8, ftrapeziumext ) RETURNS bool 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'not_defuzzy_B' LANGUAGE 'c' ;
CREATE OPERATOR <> ( leftarg = float8, rightarg = ftrapeziumext, procedure = notdefuzzy ) ;


--*****************************zapytania z operatoarami ALL, ANY, IN typu (fext, ft)********************
-- C
CREATE OR REPLACE FUNCTION defuzzy( ftrapeziumext, ftrapezium ) RETURNS bool 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'defuzzy_C' LANGUAGE 'c' ;
CREATE OPERATOR = ( leftarg = ftrapeziumext, rightarg = ftrapezium, procedure = defuzzy ) ;

CREATE OR REPLACE FUNCTION notdefuzzy( ftrapeziumext, ftrapezium ) RETURNS bool 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'not_defuzzy_C' LANGUAGE 'c' ;
CREATE OPERATOR <> ( leftarg = ftrapeziumext, rightarg = ftrapezium, procedure = notdefuzzy ) ;


--*****************************zapytania z operatoarami ALL, ANY, IN typu (ft, fext)********************
-- D
CREATE OR REPLACE FUNCTION defuzzy( ftrapezium, ftrapeziumext ) RETURNS bool 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'defuzzy_D' LANGUAGE 'c' ;
CREATE OPERATOR = ( leftarg = ftrapezium, rightarg = ftrapeziumext, procedure = defuzzy ) ;

CREATE OR REPLACE FUNCTION notdefuzzy( ftrapezium, ftrapeziumext ) RETURNS bool 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'not_defuzzy_D' LANGUAGE 'c' ;
CREATE OPERATOR <> ( leftarg = ftrapezium, rightarg = ftrapeziumext, procedure = notdefuzzy ) ;


