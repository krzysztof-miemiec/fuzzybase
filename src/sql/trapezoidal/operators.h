#ifndef TRAPEZOIDAL_OPERATORS_H
#define TRAPEZOIDAL_OPERATORS_H

#include "function.h"

trapezoidal_function *minus_f(trapezoidal_function *f);

trapezoidal_function *f_sum_r(trapezoidal_function *f, float8 *r);

trapezoidal_function *r_sum_f(float8 *r, trapezoidal_function *f);

trapezoidal_function *f_sub_r(trapezoidal_function *f, float8 *r);

trapezoidal_function *r_sub_f(float8 *r, trapezoidal_function *f);

trapezoidal_function *f_sum_f(trapezoidal_function *x, trapezoidal_function *y);

trapezoidal_function *f_sub_f(trapezoidal_function *x, trapezoidal_function *y);

trapezoidal_function *f_mul_r(trapezoidal_function *f, float8 *r);

trapezoidal_function *r_mul_f(float8 *r, trapezoidal_function *f);

trapezoidal_function *f_div_r(trapezoidal_function *f, float8 *r);

trapezoidal_function *r_div_f(float8 *r, trapezoidal_function *f);

trapezoidal_function *f_mul_f(trapezoidal_function *a, trapezoidal_function *b);

trapezoidal_function *f_div_f(trapezoidal_function *a, trapezoidal_function *b);

trapezoidal_function *trapezoidal_function_min(trapezoidal_function *a, trapezoidal_function *b);

trapezoidal_function *trapezoidal_function_max(trapezoidal_function *a, trapezoidal_function *b);

bool is_equal(trapezoidal_function *a, trapezoidal_function *b);

bool is_lower(trapezoidal_function *a, trapezoidal_function *b);

bool is_greater(trapezoidal_function *a, trapezoidal_function *b);

bool is_greater_equal(trapezoidal_function *a, trapezoidal_function *b);

bool is_lower_equal(trapezoidal_function *a, trapezoidal_function *b);

bool not_equal(trapezoidal_function *a, trapezoidal_function *b);

int trapezoidal_function_abs_cmp(trapezoidal_function *a, trapezoidal_function *b);

#endif
