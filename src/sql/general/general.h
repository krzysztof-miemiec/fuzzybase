#ifndef GENERAL_H
#define GENERAL_H

#include <stdlib.h>
#include "postgres.h"

// Prototypes
typedef struct {
    int8 bool_count, count;
} twoint;
twoint *new_twoint(void);

// General functions, independent from fuzzy type

// Zadeh operators
/**
 * float8 min(float8 x, float8 y);
 */
PG_FUNCTION_INFO_V1(min);

Datum min(PG_FUNCTION_ARGS) {
    if (PG_ARGISNULL(0) || PG_ARGISNULL(1)) {
        PG_RETURN_NULL();
    }
    float8 x = PG_GETARG_FLOAT8(0);
    float8 y = PG_GETARG_FLOAT8(1);
    if (x < y) {
        PG_RETURN_FLOAT8(x);
    }
    PG_RETURN_FLOAT8(y);
}

/**
 * float8 max(float8 x, float8 y);
 */
PG_FUNCTION_INFO_V1(max);

Datum max(PG_FUNCTION_ARGS) {
    if (PG_ARGISNULL(0) || PG_ARGISNULL(1)) {
        PG_RETURN_NULL();
    }
    float8 x = PG_GETARG_FLOAT8(0);
    float8 y = PG_GETARG_FLOAT8(1);
    if (x > y) {
        PG_RETURN_FLOAT8(x);
    }
    PG_RETURN_FLOAT8(y);
}

/**
 * float8 neg_dm(float8 x);
 */
PG_FUNCTION_INFO_V1(neg_dm);

Datum neg_dm(PG_FUNCTION_ARGS) {
    if (PG_ARGISNULL(0)) {
        PG_RETURN_NULL();
    }
    float8 x = PG_GETARG_FLOAT8(0);
    float8 result = 1 - x;
    PG_RETURN_FLOAT8(result);
}

// Percentage Aggregate - Extended type that stores summed values

/**
 * Creates Two Int type
 * @return freshly-allocated Two Int
 */
twoint *new_twoint(void) {
    return (twoint *) palloc(sizeof(twoint));
}

/**
 * twoint *twoint_in(char* in);
 */
PG_FUNCTION_INFO_V1(twoint_in);

Datum twoint_in(PG_FUNCTION_ARGS) {
    char *str = PG_GETARG_CSTRING(0);
    twoint *result = new_twoint();
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
    sscanf(str, "%d,%d", &(result->bool_count), &(result->count));
#pragma GCC diagnostic pop
    PG_RETURN_POINTER(result);
}

/**
 * twoint *twoint_out(twoint* in);
 */
PG_FUNCTION_INFO_V1(twoint_out);

Datum twoint_out(PG_FUNCTION_ARGS) {
    twoint *t = (twoint *) PG_GETARG_POINTER(0);
    char *result = psprintf("%d,%d", t->bool_count, t->count);
    PG_RETURN_CSTRING(result);
}

/**
 * twoint *state_percentage(twoint *state, bool next);
 */
PG_FUNCTION_INFO_V1(state_percentage);

Datum state_percentage(PG_FUNCTION_ARGS) {
    twoint *result = new_twoint();
    twoint *state = (twoint *) PG_GETARG_POINTER(0);
    bool next = PG_GETARG_BOOL(1);

    result->bool_count = state->bool_count + (next ? 1 : 0);
    result->count = state->count + 1;

    PG_RETURN_POINTER(result);
}

/**
 * float8 *final_percentage(twoint *last_state);
 */
PG_FUNCTION_INFO_V1(final_percentage);

Datum final_percentage(PG_FUNCTION_ARGS) {
    if (PG_ARGISNULL(0)) {
        PG_RETURN_NULL();
    }

    twoint *state = (twoint *) PG_GETARG_POINTER(0);
    float8 result = state->bool_count / state->count;

    PG_RETURN_FLOAT8(result);
}

#endif
