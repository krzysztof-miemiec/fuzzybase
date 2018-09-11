-- Trapezoidal Function

CREATE OR REPLACE FUNCTION trapezoidal_function_in(opaque) RETURNS trapezoidal_function
  AS '../fuzzy.so' LANGUAGE 'C';

CREATE OR REPLACE FUNCTION trapezoidal_function_out(trapezoidal_function) RETURNS opaque
  AS '../fuzzy.so' LANGUAGE 'C';

CREATE TYPE trapezoidal_function(
  internallength=32,
  input=trapezoidal_function_in,
  output=trapezoidal_function_out
);

-- Trapezoidal Function Extended

CREATE OR REPLACE FUNCTION trapezoidal_function_ext_in(opaque) RETURNS trapezoidal_function_ext
  AS '../fuzzy.so' LANGUAGE 'C';

CREATE OR REPLACE FUNCTION trapezoidal_function_ext_out(trapezoidal_function_ext) RETURNS opaque
  AS '../fuzzy.so' LANGUAGE 'C';

CREATE TYPE trapezoidal_function_ext(
  internallength=44,
  input=trapezoidal_function_ext_in,
  output=trapezoidal_function_ext_out
);

-- Conversion of FEXT to TF
CREATE OR REPLACE FUNCTION to_trapezoidal_function(trapezoidal_function_ext) RETURNS trapezoidal_function
  AS '../fuzzy.so', 'trapezoidal_function_ext_to_trapezoidal_function' LANGUAGE 'c';

-- Creation of TF out of it's values
CREATE OR REPLACE FUNCTION about(float8, float8, float8, float8) RETURNS trapezoidal_function
  AS '../fuzzy.so', 'about' LANGUAGE 'c';

-- Adding threshold (extension) to TF
CREATE OR REPLACE FUNCTION to_fext_equal(trapezoidal_function, float8) RETURNS trapezoidal_function_ext
  AS '../fuzzy.so', 'to_fext_equal' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION to_fext_not_equal(trapezoidal_function, float8) RETURNS trapezoidal_function_ext
  AS '../fuzzy.so', 'to_fext_not_equal' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION to_fext_greater(trapezoidal_function, float8) RETURNS trapezoidal_function_ext
  AS '../fuzzy.so', 'to_fext_greater' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION to_fext_greater_equal(trapezoidal_function, float8) RETURNS trapezoidal_function_ext
  AS '../fuzzy.so', 'to_fext_greater_equal' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION to_fext_lower(trapezoidal_function, float8) RETURNS trapezoidal_function_ext
  AS '../fuzzy.so', 'to_fext_lower' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION to_fext_lower_equal(trapezoidal_function, float8) RETURNS trapezoidal_function_ext
  AS '../fuzzy.so', 'to_fext_lower_equal' LANGUAGE 'c';

CREATE OPERATOR *= (leftarg=trapezoidal_function, rightarg=float8, procedure=to_fext_equal);
CREATE OPERATOR *<> (leftarg=trapezoidal_function, rightarg=float8, procedure=to_fext_not_equal);
CREATE OPERATOR *> (leftarg=trapezoidal_function, rightarg=float8, procedure=to_fext_greater);
CREATE OPERATOR *>= (leftarg=trapezoidal_function, rightarg=float8, procedure=to_fext_greater_equal);
CREATE OPERATOR *< (leftarg=trapezoidal_function, rightarg=float8, procedure=to_fext_lower);
CREATE OPERATOR *<= (leftarg=trapezoidal_function, rightarg=float8, procedure=to_fext_lower_equal);
