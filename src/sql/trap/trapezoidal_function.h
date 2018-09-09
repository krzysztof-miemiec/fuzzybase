#ifndef TRAPEZOIDAL_FUNCTION_H
#define TRAPEZOIDAL_FUNCTION_H

#include "../general/general.h"
#include "../general/utils.h"

// Prototypes
typedef struct {
    float8 a, m, dm, b;
} trapezoidal_function;

typedef struct {
    float8 ext;
    trapezoidal_function f;
    char op[4];
} trapezoidal_function_extended;

trapezoidal_function *new_trapezoidal_function();
trapezoidal_function_extended *new_trapezoidal_function_extended();

void trapezoidal_function_clear(trapezoidal_function *f);
void trapezoidal_function_assign(trapezoidal_function *s, trapezoidal_function *d);

trapezoidal_function *trapezoidal_function_in(char *str);
char *trapezoidal_function_out(trapezoidal_function *f);

#endif
