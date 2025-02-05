#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"

PG_MODULE_MAGIC;

#include "./general/utils.h"
#include "./general/general.h"

#include "./trapezoidal/aggregate.h"
#include "./trapezoidal/defuzzy.h"
#include "./trapezoidal/degree.h"
#include "./trapezoidal/function.h"
#include "./trapezoidal/linguistic_functions.h"
#include "./trapezoidal/operators.h"
