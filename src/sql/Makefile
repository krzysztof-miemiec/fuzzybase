MODULES = general/general \
  general/utils \
  trapezoidal/function \
  trapezoidal/operators \
  trapezoidal/degree \
  trapezoidal/defuzzy \
  trapezoidal/aggregate \
  trapezoidal/linguistic_functions

DATA = general/general.sql \
  trapezoidal/function.sql \
  trapezoidal/operators.sql \
  trapezoidal/degree.sql \
  trapezoidal/defuzzy.sql \
  trapezoidal/aggregate.sql \
  trapezoidal/linguistic_functions.sql

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
