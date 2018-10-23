-- Percentage linguistic functions
CREATE OR REPLACE FUNCTION almost_none() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_almost_none' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION almost_all() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_almost_all' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_a_quarter() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_a_quarter' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_a_third() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_a_third' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_half() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_half' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_two_thirds() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_two_thirds' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_three_quarters() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_three_quarters' LANGUAGE 'c' IMMUTABLE STRICT;

-- Number linguistic functions
CREATE OR REPLACE FUNCTION about_one() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_one' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_some() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_some' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_a_dozen() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_a_dozen' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_a_few_dozen() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_a_few_dozen' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_a_few_hundred() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_a_few_hundred' LANGUAGE 'c' IMMUTABLE STRICT;

-- Time linguistic functions
CREATE OR REPLACE FUNCTION about_a_minute() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_a_minute' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_a_quarter_of_an_hour() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_a_quarter_of_an_hour' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_an_hour() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_an_hour' LANGUAGE 'c' IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION seconds_to_str(trapezoidal_function) RETURNS TEXT
  AS 'fuzzy', 'pg_seconds_to_str' LANGUAGE 'c' IMMUTABLE STRICT;

-- Date linguistic functions
CREATE OR REPLACE FUNCTION about_a_week() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_a_week' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_a_month() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_a_month' LANGUAGE 'c' IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION about_a_year() RETURNS trapezoidal_function
  AS 'fuzzy', 'pg_about_a_year' LANGUAGE 'c' IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION days_to_str(trapezoidal_function) RETURNS TEXT
  AS 'fuzzy', 'pg_days_to_str' LANGUAGE 'c' IMMUTABLE STRICT;
