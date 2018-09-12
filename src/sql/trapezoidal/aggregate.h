#ifndef AGGREGATE_H
#define AGGREGATE_H

#include "postgres.h"
#include "../general/general.h"
#include "./function.h"
#include "./operators.h"
#include "./degree.h"
#include "./linguistic_functions.h"

trapezoidal_function_extended *state_max(trapezoidal_function_extended *state, trapezoidal_function *next_data);

trapezoidal_function_extended *state_min(trapezoidal_function_extended *state, trapezoidal_function *next_data);

trapezoidal_function *final_avg(trapezoidal_function_extended *state);

trapezoidal_function_extended *state_avg(trapezoidal_function_extended *state, trapezoidal_function *next);

float8 *percentage_universal_final_func(twoint *last_state, trapezoidal_function *lingw);

/**
 * State function for MAX aggregate function
 * @param state
 * @param next_data
 * @return
 */
trapezoidal_function_extended *state_max(trapezoidal_function_extended *state, trapezoidal_function *next_data) {
    if (state == NULL || next_data == NULL) {
        return NULL;
    }
    if (state->ext == 0) {
        state->ext++;
        trapezoidal_function_assign(next_data, &(state->f));
        return state;
    };
    trapezoidal_function_assign(trapezoidal_function_max(&(state->f), next_data), &(state->f));

    return state;
};

PG_FUNCTION_INFO_V1(pg_state_max);

Datum pg_state_max(PG_FUNCTION_ARGS) {
    trapezoidal_function_extended *state = (trapezoidal_function_extended *) PG_GETARG_POINTER(0);
    trapezoidal_function *next = (trapezoidal_function *) PG_GETARG_POINTER(1);
    trapezoidal_function_extended *result = state_max(state, next);
    PG_RETURN_POINTER(result);
}

/**
 * State function for MIN aggregate function
 * @param state
 * @param next_data
 * @return
 */
trapezoidal_function_extended *state_min(trapezoidal_function_extended *state, trapezoidal_function *next_data) {
    if (state == NULL || next_data == NULL) {
        return NULL;
    }
    if (state->ext == 0) {
        state->ext++;
        trapezoidal_function_assign(next_data, &(state->f));
        return state;
    };
    trapezoidal_function_assign(trapezoidal_function_min(&(state->f), next_data), &(state->f));

    return state;
};

PG_FUNCTION_INFO_V1(pg_state_min);

Datum pg_state_min(PG_FUNCTION_ARGS) {
    trapezoidal_function_extended *state = (trapezoidal_function_extended *) PG_GETARG_POINTER(0);
    trapezoidal_function *next = (trapezoidal_function *) PG_GETARG_POINTER(1);
    trapezoidal_function_extended *result = state_min(state, next);
    PG_RETURN_POINTER(result);
}

/**
 * Final function for AVG aggregate function
 * @param state pointer to an extended trapezoidal function
 * @return pointer to trapezoidal function
 */
trapezoidal_function *final_avg(trapezoidal_function_extended *state) {
    if (state == NULL) {
        return NULL;
    }
    trapezoidal_function *result = new_trapezoidal_function();

    result->a = state->f.a / state->ext;
    result->m = state->f.m / state->ext;
    result->dm = state->f.dm / state->ext;
    result->b = state->f.b / state->ext;

    return result;
}

PG_FUNCTION_INFO_V1(pg_final_avg);

Datum pg_final_avg(PG_FUNCTION_ARGS) {
    trapezoidal_function_extended *state = (trapezoidal_function_extended *) PG_GETARG_POINTER(0);
    trapezoidal_function *result = final_avg(state);
    PG_RETURN_POINTER(result);
}

/**
 * State function for AVG aggregate function
 * @param state pointer to an extended trapezoidal function
 * @param next pointer to trapezoidal function
 * @return the pointer to next extended trapezoidal function state
 */
trapezoidal_function_extended *state_avg(trapezoidal_function_extended *state, trapezoidal_function *next) {
    trapezoidal_function_extended *result = new_trapezoidal_function_extended();

    result->ext += 1;
    f_sum_f(&result->f, next);

    return result;
}

PG_FUNCTION_INFO_V1(pg_state_avg);

Datum pg_state_avg(PG_FUNCTION_ARGS) {
    trapezoidal_function_extended *state = (trapezoidal_function_extended *) PG_GETARG_POINTER(0);
    trapezoidal_function *next = (trapezoidal_function *) PG_GETARG_POINTER(1);
    trapezoidal_function_extended *result = state_avg(state, next);
    PG_RETURN_POINTER(result);
}

/**
 * Percentage final function
 * @param last_state pointer to last state
 * @param tf pointer to lingwistic trapezoidal function
 * @return pointer to the degree of membership
 */
float8 *percentage_universal_final_func(twoint *last_state, trapezoidal_function *lingw) {
    if (last_state == NULL || lingw == NULL) {
        return NULL;
    }
    float8 percentage = (float8) last_state->bool_count / last_state->count;
    return degreefr(lingw, &percentage);
}

PG_FUNCTION_INFO_V1(pg_percentage_almost_none);

Datum pg_percentage_almost_none(PG_FUNCTION_ARGS) {
    twoint *state = (twoint *) PG_GETARG_POINTER(0);
    float8 *result = percentage_universal_final_func(state, almost_none());
    PG_RETURN_POINTER(result);
}

PG_FUNCTION_INFO_V1(pg_percentage_almost_all);

Datum pg_percentage_almost_all(PG_FUNCTION_ARGS) {
    twoint *state = (twoint *) PG_GETARG_POINTER(0);
    float8 *result = percentage_universal_final_func(state, almost_all());
    PG_RETURN_POINTER(result);
}

PG_FUNCTION_INFO_V1(pg_percentage_about_a_quarter);

Datum pg_percentage_about_a_quarter(PG_FUNCTION_ARGS) {
    twoint *state = (twoint *) PG_GETARG_POINTER(0);
    float8 *result = percentage_universal_final_func(state, about_a_quarter());
    PG_RETURN_POINTER(result);
}

PG_FUNCTION_INFO_V1(pg_percentage_about_a_third);

Datum pg_percentage_about_a_third(PG_FUNCTION_ARGS) {
    twoint *state = (twoint *) PG_GETARG_POINTER(0);
    float8 *result = percentage_universal_final_func(state, about_a_third());
    PG_RETURN_POINTER(result);
}

PG_FUNCTION_INFO_V1(pg_percentage_about_half);

Datum pg_percentage_about_half(PG_FUNCTION_ARGS) {
    twoint *state = (twoint *) PG_GETARG_POINTER(0);
    float8 *result = percentage_universal_final_func(state, about_half());
    PG_RETURN_POINTER(result);
}


PG_FUNCTION_INFO_V1(pg_percentage_about_two_thirds);

Datum pg_percentage_about_two_thirds(PG_FUNCTION_ARGS) {
    twoint *state = (twoint *) PG_GETARG_POINTER(0);
    float8 *result = percentage_universal_final_func(state, about_two_thirds());
    PG_RETURN_POINTER(result);
}

PG_FUNCTION_INFO_V1(pg_percentage_about_three_quarters);

Datum pg_percentage_about_three_quarters(PG_FUNCTION_ARGS) {
    twoint *state = (twoint *) PG_GETARG_POINTER(0);
    float8 *result = percentage_universal_final_func(state, about_three_quarters());
    PG_RETURN_POINTER(result);
}

#endif