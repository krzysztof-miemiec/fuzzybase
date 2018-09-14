#ifndef TRAPEZOIDAL_FUNCTION_H
#define TRAPEZOIDAL_FUNCTION_H

#include "postgres.h"
#include <stdlib.h>
#include "../general/utils.h"
#include "../general/extension.h"

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

char *trapezoidal_function_out(trapezoidal_function *t);

trapezoidal_function_extended *trapezoidal_function_extended_in(char *str);

char *trapezoidal_function_extended_out(trapezoidal_function_extended *t);

trapezoidal_function *about_r(float8 l, float8 m, float8 n, float8 o);

trapezoidal_function_extended *to_fext(trapezoidal_function *ft, float8 *ext, char op[4]);

trapezoidal_function *trapezoidal_function_ext_to_trapezoidal_function(trapezoidal_function_extended *last_state);

trapezoidal_function *new_trapezoidal_function() {
    return (trapezoidal_function *) palloc(sizeof(trapezoidal_function));
}

trapezoidal_function_extended *new_trapezoidal_function_extended() {
    return (trapezoidal_function_extended *) palloc(sizeof(trapezoidal_function_extended));
}

trapezoidal_function_extended *to_fext_equal(trapezoidal_function *ft, float8 *ext);

trapezoidal_function_extended *to_fext_not_equal(trapezoidal_function *ft, float8 *ext);

trapezoidal_function_extended *to_fext_greater(trapezoidal_function *ft, float8 *ext);

trapezoidal_function_extended *to_fext_greater_equal(trapezoidal_function *ft, float8 *ext);

trapezoidal_function_extended *to_fext_lower(trapezoidal_function *ft, float8 *ext);

trapezoidal_function_extended *to_fext_lower_equal(trapezoidal_function *ft, float8 *ext);

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

    return result;
}

PG_FUNC_1(trapezoidal_function_in, trapezoidal_function*, POINTER, char*, CSTRING);

char *trapezoidal_function_out(trapezoidal_function *f) {
    char *result = (char *) palloc(512);

    strcpy(result, "");

    if (f->a != 0) {
        sprintf(result + strlen(result), "%.2f/", f->m - f->a);
    }

    sprintf(result + strlen(result), "%.2f", f->m);

    if (f->dm != 0) {
        sprintf(result + strlen(result), "~%.2f", f->m + f->dm);
    }
    if (f->b != 0) {
        sprintf(result + strlen(result), "\\%.2f", f->m + f->dm + f->b);
    }
    return result;
}

PG_FUNC_1(trapezoidal_function_out, char*, CSTRING, trapezoidal_function*, POINTER);

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

PG_FUNC_1(trapezoidal_function_extended_in, trapezoidal_function_extended*, POINTER, char*, CSTRING);

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

PG_FUNC_1(trapezoidal_function_extended_out, char*, CSTRING, trapezoidal_function_extended*, POINTER);

/**
 * trapezoidal_function *trapezoidal_function_ext_to_trapezoidal_function(trapezoidal_function_extended *last_state)
 * Extracts trapezoidal function out of extended trapezoidal function
 * @param last_state
 * @return trapezoidal function
 */
trapezoidal_function *trapezoidal_function_ext_to_trapezoidal_function(trapezoidal_function_extended *last_state) {
    if (last_state == NULL) {
        return NULL;
    }
    return &(last_state->f);
};

PG_FUNC_1(trapezoidal_function_ext_to_trapezoidal_function, trapezoidal_function*, POINTER,
          trapezoidal_function_extended*, POINTER);

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
PG_FUNCTION_INFO_V1(about);

Datum about(PG_FUNCTION_ARGS) {
    float8 l = PG_GETARG_FLOAT8(0);
    float8 m = PG_GETARG_FLOAT8(1);
    float8 n = PG_GETARG_FLOAT8(2);
    float8 o = PG_GETARG_FLOAT8(3);

    trapezoidal_function *result = about_r(l, m, n, o);

    PG_RETURN_POINTER(result);
}

