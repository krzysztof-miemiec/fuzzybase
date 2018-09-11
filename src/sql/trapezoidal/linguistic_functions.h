#ifndef TRAPEZOIDAL_LINGUISTIC_FUNCTIONS_H
#define TRAPEZOIDAL_LINGUISTIC_FUNCTIONS_H

#include "function.h"

trapezoidal_function *almost_none(void);

trapezoidal_function *almost_all(void);

trapezoidal_function *about_a_quarter(void);

trapezoidal_function *about_a_third(void);

trapezoidal_function *about_half(void);

trapezoidal_function *about_two_thirds(void);

trapezoidal_function *about_three_quarters(void);

trapezoidal_function *about_one(void);

trapezoidal_function *about_some(void);

trapezoidal_function *about_a_dozen(void);

trapezoidal_function *about_a_few_dozen(void);

trapezoidal_function *about_a_few_hundred(void);

trapezoidal_function *about_a_minute(void);

trapezoidal_function *about_a_quarter_of_an_hour(void);

trapezoidal_function *about_an_hour(void);

trapezoidal_function *about_a_week(void);

trapezoidal_function *about_a_month(void);

trapezoidal_function *about_a_year(void);


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


trapezoidal_function *almost_none() { return about_r(0.00, 0.00, 0.05, 0.10); }

trapezoidal_function *almost_all() { return about_r(0.09, 0.95, 1.00, 1.00); }

trapezoidal_function *about_a_quarter() { return about_r(0.10, 0.20, 0.30, 0.40); }

trapezoidal_function *about_a_third() { return about_r(0.18, 0.28, 0.38, 0.48); }

trapezoidal_function *about_half() { return about_r(0.35, 0.45, 0.55, 0.65); }

trapezoidal_function *about_two_thirds() { return about_r(0.51, 0.61, 0.71, 0.81); }

trapezoidal_function *about_three_quarters() { return about_r(0.60, 0.70, 0.80, 0.90); }

trapezoidal_function *about_one() { return about_r(0, 1, 1, 2); }

trapezoidal_function *about_some() { return about_r(1, 3, 9, 12); }

trapezoidal_function *about_a_dozen() { return about_r(8, 12, 19, 22); }

trapezoidal_function *about_a_few_dozen() { return about_r(20, 30, 90, 120); }

trapezoidal_function *about_a_few_hundred() { return about_r(100, 300, 900, 1200); }

trapezoidal_function *about_a_minute() { return about_r(40, 60, 60, 80); }

trapezoidal_function *about_a_quarter_of_an_hour() { return about_r(10 * 60, 15 * 60, 15 * 60, 20 * 60); }

trapezoidal_function *about_an_hour() { return about_r(40 * 60, 60 * 60, 60 * 60, 80 * 60); }

trapezoidal_function *about_a_week() { return about_r(3, 7, 7, 11); }

trapezoidal_function *about_a_month() { return about_r(20, 28, 31, 39); }

trapezoidal_function *about_a_year() { return about_r(160, 365, 366, 570); }

text *seconds_to_str(trapezoidal_function *func) {
    if (func == NULL) {
        return to_text("");
    }

    if (is_equal(func, about_a_minute())) {
        return to_text("about a minute");
    }
    if (is_equal(func, about_a_quarter_of_an_hour())) {
        return to_text("about a quarter of an hour");
    }
    if (is_equal(func, about_an_hour())) {
        return to_text("about an hour");
    }
    return to_text(trapezoidal_function_out(func));
}

text *days_to_str(trapezoidal_function *func) {
    if (func == NULL) {
        return to_text("");
    }

    if (is_equal(func, about_a_week())) {
        return to_text("about a week");
    }
    if (is_equal(func, about_a_month())) {
        return to_text("about a month");
    }
    if (is_equal(func, about_a_year())) {
        return to_text("about a year");
    }

    return to_text(trapezoidal_function_out(func));
}

#endif