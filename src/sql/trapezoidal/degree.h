#ifndef DEGREE_H
#define DEGREE_H

#import "function.h"

float8 degree(float8 x, trapezoidal_function f);
float8 *degreerf(float8 *x, trapezoidal_function *f);
float8 *degreefr(trapezoidal_function *f, float8 *x);
float e(float xD1, float xG1, float xD2, float xG2);
float8 degreeftofft(trapezoidal_function x, trapezoidal_function y);
float8 *degreeotrapezoidal_function(trapezoidal_function *x, trapezoidal_function *y);

#endif
