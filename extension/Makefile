EXTENSION = fuzzy
MODULES = fuzzy
REGRESS = logic_test functions_test helpers_test

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

add: clean all install

everything: add installcheck

.PHONY: fuzzy.sql everything add

