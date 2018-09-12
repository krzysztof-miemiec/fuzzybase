#ifndef TRAPEZOIDAL_FUNCTION_H
#define TRAPEZOIDAL_FUNCTION_H

#include "postgres.h"
#include <stdlib.h>
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

trapezoidal_function *new_trapezoidal_function(void);

trapezoidal_function_extended *new_trapezoidal_function_extended(void);

void trapezoidal_function_clear(trapezoidal_function *f);

void trapezoidal_function_assign(trapezoidal_function *s, trapezoidal_function *d);

trapezoidal_function *trapezoidal_function_from_string(char *str);

char *trapezoidal_function_to_string(trapezoidal_function *t);

trapezoidal_function *about_r(float8 l, float8 m, float8 n, float8 o);

trapezoidal_function_extended *to_fext(trapezoidal_function *ft, float8 *ext, char op[4]);

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

trapezoidal_function *trapezoidal_function_from_string(char *str) {
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

char *trapezoidal_function_to_string(trapezoidal_function *f) {
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

/**
 * Converts the trapezoidal function string representation to a structure
 * @param str Input string in l/m~n\o format
 * @return trapezoidal function
 */
PG_FUNCTION_INFO_V1(trapezoidal_function_in);

Datum trapezoidal_function_in(PG_FUNCTION_ARGS) {
    char *str = PG_GETARG_CSTRING(0);
    trapezoidal_function *result = trapezoidal_function_from_string(str);
    PG_RETURN_POINTER(result);
}


/**
 * Converts a trapezoidal function record to it's string representation
 *
 * @param f trapezoidal function
 * @return Trapezoidal function string in l/m~n\o format
 */
PG_FUNCTION_INFO_V1(trapezoidal_function_out);

Datum trapezoidal_function_out(PG_FUNCTION_ARGS) {
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(0);
    char *result = trapezoidal_function_to_string(f);
    PG_RETURN_CSTRING(result);
}

/**
 * Converts the extended trapezoidal function string representation to a structure
 * @param str Input string in ext|l/m~n\o format
 * @return Extended trapezoidal function
 */
PG_FUNCTION_INFO_V1(trapezoidal_function_extended_in);

Datum trapezoidal_function_extended_in(PG_FUNCTION_ARGS) {
    char *str = PG_GETARG_CSTRING(0);

    trapezoidal_function_extended *result = new_trapezoidal_function_extended();
    sscanf(str, "%lf", &result->ext);
    trapezoidal_function *f = trapezoidal_function_from_string(str + charpos(str, '|') + 1);
    trapezoidal_function_assign(&result->f, f);
    pfree(f);

    PG_RETURN_POINTER(result);
}

/**
 * Converts an extended trapezoidal function to it's string representation
 *
 * @param f trapezoidal function
 * @return Trapezoidal function string in l/m~n\o op ext format
 */
PG_FUNCTION_INFO_V1(trapezoidal_function_extended_out);

Datum trapezoidal_function_extended_out(PG_FUNCTION_ARGS) {
    trapezoidal_function_extended *x = (trapezoidal_function_extended *) PG_GETARG_POINTER(0);

    char *result = trapezoidal_function_to_string(&x->f);
    sprintf(result + strlen(result), " %s %.2f", x->op, x->ext);

    PG_RETURN_CSTRING(result);
}

/**
 * trapezoidal_function *trapezoidal_function_ext_to_trapezoidal_function(trapezoidal_function_extended *last_state)
 * Extracts trapezoidal function out of extended trapezoidal function
 * @param last_state
 * @return trapezoidal function
 */
PG_FUNCTION_INFO_V1(trapezoidal_function_ext_to_trapezoidal_function);

Datum trapezoidal_function_ext_to_trapezoidal_function(PG_FUNCTION_ARGS) {
    trapezoidal_function_extended *last_state = (trapezoidal_function_extended *) PG_GETARG_POINTER(0);
    if (last_state == NULL) {
        PG_RETURN_NULL();
    }
    trapezoidal_function *result = &(last_state->f);
    PG_RETURN_POINTER(result);
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

PG_FUNCTION_INFO_V1(to_fext_equal);

Datum to_fext_equal(PG_FUNCTION_ARGS) {
    trapezoidal_function *ft = (trapezoidal_function *) PG_GETARG_POINTER(0);
    float8 *ext = (float8 *) PG_GETARG_POINTER(1);
    trapezoidal_function_extended *result = to_fext(ft, ext, "*=");
    PG_RETURN_POINTER(result);
};

/**
 * Creates an extended trapezoidal function with not equal operator
 * @param ft pointer to trapezoidal function
 * @param ext pointer to extension
 * @return a pointer to a new extended trapezoidal function (with an extension and operator)
 */
PG_FUNCTION_INFO_V1(to_fext_not_equal);

Datum to_fext_not_equal(PG_FUNCTION_ARGS) {
    trapezoidal_function *ft = (trapezoidal_function *) PG_GETARG_POINTER(0);
    float8 *ext = (float8 *) PG_GETARG_POINTER(1);
    trapezoidal_function_extended *result = to_fext(ft, ext, "*<>");
    PG_RETURN_POINTER(result);
};

/**
 * Creates an extended trapezoidal function with greater operator
 * @param ft pointer to trapezoidal function
 * @param ext pointer to extension
 * @return a pointer to a new extended trapezoidal function (with an extension and operator)
 */
PG_FUNCTION_INFO_V1(to_fext_greater);

Datum to_fext_greater(PG_FUNCTION_ARGS) {
    trapezoidal_function *ft = (trapezoidal_function *) PG_GETARG_POINTER(0);
    float8 *ext = (float8 *) PG_GETARG_POINTER(1);
    trapezoidal_function_extended *result = to_fext(ft, ext, "*>");
    PG_RETURN_POINTER(result);
};

/**
 * Creates an extended trapezoidal function with greater or equal operator
 * @param ft pointer to trapezoidal function
 * @param ext pointer to extension
 * @return a pointer to a new extended trapezoidal function (with an extension and operator)
 */
PG_FUNCTION_INFO_V1(to_fext_greater_equal);

Datum to_fext_greater_equal(PG_FUNCTION_ARGS) {
    trapezoidal_function *ft = (trapezoidal_function *) PG_GETARG_POINTER(0);
    float8 *ext = (float8 *) PG_GETARG_POINTER(1);
    trapezoidal_function_extended *result = to_fext(ft, ext, "*>=");
    PG_RETURN_POINTER(result);
};

/**
 * Creates an extended trapezoidal function with lower operator
 * @param ft pointer to trapezoidal function
 * @param ext pointer to extension
 * @return a pointer to a new extended trapezoidal function (with an extension and operator)
 */
PG_FUNCTION_INFO_V1(to_fext_lower);

Datum to_fext_lower(PG_FUNCTION_ARGS) {
    trapezoidal_function *ft = (trapezoidal_function *) PG_GETARG_POINTER(0);
    float8 *ext = (float8 *) PG_GETARG_POINTER(1);
    trapezoidal_function_extended *result = to_fext(ft, ext, "*<");
    PG_RETURN_POINTER(result);
};

/**
 * Creates an extended trapezoidal function with lower or equal operator
 * @param ft pointer to trapezoidal function
 * @param ext pointer to extension
 * @return a pointer to a new extended trapezoidal function (with an extension and operator)
 */
PG_FUNCTION_INFO_V1(to_fext_lower_equal);

Datum to_fext_lower_equal(PG_FUNCTION_ARGS) {
    trapezoidal_function *ft = (trapezoidal_function *) PG_GETARG_POINTER(0);
    float8 *ext = (float8 *) PG_GETARG_POINTER(1);
    trapezoidal_function_extended *result = to_fext(ft, ext, "*<=");
    PG_RETURN_POINTER(result);
};

#endif
