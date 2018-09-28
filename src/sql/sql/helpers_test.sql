CREATE EXTENSION fuzzy;

-- Fuzzy helpers
SELECT add_fuzzy_function('heart_rate', '0', 'none')
UNION SELECT add_fuzzy_function('heart_rate', '1~35\50', 'very low')
UNION SELECT add_fuzzy_function('heart_rate', '35/40~60\70', 'low')
UNION SELECT add_fuzzy_function('heart_rate', '50/60~100\130', 'normal')
UNION SELECT add_fuzzy_function('heart_rate', '120/130~160\190', 'high')
UNION SELECT add_fuzzy_function('heart_rate', '160/180~300', 'very high')
UNION SELECT add_fuzzy_function('heart_rate', '250/300~600\900', 'extremely high')
UNION SELECT add_fuzzy_function('heart_rate', '300/400~1200', 'impossible');

-- Creation and selection
SELECT x, get_fuzzy_name('heart_rate', x) FROM generate_series(10, 220, 50) AS x;

-- Deletion
SELECT delete_fuzzy_function('heart_rate', 'normal');
SELECT delete_fuzzy_function('heart_rate', trapezoidal_function '0');
SELECT * FROM get_fuzzy_type_functions('heart_rate');

-- Deletion of the whole type
SELECT delete_fuzzy_type('heart_rate');
SELECT * FROM get_fuzzy_type_functions('heart_rate');

-- Creation of a single type
SELECT add_fuzzy_type('cholesterol');
SELECT add_fuzzy_function('heart_rate', '35/40~60\70', 'low')
UNION SELECT add_fuzzy_function('heart_rate', '50/60~100\130', 'normal')
UNION SELECT add_fuzzy_function('heart_rate', '120/130~160\190', 'high');

-- Selection of all types
SELECT * FROM get_fuzzy_types();

-- Getter for a specific function
SELECT * FROM get_fuzzy_function('heart_rate', 'high');
SELECT 'heart_rate'|>'high';
SELECT  130~>'heart_rate';

DROP EXTENSION fuzzy CASCADE;
