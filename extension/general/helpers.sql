CREATE SCHEMA IF NOT EXISTS fuzzy;

CREATE TABLE IF NOT EXISTS fuzzy.types (
  id   SERIAL PRIMARY KEY,
  name VARCHAR(64) UNIQUE
);

CREATE TABLE IF NOT EXISTS fuzzy.functions (
  type INT                  NOT NULL,
  fun  TRAPEZOIDAL_FUNCTION NOT NULL,
  name VARCHAR(64),
  FOREIGN KEY (type) REFERENCES fuzzy.types (id) ON DELETE CASCADE,
  UNIQUE (type, name)
);

-- Add Fuzzy type
DROP FUNCTION IF EXISTS add_fuzzy_type(
  type_name VARCHAR(64)
);
CREATE OR REPLACE FUNCTION add_fuzzy_type(
  type_name VARCHAR(64)
) RETURNS fuzzy.types.id%TYPE AS $$
  INSERT INTO fuzzy.types (name) VALUES (type_name) ON CONFLICT DO NOTHING;
  SELECT id FROM fuzzy.types WHERE name=type_name;
$$ LANGUAGE sql VOLATILE;

-- Get fuzzy type by name
DROP FUNCTION IF EXISTS get_fuzzy_type(
  type_name VARCHAR(64)
);
CREATE OR REPLACE FUNCTION get_fuzzy_type(
  type_name VARCHAR(64)
) RETURNS fuzzy.types.id%TYPE AS $$
DECLARE
  type_id fuzzy.types.id%TYPE;
BEGIN
  type_id := (SELECT id FROM fuzzy.types WHERE name=type_name);
  IF type_id IS NULL THEN
    RAISE EXCEPTION 'Can''t find specified fuzzy type. The type "%" does not exist.', type_name
      USING HINT = 'Check if you specified the correct fuzzy type name. See available types by SELECT * FROM get_fuzzy_types();';
  END IF;
  RETURN type_id;
END;
$$ LANGUAGE plpgsql IMMUTABLE STRICT;

