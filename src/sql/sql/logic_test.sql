CREATE EXTENSION fuzzy;

CREATE TABLE test_twoints(a INT, b TWOINT);
INSERT INTO test_twoints VALUES (1, '1,20'), (1, '7,-3');

CREATE TABLE test_zadeh(a FLOAT8, b FLOAT8);
INSERT INTO test_zadeh VALUES (0, .3), (.4, .9), (.6, .2), (1, 1), (NULL, 0.5), (0.5, NULL);
SELECT ~a AS neg_a FROM test_zadeh;
SELECT a|||b AS a_or_b FROM test_zadeh;
SELECT a&&&b AS a_and_b FROM test_zadeh;

DROP EXTENSION fuzzy CASCADE;
