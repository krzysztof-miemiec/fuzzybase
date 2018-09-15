DROP TABLE IF EXISTS test_twoints, test_functions, test_functions_ext, test_zadeh;
DROP EXTENSION fuzzy CASCADE;
CREATE EXTENSION fuzzy;

CREATE TABLE test_twoints(a INT, b TWOINT);
INSERT INTO test_twoints VALUES (1, '1,20'), (1, '7,-3');

CREATE TABLE test_functions(a INT, b TRAPEZOIDAL_FUNCTION);
INSERT INTO test_functions VALUES
  (1, '0.2/0.4~0.6\0.8'),
  (2, '0.2/0.5\0.8'),
  (3, '0.2/0.4~0.8'),
  (4, '0.2/0.5'),
  (5, '0.2~0.8'),
  (6, '0.5'),
  (7, about(-10, 0, 3, 40)),
  (8, almost_none()),
  (9, almost_all()),
  (10, about_a_quarter()),
  (11, about_a_third()),
  (12, about_half()),
  (13, about_two_thirds()),
  (14, about_three_quarters()),
  (15, about_one()),
  (16, about_some()),
  (17, about_a_dozen()),
  (18, about_a_few_dozen()),
  (19, about_a_few_hundred()),
  (20, about_a_minute()),
  (21, about_a_quarter_of_an_hour()),
  (22, about_an_hour()),
  (23, about_a_week()),
  (24, about_a_month()),
  (25, about_a_year());

SELECT *, b+1 AS b_plus_one, 1+b AS one_plus_b, b-1 AS b_minus_one, 1-b AS one_minus_b FROM test_functions;
SELECT *, b*2 AS b_mul_two, 2*b AS two_mul_b, b/2 AS b_div_two, 2/b AS two_div_b FROM test_functions;

CREATE INDEX trapezoidal ON test_functions(b);

CREATE TABLE test_functions_ext(a INT, b TRAPEZOIDAL_FUNCTION_EXT);
INSERT INTO test_functions_ext VALUES
  (1, '0.2/0.4~0.6\0.8 *>= .3'),
  (2, to_fext_equal('1/2~3\4', .1)),
  (3, to_fext_not_equal('1/2~3\4', 0)),
  (4, to_fext_greater('1/2~3\4', .9)),
  (5, to_fext_greater_equal('1/2~3\4', .5)),
  (6, to_fext_lower('1/2~3\4', .3)),
  (7, to_fext_lower_equal('1/2~3\4', .6));

SELECT *, to_trapezoidal_function(b) as f FROM test_functions_ext;

CREATE TABLE test_zadeh(a FLOAT8, b FLOAT8);
INSERT INTO test_zadeh VALUES (0, .3), (.4, .9), (.6, .2), (1, 1), (NULL, 0.5), (0.5, NULL);
SELECT ~a AS neg_a FROM test_zadeh;
SELECT a|||b AS a_or_b FROM test_zadeh;
SELECT a&&&b AS a_and_b FROM test_zadeh;

SELECT state_percentage('1,2', false);
SELECT state_percentage('1,2', true);
SELECT final_percentage('11,20');
SELECT final_percentage('0,30');
SELECT final_percentage('15,15');
SELECT PERCENTAGE(a<.5) FROM test_zadeh;

SELECT degree(.3, '.2/1~2\2.2'), degree('.2/1~2\2.2', .9);
SELECT degreeff('1/2~3\4', '1/2~3\4'), degreeff('3/5~8\9', '1/2~3\4'), degreeff('1/2~3\4', '3/5~8\9');

SELECT defuzzy(b, 1.5), notdefuzzy(b, 1.5), defuzzy(1.5, b), notdefuzzy(1.5, b),
 degree(to_trapezoidal_function(b), 1.5) FROM test_functions_ext;