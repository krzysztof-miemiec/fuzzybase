#include "postgres.h"
#include <stdlib.h>

#include "./general.h"

// General functions, independent from fuzzy type

// Zadeh operators

float8 *min(float8 *x, float8 *y) {
    if ((x == NULL) || (y == NULL)) {
        return NULL;
    }
    if (*x < *y) {
        return x;
    }
    return y;
}

float8 *max(float8 *x, float8 *y) {
    if ((x == NULL) || (y == NULL)) {
        return NULL;
    }
    if (*x < *y)
        return y;
    else
        return x;
}

float8 *neg_dm(float8 *x) {
    if (x == NULL) {
        return NULL;
    } else {
        *x = 1 - *x;
        return (x);
    };
}

// Percentage Aggregate - Extended type that stores summed values

twoint *twoint_from_string(char *str) {
    twoint *result = (twoint *) palloc(sizeof(twoint));

    sscanf(str, "%d,%d", &(result->bool_count), &(result->count));

    return result;
}

char *twoint_to_string(twoint *t) {
    char *result = (char *) palloc(sizeof(char));
    strcpy(result, "");

    sprintf(result, "%d,%d", t->bool_count, t->count);
    return result;
}

twoint *percentage_sfunc(twoint *state, bool next_data) {
    twoint *result = (twoint *) palloc(sizeof(twoint));

    result->bool_count = state->bool_count;
    result->count = state->count;

    result->count++;
    if (next_data) {
        result->bool_count++;
    }

    return result;
}

float8 *percentage_final_func(twoint *last_state) {
    float8 *result = NULL;

    if (last_state == NULL) {
        return NULL;
    }

    result = (float8 *) palloc(8);
    *result = (float8)(last_state->bool_count / last_state->count);

    return result;
}
