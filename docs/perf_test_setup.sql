drop database if exists perf_test;
drop user if exists perf_test;
create user perf_test with encrypted password 'perf_test' noinherit;
create database perf_test;
grant all on database perf_test to perf_test;
\c perf_test
CREATE EXTENSION fuzzy;
grant all on ALL TABLES IN SCHEMA public to perf_test;
grant all on ALL TABLES IN SCHEMA fuzzy to perf_test;

\i heart_disease.sql
\i heart_disease_functions.sql

GRANT ALL ON SCHEMA fuzzy TO perf_test;

INSERT INTO heart_disease SELECT * FROM heart_disease;
INSERT INTO heart_disease SELECT * FROM heart_disease;
INSERT INTO heart_disease SELECT * FROM heart_disease;
INSERT INTO heart_disease SELECT * FROM heart_disease;
INSERT INTO heart_disease SELECT * FROM heart_disease;
INSERT INTO heart_disease SELECT * FROM heart_disease;
INSERT INTO heart_disease SELECT * FROM heart_disease;
INSERT INTO heart_disease SELECT * FROM heart_disease;
INSERT INTO heart_disease SELECT * FROM heart_disease;
INSERT INTO heart_disease SELECT * FROM heart_disease;
