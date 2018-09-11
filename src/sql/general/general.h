#ifndef GENERAL_H
#define GENERAL_H

#include <stdlib.h>
#include "postgres.h"

// Prototypes
typedef struct {
    int8 bool_count, count;
} twoint;

twoint *new_twoint(void);

float8 *min(float8 *x, float8 *y);

float8 *max(float8 *x, float8 *y);

float8 *neg_dm(float8 *x);

twoint *twoint_from_string(char *str);

char *twoint_to_string(twoint *t);

twoint *state_percentage(twoint *state, bool next);

float8 *final_percentage(twoint *last_state);


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

twoint *new_twoint(void) {
    return (twoint *) palloc(sizeof(twoint));
}

twoint *twoint_from_string(char *str) {
    twoint *result = new_twoint();

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
    sscanf(str, "%d,%d", &(result->bool_count), &(result->count));
#pragma GCC diagnostic pop

    return result;
}

char *twoint_to_string(twoint *t) {
    char *result = (char *) palloc(sizeof(char));
    strcpy(result, "");

    sprintf(result, "%d,%d", t->bool_count, t->count);
    return result;
}

twoint *state_percentage(twoint *state, bool next) {
    twoint *result = new_twoint();

    result->bool_count = state->bool_count;
    result->count = state->count;

    result->count++;
    if (next) {
        result->bool_count++;
    }

    return result;
}

float8 *final_percentage(twoint *last_state) {
    float8 *result = NULL;

    if (last_state == NULL) {
        return NULL;
    }

    result = (float8 *) palloc(8);
    *result = (float8)(last_state->bool_count / last_state->count);

    return result;
}

#endif
