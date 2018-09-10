#ifndef AGGREGATE_H
#define AGGREGATE_H

#import "function.h"

trapezoidal_function_extended *state_max(trapezoidal_function_extended *state, trapezoidal_function *next_data);

trapezoidal_function_extended *state_min(trapezoidal_function_extended *state, trapezoidal_function *next_data);

trapezoidal_function *final_avg(trapezoidal_function_extended *state);

trapezoidal_function_extended *state_avg(trapezoidal_function_extended *state, trapezoidal_function *next);

#endif