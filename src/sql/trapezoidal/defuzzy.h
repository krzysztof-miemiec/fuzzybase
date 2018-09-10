#ifndef DEFUZZY_H
#define DEFUZZY_H

#include "function.h"

bool defuzzy(float8 degree, char op[4], float8 threshold);

bool defuzzy_fext_r(trapezoidal_function_extended *fext, float8 *data);

bool not_defuzzy_fext_r(trapezoidal_function_extended *fext, float8 *data);

bool defuzzy_r_fext(float8 *data, trapezoidal_function_extended *fext);

bool not_defuzzy_r_fext(float8 *data, trapezoidal_function_extended *fext);

bool defuzzy_fext_ft(trapezoidal_function_extended *fext, trapezoidal_function *ft);

bool not_defuzzy_fext_ft(trapezoidal_function_extended *fext, trapezoidal_function *ft);

bool defuzzy_ft_fext(trapezoidal_function *ft, trapezoidal_function_extended *fext);

bool not_defuzzy_ft_fext(trapezoidal_function *ft, trapezoidal_function_extended *fext);

#endif