-- Percentage linguistic functions
CREATE OR REPLACE FUNCTION almost_none() RETURNS trapezoidal_function
  AS 'fuzzy', 'almost_none' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION almost_all() RETURNS trapezoidal_function
  AS 'fuzzy', 'almost_all' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION about_a_quarter() RETURNS trapezoidal_function
  AS 'fuzzy', 'about_a_quarter' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION about_a_third() RETURNS trapezoidal_function
  AS 'fuzzy', 'about_a_third' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION about_half() RETURNS trapezoidal_function
  AS 'fuzzy', 'about_half' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION about_two_thirds() RETURNS trapezoidal_function
  AS 'fuzzy', 'about_two_thirds' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION about_three_quarters() RETURNS trapezoidal_function
  AS 'fuzzy', 'about_three_quarters' LANGUAGE 'c';

-- Number linguistic functions
CREATE OR REPLACE FUNCTION about_one() RETURNS trapezoidal_function
  AS 'fuzzy', 'about_one' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION about_some() RETURNS trapezoidal_function
  AS 'fuzzy', 'about_some' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION about_a_dozen() RETURNS trapezoidal_function
  AS 'fuzzy', 'about_a_dozen' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION about_a_few_dozen() RETURNS trapezoidal_function
  AS 'fuzzy', 'about_a_few_dozen' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION about_a_few_hundred() RETURNS trapezoidal_function
  AS 'fuzzy', 'about_a_few_hundred' LANGUAGE 'c';

-- Time linguistic functions
CREATE OR REPLACE FUNCTION about_a_minute() RETURNS trapezoidal_function
  AS 'fuzzy', 'about_a_minute' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION about_a_quarter_of_an_hour() RETURNS trapezoidal_function
  AS 'fuzzy', 'about_a_quarter_of_an_hour' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION about_an_hour() RETURNS trapezoidal_function
  AS 'fuzzy', 'about_an_hour' LANGUAGE 'c';

CREATE OR REPLACE FUNCTION seconds_to_str(trapezoidal_function) RETURNS TEXT
  AS 'fuzzy', 'seconds_to_str' LANGUAGE 'c';

-- Date linguistic functions
CREATE OR REPLACE FUNCTION about_a_week() RETURNS trapezoidal_function
  AS 'fuzzy', 'about_a_week' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION about_a_month() RETURNS trapezoidal_function
  AS 'fuzzy', 'about_a_month' LANGUAGE 'c';
CREATE OR REPLACE FUNCTION about_a_year() RETURNS trapezoidal_function
  AS 'fuzzy', 'about_a_year' LANGUAGE 'c';

CREATE OR REPLACE FUNCTION days_to_str(trapezoidal_function) RETURNS TEXT
  AS 'fuzzy', 'days_to_str' LANGUAGE 'c';
