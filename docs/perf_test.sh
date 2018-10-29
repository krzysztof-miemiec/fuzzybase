#!/usr/bin/env bash
set -e

# In order to create the user and database, run the following PSQL script as Postgres admin
# psql -d existing_database -f perf_test_setup.sql
#

PGDATABASE=perf_test
PGPASSWORD=perf_test

sql="psql -d ${PGDATABASE}"

ROW_COUNT=$($sql -c 'SELECT COUNT(*) FROM heart_disease;' | grep -e '^ [0-9]' | sed 's: ::g')
echo "There are ${ROW_COUNT} rows in the table."

function time_fn() {
  echo "${1}"
  x=1
  while [ $x -le 20 ]; do
    $sql -c '\timing' -c "${1}" | grep -e '^Time: [0-9]' | sed 's/Time: //'
    x=$(( $x + 1 ))
  done
}

echo Fuzzy age precise query
time_fn "SELECT age~=('age'|>'old') AS r FROM heart_disease;"

echo Fuzzy age precist query using with
time_fn "SELECT age~=('60/70~100\120') AS r FROM heart_disease;"

echo Standard age precise query
time_fn "SELECT CASE
        WHEN (age IS NULL) THEN NULL
        WHEN (age<60) THEN 0.0
        WHEN (age<70) THEN (age-60.0)/10.0
        WHEN (age<100) THEN 1.0
        WHEN (age<120) THEN (age-120.0)/-20.0
        ELSE 0.0 END AS r FROM heart_disease;"

echo Fuzzy age query
time_fn "SELECT COUNT("'*'") FROM heart_disease WHERE age~=('age'|>'old')>0;"
echo Standard age query
time_fn "SELECT COUNT("'*'") FROM heart_disease WHERE age>60 AND age<120;"

echo Fuzzy group by pressure query
time_fn "SELECT
    thalach~>'blood_pressure' AS pressure,
    COUNT("'*'") AS count
    FROM heart_disease
    GROUP BY pressure;"
echo Standard group by pressure query
time_fn "SELECT
    CASE
      WHEN thalach<80 THEN 'hypotension'
       WHEN thalach<120 THEN 'normal'
       WHEN thalach<140 THEN 'prehypertension'
       WHEN thalach<170 THEN 'hypertension stage 1'
       WHEN thalach<180 THEN 'hypertension stage 2'
       ELSE 'high crisis (emergency)'
    END
        AS pressure,
        COUNT("'*'") AS COUNT
    FROM heart_disease
    GROUP BY pressure;"


echo Fuzzy group by normal pressure query
time_fn "SELECT
    thalach~=('blood_pressure'|>'normal') AS pressure,
    COUNT("'*'") AS COUNT
    FROM heart_disease
    GROUP BY pressure;"
echo Standard group by normal pressure query
time_fn "SELECT
    CASE
        WHEN (thalach IS NULL) THEN NULL
        WHEN (thalach<75) THEN 0.0
        WHEN (thalach<80) THEN (thalach-75.0)/5.0
        WHEN (thalach<120) THEN 1.0
        WHEN (thalach<130) THEN (thalach-130.0)/-10.0
        ELSE 0.0
    END
     AS pressure,
     COUNT(*) AS count
    FROM heart_disease
    GROUP BY pressure;"