-- Add fuzzy function
DROP FUNCTION IF EXISTS add_fuzzy_function(
  type_name VARCHAR(64),
  fuzzy_function TRAPEZOIDAL_FUNCTION,
  range_name VARCHAR(64)
);
CREATE FUNCTION add_fuzzy_function(
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

-- Delete fuzzy function by range name
DROP FUNCTION IF EXISTS delete_fuzzy_function(
  type_name VARCHAR(64),
  range_name VARCHAR(64)
);
CREATE FUNCTION delete_fuzzy_function(
  type_name VARCHAR(64),
  range_name VARCHAR(64)
) RETURNS RECORD AS $$
DECLARE
  type_id fuzzy.types.id%TYPE;
BEGIN
  type_id := get_fuzzy_type(type_name);
  DELETE FROM fuzzy.functions WHERE type=type_id AND name=range_name;
  RETURN (type_id, range_name);
END;
$$ LANGUAGE plpgsql VOLATILE;

-- Delete fuzzy function by function value
DROP FUNCTION IF EXISTS delete_fuzzy_function(
  type_name VARCHAR(64),
  func TRAPEZOIDAL_FUNCTION
);
CREATE FUNCTION delete_fuzzy_function(
  type_name VARCHAR(64),
  func TRAPEZOIDAL_FUNCTION
) RETURNS RECORD AS $$
DECLARE
  type_id fuzzy.types.id%TYPE;
BEGIN
  type_id := get_fuzzy_type(type_name);
  DELETE FROM fuzzy.functions WHERE type=type_id AND fun=func;
  RETURN (type_id, func);
END;
$$ LANGUAGE plpgsql VOLATILE;

-- Delete fuzzy function by function value
DROP FUNCTION IF EXISTS delete_fuzzy_type(
  type_name VARCHAR(64)
);
CREATE FUNCTION delete_fuzzy_type(
  type_name VARCHAR(64)
) RETURNS VARCHAR(64) AS $$
DECLARE
  type_id fuzzy.types.id%TYPE;
BEGIN
  type_id := get_fuzzy_type(type_name);
  DELETE FROM fuzzy.types CASCADE WHERE id=type_id;
  RETURN type_name;
END;
$$ LANGUAGE plpgsql VOLATILE;

-- Get all functions for specified fuzzy type
DROP FUNCTION IF EXISTS get_fuzzy_type_functions(
  type_name VARCHAR(64)
);
CREATE FUNCTION get_fuzzy_type_functions(
  type_name VARCHAR(64)
) RETURNS TABLE (
  func  TRAPEZOIDAL_FUNCTION,
  range_name VARCHAR(64)
) AS $$
DECLARE
  type_id fuzzy.types.id%TYPE;
BEGIN
  type_id := get_fuzzy_type(type_name);
  RETURN QUERY SELECT fun, name FROM fuzzy.functions WHERE fuzzy.functions.type=type_id;
END;
$$ LANGUAGE plpgsql IMMUTABLE STRICT;

-- Get the name of the best fitting fuzzy function for specified type and value (the "range name")
DROP FUNCTION IF EXISTS get_fuzzy_name(
  type_name VARCHAR(64),
  input FLOAT8
);
CREATE FUNCTION get_fuzzy_name(
  input FLOAT8,
  type_name VARCHAR(64)
) RETURNS VARCHAR(64) AS $$
  SELECT f.name FROM fuzzy.functions f, fuzzy.types t
  WHERE t.name=type_name AND t.id=f.type AND degree(input, f.fun)>0
  ORDER BY degree(input, f.fun) DESC LIMIT 1;
$$ LANGUAGE sql STABLE;

CREATE OPERATOR ~> (
  PROCEDURE = get_fuzzy_name,
  LEFTARG = FLOAT8,
  RIGHTARG = VARCHAR(64)
);

-- Get fuzzy function
DROP FUNCTION IF EXISTS get_fuzzy_function(
  type_name VARCHAR(64),
  function_name VARCHAR(64)
);
CREATE FUNCTION get_fuzzy_function(
  type_name VARCHAR(64),
  function_name VARCHAR(64)
) RETURNS TRAPEZOIDAL_FUNCTION AS $$
DECLARE
  type_id fuzzy.types.id%TYPE;
BEGIN
  type_id := get_fuzzy_type(type_name);
  RETURN (SELECT fun
          FROM fuzzy.functions
          WHERE type = type_id AND function_name = name);
END;
$$ LANGUAGE plpgsql IMMUTABLE STRICT;

CREATE OPERATOR |> (
  PROCEDURE = get_fuzzy_function,
  LEFTARG = VARCHAR(64),
  RIGHTARG = VARCHAR(64)
);

-- Get all fuzzy types
DROP FUNCTION IF EXISTS get_fuzzy_types();
CREATE FUNCTION get_fuzzy_types() RETURNS TABLE (
  type_name VARCHAR(64),
  range_names VARCHAR[]
) AS $$
  SELECT
        fts.name AS type_name,
        array_agg(ffs.name) AS range_names
  FROM
       fuzzy.types fts
  LEFT JOIN
      fuzzy.functions ffs ON ffs.type=fts.id
  GROUP BY fts.name;
$$ LANGUAGE sql IMMUTABLE STRICT;

DROP FUNCTION IF EXISTS get_fuzzy_functions();
CREATE FUNCTION get_fuzzy_functions() RETURNS TABLE (
  type_id INT,
  type_name VARCHAR(64),
  name VARCHAR(64),
  fun TRAPEZOIDAL_FUNCTION
) AS $$
  SELECT
    fts.id as type_id,
    fts.name as type_name,
    ffs.name as name,
    ffs.fun as fun
  FROM
    fuzzy.types fts, fuzzy.functions ffs
  WHERE ffs.type=fts.id;
$$ LANGUAGE sql IMMUTABLE STRICT;
