SELECT add_fuzzy_function('heart_rate', '0', 'none')
UNION SELECT add_fuzzy_function('heart_rate', '1~35\50', 'very low')
UNION SELECT add_fuzzy_function('heart_rate', '35/40~60\70', 'low')
UNION SELECT add_fuzzy_function('heart_rate', '50/60~100\130', 'normal')
UNION SELECT add_fuzzy_function('heart_rate', '120/130~160\190', 'high')
UNION SELECT add_fuzzy_function('heart_rate', '160/180~300', 'very high')
UNION SELECT add_fuzzy_function('heart_rate', '250/300~600\900', 'extremely high')
UNION SELECT add_fuzzy_function('heart_rate', '300/400~1200', 'impossible');

SELECT add_fuzzy_function('blood_pressure', '0~80\85', 'hypotension')
UNION SELECT add_fuzzy_function('blood_pressure', '75/80~120\130', 'normal')
UNION SELECT add_fuzzy_function('blood_pressure', '120/125~140\150', 'prehypertension')
UNION SELECT add_fuzzy_function('blood_pressure', '130/140~160\170', 'hypertension stage 1')
UNION SELECT add_fuzzy_function('blood_pressure', '150/160~180\200', 'hypertension stage 2')
UNION SELECT add_fuzzy_function('blood_pressure', '170/180~300', 'high crisis (emergency)');

SELECT add_fuzzy_function('total_cholesterol', '0~200\210', 'desirable')
UNION SELECT add_fuzzy_function('total_cholesterol', '190/200~240\250', 'borderline high')
UNION SELECT add_fuzzy_function('total_cholesterol', '230/240~1000', 'high');

SELECT add_fuzzy_function('age', '0~12\15', 'child')
UNION SELECT add_fuzzy_function('age', '10/12~16\19', 'young')
UNION SELECT add_fuzzy_function('age', '17/19~39\45', 'young adult')
UNION SELECT add_fuzzy_function('age', '35/40~60\65', 'adult')
UNION SELECT add_fuzzy_function('age', '60/65~200', 'old');

CREATE VIEW heart_disease_explained AS (
  SELECT
    age,
    CASE sex WHEN TRUE THEN 'M' ELSE 'F' END AS sex,
    CASE cp
      WHEN 1 THEN 'typical angina'
      WHEN 2 THEN 'atypical angina'
      WHEN 3 THEN 'non-anginal'
      WHEN 4 THEN 'asymptomatic'
      END AS chest_pain,
    trestbps~>'blood_pressure' AS rest_blood_pressure,
    chol~>'total_cholesterol' AS cholesterol,
    CASE fbs
      WHEN TRUE THEN 'above 120mg/dl'
      ELSE 'normal'
    END AS sugar_level,
    CASE restecg
      WHEN 0 THEN 'normal'
      WHEN 1 THEN 'ST-T wave abnormality'
      WHEN 2 THEN 'hypertrophy'
      END AS rest_ecg,
   thalach~>'heart_rate' AS excercise_heart_rate,
    oldpeak AS st_depression,
    slope AS st_slope,
    ca AS fluoroscopy_vessels,
    CASE thal
      WHEN 3 THEN 'normal'
      WHEN 6 THEN 'fixed defect'
      WHEN 7 THEN 'reversible'
      END AS thal,
    CASE num
    WHEN 0 THEN 'healthy'
    ELSE 'disease'
    END AS disease
  FROM heart_disease
);

CREATE VIEW heart_disease_grouped AS (
   SELECT
       age~>'age' AS age_group,
       CASE sex WHEN TRUE THEN 'M' ELSE 'F' END AS sex,
       CASE cp
         WHEN 4 THEN 'none'
         ELSE 'pain'
         END AS chest_pain,
       trestbps~=('blood_pressure'|>'normal')>0 AS pressure_normal,
       chol~=('total_cholesterol'|>'desirable')>0 AS cholesterol_desirable,
       CASE fbs
         WHEN TRUE THEN 'above 120mg/dl'
         ELSE 'normal'
         END AS sugar_level,
       CASE restecg
         WHEN 0 THEN 'normal'
         ELSE 'not normal'
         END AS rest_ecg,
       thalach~>'heart_rate' AS excercise_heart_rate,
       CASE thal
         WHEN 3 THEN 'normal'
         ELSE 'not normal'
         END AS thal,
       CASE num
         WHEN 0 THEN 'healthy'
         ELSE 'disease'
         END AS disease,
       COUNT(*)
  FROM heart_disease
  GROUP BY
           age_group,
           sex,
           pressure_normal,
           cholesterol_desirable,
           sugar_level,
           rest_ecg,
           chest_pain,
           thal,
           disease,
           excercise_heart_rate
);
