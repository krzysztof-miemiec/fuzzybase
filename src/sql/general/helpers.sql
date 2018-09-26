CREATE SCHEMA IF NOT EXISTS fuzzy;

CREATE TABLE IF NOT EXISTS fuzzy.types (
  id   SERIAL PRIMARY KEY,
  name VARCHAR(64)
);

CREATE TABLE IF NOT EXISTS fuzzy.functions (
  type INT                  NOT NULL,
  fun  TRAPEZOIDAL_FUNCTION NOT NULL,
  name VARCHAR(64),
  FOREIGN KEY (type) REFERENCES fuzzy.types (id)
);

CREATE OR REPLACE FUNCTION add_fuzzy_type(
  name VARCHAR(64)
) RETURNS fuzzy.types.id%TYPE AS $$
  INSERT INTO fuzzy.types (name) VALUES (name) RETURNING id AS id;
$$ LANGUAGE SQL VOLATILE;

CREATE OR REPLACE FUNCTION add_fuzzy_function(
  type_name VARCHAR(64),
  fuzzy_function TRAPEZOIDAL_FUNCTION,
  range_name VARCHAR(64) DEFAULT NULL
) RETURNS RECORD AS $$
DECLARE
  type_id fuzzy.types.id%TYPE;
BEGIN
  type_id := (SELECT add_fuzzy_type(type_name));
  INSERT INTO fuzzy.functions VALUES (
    type_id,
    fuzzy_function,
    range_name
  );
  RETURN (type_id, fuzzy_function, range_name);
END;
$$ LANGUAGE plpgsql VOLATILE;

CREATE OR REPLACE FUNCTION get_fuzzy_type_functions(
  type_name VARCHAR(64)
) RETURNS fuzzy.functions AS $$
  SELECT * FROM fuzzy.functions WHERE type=(SELECT id FROM fuzzy.types WHERE name=type_name);
$$ LANGUAGE SQL IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION delete_fuzzy_type_functions(
  type_name VARCHAR(64)
) RETURNS fuzzy.functions AS $$
DELETE FROM fuzzy.functions WHERE type=(SELECT id FROM fuzzy.types WHERE name=type_name);
$$ LANGUAGE SQL IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION get_fuzzy_name(
  type_name VARCHAR(64),
  input FLOAT8
) RETURNS VARCHAR(64) AS $$
DECLARE
  result_name VARCHAR(64);
BEGIN
  SELECT name INTO result_name FROM fuzzy.functions
    WHERE type=(SELECT id FROM fuzzy.types WHERE name=type_name)
    ORDER BY degree(input, fun) DESC
    LIMIT 1;
  RETURN result_name;
END;
$$ LANGUAGE plpgsql IMMUTABLE STRICT;


SELECT add_fuzzy_type('heart_rate');
SELECT add_fuzzy_function('a', '3.3/4~5\5.3');
INSERT INTO fuzzy.functions VALUES (
(SELECT t.id AS id FROM fuzzy.types t WHERE t.name = 'heart_rate'),
'3.3/4~5\5.3',
'small'
) RETURNING '3.3/4~5\5.3';
