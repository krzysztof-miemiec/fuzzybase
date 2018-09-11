MODULES = fuzzy

DATA = general/general.sql \
  trapezoidal/function.sql \
  trapezoidal/operators.sql \
  trapezoidal/degree.sql \
  trapezoidal/defuzzy.sql \
  trapezoidal/aggregate.sql \
  trapezoidal/linguistic_functions.sql

PG_CONFIG = pg_config
SHLIB_LINK = -L./general
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
