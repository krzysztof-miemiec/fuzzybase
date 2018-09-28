CREATE EXTENSION fuzzy;

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
  (25, about_a_year()),
  (26, NULL);

CREATE INDEX trapezoidal ON test_functions(b);

SELECT *, seconds_to_str(b), days_to_str(b) FROM test_functions;

-- SUM
SELECT b+1 AS b_plus_one, 1+b AS one_plus_b FROM test_functions;
-- SUB
SELECT b-1 AS b_minus_one, 1-b AS one_minus_b FROM test_functions;
-- MUL
SELECT b*2 AS b_mul_two, 2*b AS two_mul_b FROM test_functions;
-- DIV
SELECT b/2 AS b_div_two, 2/b AS two_div_b FROM test_functions;
-- NEG
SELECT -b AS neg_b FROM test_functions;
-- Division by zero (should return null)
SELECT 0/b AS zero_div_b, b/0 AS b_div_zero FROM test_functions;
-- Complex expression that should be evaluated to b
SELECT b, ((1-(-b)-1)*b)/b AS should_be_b FROM test_functions;

-- Function operators
SELECT (trapezoidal_function '1/2~3\4')+(trapezoidal_function '3/4~5\6') AS f_plus_f;
SELECT (trapezoidal_function '1/2~3\4')-(trapezoidal_function '3/4~5\6') AS f_minus_f;
SELECT (trapezoidal_function '1/2~3\4')*(trapezoidal_function '3/4~5\6') AS f_mul_f;
SELECT (trapezoidal_function '1/2~3\4')/(trapezoidal_function '3/4~5\6') AS f_div_f;
SELECT max(trapezoidal_function '1/2~3\4', trapezoidal_function '3/4~5\6') AS max_f;
SELECT min(trapezoidal_function '1/2~3\4', trapezoidal_function '3/4~5\6') AS min_f;

CREATE TABLE test_functions_ext(a INT, b TRAPEZOIDAL_FUNCTION_EXT);
INSERT INTO test_functions_ext VALUES
  (1, '0.2/0.4~0.6\0.8 *>= .3'),
  (2, trapezoidal_function('1/2~3\4') *= .1),
  (3, trapezoidal_function('1/2~3\4') *<> 0),
  (4, trapezoidal_function('1/2~3\4') *> .9),
  (5, trapezoidal_function('1/2~3\4') *>= .5),
  (6, trapezoidal_function('1/2~3\4') *< .3),
  (7, trapezoidal_function('1/2~3\4') *<= .6);

-- Conversion
SELECT *, to_trapezoidal_function(b) as f FROM test_functions_ext;

SELECT state_percentage('1,2', false);
SELECT state_percentage('1,2', true);
SELECT final_percentage('11,20');
SELECT final_percentage('0,30');
SELECT final_percentage('15,15');
SELECT PERCENTAGE(a<.5) FROM test_zadeh;

SELECT degree(.3, '.2/1~2\2.2'), degree('.2/1~2\2.2', .9);
SELECT degreeff('1/2~3\4', '1/2~3\4'), degreeff('3/5~8\9', '1/2~3\4'), degreeff('1/2~3\4', '3/5~8\9');

-- Defuzzy
SELECT
    degree(to_trapezoidal_function(b), 1.5) AS degree,
    defuzzy(b, 1.5),
    defuzzy(1.5, b)
  FROM test_functions_ext;
-- Not defuzzy
SELECT
    degree(to_trapezoidal_function(b), 1.5) AS degree,
    notdefuzzy(b, 1.5),
    notdefuzzy(1.5, b)
  FROM test_functions_ext;

SELECT about_one();

DROP EXTENSION fuzzy CASCADE;
