#ifndef TRAPEZOIDAL_FUNCTION_H
#define TRAPEZOIDAL_FUNCTION_H

#include "../general/general.h"

// Prototypes
typedef struct {
    float8 a, m, dm, b;
} trapezoidal_function;

typedef struct {
    float8 ext;
    trapezoidal_function f;
    char op[4];
} trapezoidal_function_extended;

trapezoidal_function *new_trapezoidal_function(void);

trapezoidal_function_extended *new_trapezoidal_function_extended(void);

void trapezoidal_function_clear(trapezoidal_function *f);

void trapezoidal_function_assign(trapezoidal_function *s, trapezoidal_function *d);

trapezoidal_function *trapezoidal_function_in(char *str);

char *trapezoidal_function_out(trapezoidal_function *f);

trapezoidal_function_extended *trapezoidal_function_extended_in(char *str);

char *trapezoidal_function_extended_out(trapezoidal_function_extended *x);

trapezoidal_function *trapezoidal_function_extended_to_trapezoidal_function(trapezoidal_function_extended *last_state);

trapezoidal_function *about_r(float8 l, float8 m, float8 n, float8 o);

trapezoidal_function *about(float8 *l, float8 *m, float8 *n, float8 *o);

trapezoidal_function_extended *to_fext(trapezoidal_function *ft, float8 *ext, char op[4]);

trapezoidal_function_extended *to_fext_equal(trapezoidal_function *ft, float8 *ext);

trapezoidal_function_extended *to_fext_not_equal(trapezoidal_function *ft, float8 *ext);

trapezoidal_function_extended *to_fext_greater(trapezoidal_function *ft, float8 *ext);

trapezoidal_function_extended *to_fext_greater_equal(trapezoidal_function *ft, float8 *ext);

trapezoidal_function_extended *to_fext_lower(trapezoidal_function *ft, float8 *ext);

trapezoidal_function_extended *to_fext_lower_equal(trapezoidal_function *ft, float8 *ext);

#endif
