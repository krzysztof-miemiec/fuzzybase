#ifndef AGGREGATE_H
#define AGGREGATE_H

#include "postgres.h"
#include "./function.h"
#include "./operators.h"
#include "./degree.h"
#include "./linguistic_functions.h"

trapezoidal_function_extended *state_max(trapezoidal_function_extended *state, trapezoidal_function *next_data);

trapezoidal_function_extended *state_min(trapezoidal_function_extended *state, trapezoidal_function *next_data);

trapezoidal_function *final_avg(trapezoidal_function_extended *state);

trapezoidal_function_extended *state_avg(trapezoidal_function_extended *state, trapezoidal_function *next);

float8 *percentage_universal_final_func(twoint *last_state, trapezoidal_function *lingw);

float8 *percentage_almost_none(twoint *last_state);

float8 *percentage_almost_all(twoint *last_state);

float8 *percentage_about_a_quarter(twoint *last_state);

float8 *percentage_about_a_third(twoint *last_state);

float8 *percentage_about_half(twoint *last_state);

float8 *percentage_about_two_thirds(twoint *last_state);

float8 *percentage_about_three_quarters(twoint *last_state);

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

float8 *percentage_almost_none(twoint *last_state) {
    return percentage_universal_final_func(last_state, almost_none());
}

float8 *percentage_almost_all(twoint *last_state) {
    return percentage_universal_final_func(last_state, almost_all());
}

float8 *percentage_about_a_quarter(twoint *last_state) {
    return percentage_universal_final_func(last_state, about_a_quarter());
}

float8 *percentage_about_a_third(twoint *last_state) {
    return percentage_universal_final_func(last_state, about_a_third());
}

float8 *percentage_about_half(twoint *last_state) {
    return percentage_universal_final_func(last_state, about_half());
}

float8 *percentage_about_two_thirds(twoint *last_state) {
    return percentage_universal_final_func(last_state, about_two_thirds());
}

float8 *percentage_about_three_quarters(twoint *last_state) {
    return percentage_universal_final_func(last_state, about_three_quarters());
}

#endif