/**
 * Creates an extended trapezoidal function out of trapezoidal function, extension and operator
 * @param ft pointer to trapezoidal function
 * @param ext extension
 * @param op operator
 * @return a pointer to a new extended trapezoidal function (with an extension and operator)
 */
trapezoidal_function_extended *to_fext(trapezoidal_function *ft, float8 *ext, char op[4]) {
    if (ft == NULL || ext == NULL || op == NULL) {
        return NULL;
    }
    trapezoidal_function_extended *result = new_trapezoidal_function_extended();

    result->ext = *ext;
    trapezoidal_function_assign(ft, &result->f);
    strncpy(result->op, op, 4);

    return result;
}

/**
 * Creates an extended trapezoidal function with equal operator
 * @param ft pointer to trapezoidal function
 * @param ext pointer to extension
 * @return a pointer to a new extended trapezoidal function (with an extension and operator)
 */
trapezoidal_function_extended *to_fext_equal(trapezoidal_function *ft, float8 *ext) {
    return to_fext(ft, ext, "*=");
};

PG_FUNC_2(to_fext_equal, trapezoidal_function_extended*, POINTER, trapezoidal_function*, POINTER, float8 *, POINTER);

/**
 * Creates an extended trapezoidal function with not equal operator
 * @param ft pointer to trapezoidal function
 * @param ext pointer to extension
 * @return a pointer to a new extended trapezoidal function (with an extension and operator)
 */
trapezoidal_function_extended *to_fext_not_equal(trapezoidal_function *ft, float8 *ext) {
    return to_fext(ft, ext, "*<>");
};

PG_FUNC_2(to_fext_not_equal, trapezoidal_function_extended*, POINTER, trapezoidal_function*, POINTER, float8 *,
          POINTER);

/**
 * Creates an extended trapezoidal function with greater operator
 * @param ft pointer to trapezoidal function
 * @param ext pointer to extension
 * @return a pointer to a new extended trapezoidal function (with an extension and operator)
 */
trapezoidal_function_extended *to_fext_greater(trapezoidal_function *ft, float8 *ext) {
    return to_fext(ft, ext, "*>");
};

PG_FUNC_2(to_fext_greater, trapezoidal_function_extended*, POINTER, trapezoidal_function*, POINTER, float8 *, POINTER);

/**
 * Creates an extended trapezoidal function with greater or equal operator
 * @param ft pointer to trapezoidal function
 * @param ext pointer to extension
 * @return a pointer to a new extended trapezoidal function (with an extension and operator)
 */
trapezoidal_function_extended *to_fext_greater_equal(trapezoidal_function *ft, float8 *ext) {
    return to_fext(ft, ext, "*>=");
};

PG_FUNC_2(to_fext_greater_equal, trapezoidal_function_extended*, POINTER, trapezoidal_function*, POINTER, float8 *,
          POINTER);

/**
 * Creates an extended trapezoidal function with lower operator
 * @param ft pointer to trapezoidal function
 * @param ext pointer to extension
 * @return a pointer to a new extended trapezoidal function (with an extension and operator)
 */
trapezoidal_function_extended *to_fext_lower(trapezoidal_function *ft, float8 *ext) {
    return to_fext(ft, ext, "*<");
};

PG_FUNC_2(to_fext_lower, trapezoidal_function_extended*, POINTER, trapezoidal_function*, POINTER, float8 *, POINTER);

/**
 * Creates an extended trapezoidal function with lower or equal operator
 * @param ft pointer to trapezoidal function
 * @param ext pointer to extension
 * @return a pointer to a new extended trapezoidal function (with an extension and operator)
 */
trapezoidal_function_extended *to_fext_lower_equal(trapezoidal_function *ft, float8 *ext) {
    return to_fext(ft, ext, "*<=");
};

PG_FUNC_2(to_fext_lower_equal, trapezoidal_function_extended*, POINTER, trapezoidal_function*, POINTER, float8 *,
          POINTER);

#endif
