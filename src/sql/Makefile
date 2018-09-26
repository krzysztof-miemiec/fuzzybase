EXTENSION = fuzzy
MODULES = fuzzy
REGRESS = fuzzy_test

DATA = fuzzy--0.0.2.sql
SQL_FILES = general/extension.sql general/general.sql trapezoidal/function.sql trapezoidal/operators.sql \
  trapezoidal/degree.sql trapezoidal/defuzzy.sql trapezoidal/aggregate.sql trapezoidal/linguistic_functions.sql \
  trapezoidal/index.sql general/helpers.sql

PG_CONFIG = pg_config
SHLIB_LINK = -L./general
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

fuzzy.sql:
	cat $(SQL_FILES) > fuzzy--0.0.2.sql

all: fuzzy.sql

everything: clean all install installcheck

.PHONY: fuzzy.sql everything

