--********************************* wyznaczanie stopnia przynaleznosci *****************************

--tworzenie funkcji wyliczajacej stopien przynaleznoci wartosci rzeczywistej do zbioru rozmytego

CREATE OR REPLACE FUNCTION degree( float8, ftrapezium ) RETURNS float8
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'degreerf' LANGUAGE 'c' ;

CREATE OPERATOR ~= ( leftarg = float8, rightarg = ftrapezium, procedure = degree ) ;

CREATE OR REPLACE FUNCTION degree( ftrapezium, float8 ) RETURNS float8
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'degreefr' LANGUAGE 'c' ;

CREATE OPERATOR ~= ( leftarg = ftrapezium, rightarg = float8, procedure = degree ) ;

--tworzenie funkcji wyznaczajcej stopien przynaleznosci dwoch wyrazow rozmytych

CREATE OR REPLACE FUNCTION degreeoftrapezium( ftrapezium, ftrapezium ) RETURNS float8
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'degreeoftrapezium' LANGUAGE 'c' ;

CREATE OPERATOR ~= ( leftarg = ftrapezium, rightarg = ftrapezium, procedure = degreeoftrapezium ) ;


