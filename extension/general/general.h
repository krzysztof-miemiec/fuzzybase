#ifndef GENERAL_H
#define GENERAL_H

#include <stdlib.h>
#include "postgres.h"
#include "./extension.h"

// Prototypes
typedef struct {
    int8 bool_count, count;
} twoint;

twoint *new_twoint(void);

float8 minimum(float8 x, float8 y);

float8 maximum(float8 x, float8 y);

float8 neg_dm(float8 x);

twoint *twoint_in(char *str);

char *twoint_out(twoint *t);

twoint *state_percentage(twoint *state, bool next);

float8 final_percentage(twoint *last_state);

// Zadeh operators

float8 minimum(float8 x, float8 y) {
    return x<y ? x : y;
}

PG_FUNC_2(minimum, float8, FLOAT8, float8, FLOAT8, float8, FLOAT8);

float8 maximum(float8 x, float8 y) {
    return x<y ? y : x;
}

PG_FUNC_2(maximum, float8, FLOAT8, float8, FLOAT8, float8, FLOAT8);

float8 neg_dm(float8 x) {
    return 1 - x;
}

PG_FUNC_1(neg_dm, float8, FLOAT8, float8, FLOAT8);

// Percentage Aggregate - Extended type that stores summed values

twoint *new_twoint(void) {
    return (twoint *) palloc(sizeof(twoint));
}

twoint *twoint_in(char *str) {
    twoint *result = new_twoint();

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
    sscanf(str, "%d,%d", &(result->bool_count), &(result->count));
#pragma GCC diagnostic pop

    return result;
}

PG_FUNC_1(twoint_in, twoint *, POINTER, char *, CSTRING);

char *twoint_out(twoint *t) {
    char *result = (char *) palloc(sizeof(char));
    strcpy(result, "");

    sprintf(result, "%d,%d", t->bool_count, t->count);
    return result;
}

PG_FUNC_1(twoint_out, char *, CSTRING, twoint *, POINTER);

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

PG_FUNC_2_POINTER(state_percentage, twoint *, POINTER, bool, BOOL);

float8 final_percentage(twoint *last_state) {
    return (float8) (last_state->bool_count) / last_state->count;
}

PG_FUNC_1(final_percentage, float8, FLOAT8, twoint *, POINTER);

#endif
