#ifndef TRAPEZOIDAL_LINGUISTIC_FUNCTIONS_H
#define TRAPEZOIDAL_LINGUISTIC_FUNCTIONS_H

#include "./trapezoidal_function.h"

trapezoidal_function *almost_none();

trapezoidal_function *almost_all();

trapezoidal_function *about_a_quarter();

trapezoidal_function *about_a_third();

trapezoidal_function *about_half();

trapezoidal_function *about_two_thirds();

trapezoidal_function *about_three_quarters();

trapezoidal_function *about_one();

trapezoidal_function *about_some();

trapezoidal_function *about_a_dozen();

trapezoidal_function *about_a_few_dozen();

trapezoidal_function *about_a_few_hundred();

trapezoidal_function *about_a_minute();

trapezoidal_function *about_a_quarter_of_an_hour();

trapezoidal_function *about_an_hour();

trapezoidal_function *about_a_week();

trapezoidal_function *about_a_month();

trapezoidal_function *about_a_year();


text *seconds_to_str(trapezoidal_function *func);

text *days_to_str(trapezoidal_function *func);


float8 *percentage_universal_final_func(twoint *last_state, trapezoidal_function *lingw);

float8 *percentage_almost_none(twoint *last_state);

float8 *percentage_almost_all(twoint *last_state);

float8 *percentage_about_a_quarter(twoint *last_state);

float8 *percentage_about_a_third(twoint *last_state);

float8 *percentage_about_half(twoint *last_state);

float8 *percentage_about_two_thirds(twoint *last_state);

float8 *percentage_about_three_quarters(twoint *last_state);

#endif
