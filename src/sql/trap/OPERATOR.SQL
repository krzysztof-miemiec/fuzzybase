--************ tworzenie funkji about *********************************

CREATE OR REPLACE FUNCTION okolo( float8, float8, float8, float8 ) RETURNS ftrapezium 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'about' LANGUAGE 'c' ;


-- ************** operacje arytmetyczne na liczbach rozmytych ***********************

--suma

CREATE OR REPLACE FUNCTION sum( ftrapezium, ftrapezium ) RETURNS ftrapezium 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'f_sum_f' LANGUAGE 'c' ;
CREATE OPERATOR + ( leftarg = ftrapezium, rightarg = ftrapezium, procedure = sum ) ;

CREATE OR REPLACE FUNCTION sum( ftrapezium, float8 ) RETURNS ftrapezium 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'f_sum_r' LANGUAGE 'c' ;
CREATE OPERATOR + ( leftarg = ftrapezium, rightarg = float8, procedure = sum ) ;

CREATE OR REPLACE FUNCTION sum( float8, ftrapezium ) RETURNS ftrapezium 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'r_sum_f' LANGUAGE 'c' ;
CREATE OPERATOR + ( leftarg = float8, rightarg = ftrapezium, procedure = sum ) ;

--roznica

CREATE OR REPLACE FUNCTION sub( ftrapezium, ftrapezium ) RETURNS ftrapezium 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'f_sub_f' LANGUAGE 'c' ;
CREATE OPERATOR - ( leftarg = ftrapezium, rightarg = ftrapezium, procedure = sub ) ;

CREATE OR REPLACE FUNCTION sub( ftrapezium, float8 ) RETURNS ftrapezium 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'f_sub_r' LANGUAGE 'c' ;
CREATE OPERATOR - ( leftarg = ftrapezium, rightarg = float8, procedure = sub ) ;

CREATE OR REPLACE FUNCTION sub( float8, ftrapezium ) RETURNS ftrapezium 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'r_sub_f' LANGUAGE 'c' ;
CREATE OPERATOR - ( leftarg = float8, rightarg = ftrapezium, procedure = sub ) ;

-- minus sam
CREATE OR REPLACE FUNCTION minus( ftrapezium ) RETURNS ftrapezium 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'minus_f' LANGUAGE 'c' ;
CREATE OPERATOR - ( rightarg = ftrapezium, procedure = minus ) ;

-- f * f

CREATE OR REPLACE FUNCTION mul( ftrapezium, ftrapezium ) RETURNS ftrapezium 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'f_mul_f' LANGUAGE 'c' ;
CREATE OPERATOR * ( leftarg = ftrapezium, rightarg = ftrapezium, procedure = mul ) ;

CREATE OR REPLACE FUNCTION mul( ftrapezium, float8 ) RETURNS ftrapezium 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'f_mul_r' LANGUAGE 'c' ;
CREATE OPERATOR * ( leftarg = ftrapezium, rightarg = float8, procedure = mul ) ;

CREATE OR REPLACE FUNCTION mul( float8, ftrapezium ) RETURNS ftrapezium
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'r_mul_f' LANGUAGE 'c' ;
CREATE OPERATOR * ( leftarg = float8, rightarg = ftrapezium, procedure = mul ) ;

-- f / f

CREATE OR REPLACE FUNCTION div( ftrapezium, ftrapezium ) RETURNS ftrapezium 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'f_div_f' LANGUAGE 'c' ;
CREATE OPERATOR / ( leftarg = ftrapezium, rightarg = ftrapezium, procedure = div ) ;

CREATE OR REPLACE FUNCTION div( ftrapezium, float8 ) RETURNS ftrapezium 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'f_div_r' LANGUAGE 'c' ;
CREATE OPERATOR / ( leftarg = ftrapezium, rightarg = float8, procedure = div ) ;

CREATE OR REPLACE FUNCTION div( float8, ftrapezium ) RETURNS ftrapezium 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'r_div_f' LANGUAGE 'c' ;
CREATE OPERATOR / ( leftarg = float8, rightarg = ftrapezium, procedure = div ) ;

-- wyznaczanie wiekszej z dwoch wartosci ftrapezium

CREATE OR REPLACE FUNCTION max( ftrapezium, ftrapezium ) RETURNS ftrapezium 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'ftrapeziummax' LANGUAGE 'c' ;

-- wyznaczanie mniejszej z dwoch wartoci ftrapezium

CREATE OR REPLACE FUNCTION min( ftrapezium, ftrapezium ) RETURNS ftrapezium 
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'ftrapeziummin' LANGUAGE 'c' ;
 

-- **** funkcje i operator relacyjne *************

-- liczby rowne
CREATE OR REPLACE FUNCTION is_equal( ftrapezium, ftrapezium ) RETURNS bool
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'is_equal' LANGUAGE 'c' ;
CREATE OPERATOR = ( leftarg = ftrapezium, rightarg = ftrapezium, procedure = is_equal ) ;

-- pierwsza mniejsza
CREATE OR REPLACE FUNCTION is_lower( ftrapezium, ftrapezium ) RETURNS bool
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'is_lower' LANGUAGE 'c' ;
CREATE OPERATOR < ( leftarg = ftrapezium, rightarg = ftrapezium, procedure = is_lower ) ;

-- pierwsza mniejsza lub rowna
CREATE OR REPLACE FUNCTION is_lower_equal( ftrapezium, ftrapezium ) RETURNS bool
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'is_lower_equal' LANGUAGE 'c' ;
CREATE OPERATOR <= ( leftarg = ftrapezium, rightarg = ftrapezium, procedure = is_lower_equal ) ;

-- pierwsza wieksza
CREATE OR REPLACE FUNCTION is_greater( ftrapezium, ftrapezium ) RETURNS bool
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'is_greater' LANGUAGE 'c' ;
CREATE OPERATOR > ( leftarg = ftrapezium, rightarg = ftrapezium, procedure = is_greater ) ;

-- pierwsza wieksza lub rowna
CREATE OR REPLACE FUNCTION is_greater_equal( ftrapezium, ftrapezium ) RETURNS bool
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'is_greater_equal' LANGUAGE 'c' ;
CREATE OPERATOR >= ( leftarg = ftrapezium, rightarg = ftrapezium, procedure = is_greater_equal ) ;

-- liczby rozne
CREATE OR REPLACE FUNCTION not_equal( ftrapezium, ftrapezium ) RETURNS bool
  AS '/fuzzy/ftrapezium/ftrapezium.so', 'not_equal' LANGUAGE 'c' ;
CREATE OPERATOR <> ( leftarg = ftrapezium, rightarg = ftrapezium, procedure = not_equal ) ;
