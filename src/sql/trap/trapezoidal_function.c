#include "postgres.h"
#include <stdlib.h>

#include "./trapezoidal_function.h"

trapezoidal_function *new_trapezoidal_function() {
    return (trapezoidal_function *) palloc(sizeof(trapezoidal_function));
}

trapezoidal_function_extended *new_trapezoidal_function_extended() {
    return (trapezoidal_function_extended *) palloc(sizeof(trapezoidal_function_extended));
}

/**
 * Resets the structure.
 * @param f trapezoidal function
 */
void trapezoidal_function_clear(trapezoidal_function *f) {
    f->a = 0;
    f->m = 0;
    f->dm = 0;
    f->b = 0;
}

/**
 * Assigns one trapezoidal function to another
 * @param s source
 * @param d destination
 */
void trapezoidal_function_assign(trapezoidal_function *s, trapezoidal_function *d) {
    if (s == NULL) {
        d = NULL;
    } else {
        d->a = s->a;
        d->m = s->m;
        d->dm = s->dm;
        d->b = s->b;
    }
}

/**
 * Converts the trapezoidal function string representation to a structure
 * @param str Input string in l/m~n\o format
 * @return trapezoidal function
 */
trapezoidal_function *trapezoidal_function_in(char *str) {
    float8 l, m, n, o;
    trapezoidal_function *result = new_trapezoidal_function();
    int slashPosition = charpos(str, '/');
    int tildePosition = charpos(str, '~');
    int backslashPosition = charpos(str, '\\');

    bool existsL = slashPosition >= 0;
    bool existsN = tildePosition >= 0;
    bool existsO = backslashPosition >= 0;

    // Left bound
    if (existsL) {
        sscanf(str, "%lf", &l);
    };

    // Lefthand side 100%
    sscanf(str + slashPosition + 1, "%lf", &m);

    if (!existsL) {
        l = m;
    }

    // Right-hand side 100%
    if (existsN) {
        sscanf(str + tildePosition + 1, "%lf", &n);
    } else {
        n = m;
    }

    // Right bound
    if (existsO) {
        sscanf(str + backslashPosition + 1, "%lf", &o);
    } else {
        o = n;
    }

    result->a = m - l;
    result->m = m;
    result->dm = n - m;
    result->b = o - n;

    return (result);
}

/**
 * Converts a trapezoidal function record to it's string representation
 *
 * @param f trapezoidal function
 * @return Trapezoidal function string in l/m~n\o format
 */
char *trapezoidal_function_out(trapezoidal_function *f) {
    char *result = (char *) palloc(512);

    strcpy(result, "");

    if (x->f.a != 0) {
        sprintf(result + strlen(result), "%.2f/", f->m - f->a);
    }

    sprintf(result + strlen(result), "%.2f", f->m);

    if (x->f.dm != 0) {
        sprintf(result + strlen(result), "~%.2f", f->m + f->dm);
    }
    if (x->f.b != 0) {
        sprintf(result + strlen(result), "\\%.2f", f->m + f->dm + f->b);
    }
    return result;
}

/**
 * Converts the extended trapezoidal function string representation to a structure
 * @param str Input string in ext|l/m~n\o format
 * @return Extended trapezoidal function
 */
trapezoidal_function_extended *trapezoidal_function_extended_in(char *str) {
    trapezoidal_function_extended *result = new_trapezoidal_function_extended();

    sscanf(str, "%lf", &result->ext);
    trapezoidal_function *f = trapezoidal_function_in(str + charpos(str, '|') + 1);
    trapezoidal_function_assign(&result->f, f);

    pfree(f);
    return result;
}

/**
 * Converts an extended trapezoidal function to it's string representation
 *
 * @param f trapezoidal function
 * @return Trapezoidal function string in l/m~n\o op ext format
 */
char *trapezoidal_function_extended_out(trapezoidal_function_extended *x) {
    char *result = trapezoidal_function_out(&x->f);
    sprintf(result + strlen(result), " %s %.2f", x->op, x->ext);

    return result;
}

/**
 * Extracts trapezoidal function out of extended trapezoidal function
 * @param last_state
 * @return trapezoidal function
 */
trapezoidal_function *trapezoidal_function_extended_to_trapezoidal_function(trapezoidal_function_extended *last_state) {
    if (last_state == NULL) {
        return NULL;
    }
    return &(last_state->f);
};

/**
 * Converts parameters to trapezoidal function
 *
 * @return trapezoidal function
 */
trapezoidal_function *about_r(float8 l, float8 m, float8 n, float8 o) {
    trapezoidal_function *f = new_trapezoidal_function();

    f->a = m - l;
    f->m = m;
    f->dm = n - m;
    f->b = o - n;

    return f;
}

/**
 * Converts parameter pointers to trapezoidal function
 *
 * @return trapezoidal function
 */
trapezoidal_function *about(float8 *l, float8 *m, float8 *n, float8 *o) {
    return about_r(*l, *m, *n, *o);
}