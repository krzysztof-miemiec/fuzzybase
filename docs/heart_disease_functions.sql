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

SELECT
       age,
       CASE sex WHEN TRUE THEN 'M' ELSE 'F' END AS sex,
       CASE cp
         WHEN 1 THEN 'typical angina'
         WHEN 2 THEN 'atypical angina'
         WHEN 3 THEN 'non-anginal'
         WHEN 4 THEN 'asymptomatic'
         END AS chest_pain,
       get_fuzzy_name('blood_pressure', trestbps) AS rest_blood_pressure,
       get_fuzzy_name('total_cholesterol', chol) AS cholesterol,
       CASE fbs
         WHEN TRUE THEN 'above 120mg/dl'
         ELSE 'normal'
       END AS sugar_level,
       CASE restecg
         WHEN 0 THEN 'normal'
         WHEN 1 THEN 'ST-T wave abnormality'
         WHEN 2 THEN 'hypertrophy'
         END AS rest_ecg,
       get_fuzzy_name('heart_rate', thalach) AS excercise_heart_rate,
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
WHERE trestbps~=get_fuzzy_function('blood_pressure', 'normal');
