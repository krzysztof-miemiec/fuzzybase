EXTENSION = fuzzy
MODULES = fuzzy

DATA = fuzzy--0.0.1.sql

PG_CONFIG = pg_config
SHLIB_LINK = -L./general
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

fuzzy-0.0.1.sql:
	cat \
	general/extension.sql \
	general/general.sql \
	trapezoidal/function.sql \
	trapezoidal/operators.sql \
	trapezoidal/degree.sql \
	trapezoidal/defuzzy.sql \
	trapezoidal/aggregate.sql \
	trapezoidal/linguistic_functions.sql > fuzzy--0.0.1.sql

all: fuzzy-0.0.1.sql
.PHONY: fuzzy-0.0.1.sql
