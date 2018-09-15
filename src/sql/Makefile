EXTENSION = fuzzy
MODULES = fuzzy

DATA = fuzzy--0.0.1.sql
SQL_FILES = general/extension.sql general/general.sql trapezoidal/function.sql trapezoidal/operators.sql \
  trapezoidal/degree.sql trapezoidal/defuzzy.sql trapezoidal/aggregate.sql trapezoidal/linguistic_functions.sql \
  trapezoidal/index.sql

PG_CONFIG = pg_config
SHLIB_LINK = -L./general
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

fuzzy.sql:
	cat $(SQL_FILES) > fuzzy--0.0.1.sql

all: fuzzy.sql

everything: clean all install
	psql -d test -f test.sql

.PHONY: fuzzy.sql everything

