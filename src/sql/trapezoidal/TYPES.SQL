--***************** tworzenie typu trapezoidal_function ****************

CREATE OR REPLACE FUNCTION trapezoidal_function_in( opaque ) RETURNS trapezoidal_function
  AS '/fuzzy/trapezoidal_function/trapezoidal_function.so' LANGUAGE 'C';

CREATE OR REPLACE FUNCTION trapezoidal_function_out( trapezoidal_function ) RETURNS opaque
  AS '/fuzzy/trapezoidal_function/trapezoidal_function.so' LANGUAGE 'C';

CREATE TYPE trapezoidal_function( internallength = 32, input = trapezoidal_function_in, output = trapezoidal_function_out ) ;

-- **************************TYP trapezoidal_function_ext*****************************************************

-- tworzenie typu trapezoidal_function_ext

CREATE OR REPLACE FUNCTION trapezoidal_function_ext_in( opaque ) RETURNS trapezoidal_function_ext
  AS '/fuzzy/trapezoidal_function/trapezoidal_function.so' LANGUAGE 'C';

CREATE OR REPLACE FUNCTION trapezoidal_function_ext_out( trapezoidal_function_ext ) RETURNS opaque
  AS '/fuzzy/trapezoidal_function/trapezoidal_function.so' LANGUAGE 'C';

CREATE TYPE trapezoidal_function_ext( internallength = 44, input = trapezoidal_function_ext_in, output = trapezoidal_function_ext_out ) ;