--**************funkcje ogolne wykorzystywane przez zapytania zagniezdzone***********
--rozszerzanie typu trapezoidal_function o stopien defuzyfikacji



--*****************************zapytania z operatoarami ALL, ANY, IN typu (fext, real)********************
-- A
CREATE OR REPLACE FUNCTION defuzzy( trapezoidal_function_ext, float8 ) RETURNS bool
  AS '../fuzzy.so', 'defuzzy_fext_r' LANGUAGE 'c' ;
CREATE OPERATOR = ( leftarg = trapezoidal_function_ext, rightarg = float8, procedure = defuzzy ) ;

CREATE OR REPLACE FUNCTION notdefuzzy( trapezoidal_function_ext, float8 ) RETURNS bool
  AS '../fuzzy.so', 'not_defuzzy_fext_r' LANGUAGE 'c' ;
CREATE OPERATOR <> ( leftarg = trapezoidal_function_ext, rightarg = float8, procedure = notdefuzzy ) ;


--*****************************zapytania z operatoarami ALL, ANY, IN typu (real, fext)********************
-- B
CREATE OR REPLACE FUNCTION defuzzy( float8, trapezoidal_function_ext ) RETURNS bool
  AS '../fuzzy.so', 'defuzzy_r_fext' LANGUAGE 'c' ;
CREATE OPERATOR = ( leftarg = float8 , rightarg = trapezoidal_function_ext, procedure = defuzzy ) ;

CREATE OR REPLACE FUNCTION notdefuzzy( float8, trapezoidal_function_ext ) RETURNS bool
  AS '../fuzzy.so', 'not_defuzzy_r_fext' LANGUAGE 'c' ;
CREATE OPERATOR <> ( leftarg = float8, rightarg = trapezoidal_function_ext, procedure = notdefuzzy ) ;


--*****************************zapytania z operatoarami ALL, ANY, IN typu (fext, ft)********************
-- C
CREATE OR REPLACE FUNCTION defuzzy( trapezoidal_function_ext, trapezoidal_function ) RETURNS bool
  AS '../fuzzy.so', 'defuzzy_fext_ft' LANGUAGE 'c' ;
CREATE OPERATOR = ( leftarg = trapezoidal_function_ext, rightarg = trapezoidal_function, procedure = defuzzy ) ;

CREATE OR REPLACE FUNCTION notdefuzzy( trapezoidal_function_ext, trapezoidal_function ) RETURNS bool
  AS '../fuzzy.so', 'not_defuzzy_fext_ft' LANGUAGE 'c' ;
CREATE OPERATOR <> ( leftarg = trapezoidal_function_ext, rightarg = trapezoidal_function, procedure = notdefuzzy ) ;


--*****************************zapytania z operatoarami ALL, ANY, IN typu (ft, fext)********************
-- D
CREATE OR REPLACE FUNCTION defuzzy( trapezoidal_function, trapezoidal_function_ext ) RETURNS bool
  AS '../fuzzy.so', 'defuzzy_ft_fext' LANGUAGE 'c' ;
CREATE OPERATOR = ( leftarg = trapezoidal_function, rightarg = trapezoidal_function_ext, procedure = defuzzy ) ;

CREATE OR REPLACE FUNCTION notdefuzzy( trapezoidal_function, trapezoidal_function_ext ) RETURNS bool
  AS '../fuzzy.so', 'not_defuzzy_ft_fext' LANGUAGE 'c' ;
CREATE OPERATOR <> ( leftarg = trapezoidal_function, rightarg = trapezoidal_function_ext, procedure = notdefuzzy ) ;


