#include "postgres.h"
#include <stdlib.h>

#include "./trapezoidal_function.h"

/**
 * Negates the trapezoidal function (-f)
 *
 * @param f trapezoidal function pointer
 * @return -f
 */
trapezoidal_function *minus_f(trapezoidal_function *f) {
    float8 b2 = 0;
    if (f == NULL) {
        return NULL;
    }
    b2 = f->a;
    f->m = -(f->m + f->dm);
    f->dm = f->dm;
    f->a = f->b;
    f->b = b2;

    return f;
}

/**
 * Adds a number to a trapezoidal function
 *
 * @param f trapezoidal function pointer
 * @param r number pointer
 * @return f+r
 */
trapezoidal_function *f_sum_r(trapezoidal_function *f, float8 *r) {
    if ((f == NULL) || (r == NULL)) {
        return NULL;
    }

    f->m += *r;
    return f;
}

/**
 * Adds a trapezoidal function to a number
 *
 * @param r number pointer
 * @param f trapezoidal function pointer
 * @return r+f
 */
trapezoidal_function *r_sum_f(float8 *r, trapezoidal_function *f) {
    if ((f == NULL) || (r == NULL)) {
        return NULL;
    }
    return f_sum_r(f, r);
};

/**
 * Subtracts a number from a trapezoidal function
 *
 * @param r number pointer
 * @param f trapezoidal function pointer
 * @return f-r
 */
trapezoidal_function *f_sub_r(trapezoidal_function *f, float8 *r) {
    if ((f == NULL) || (r == NULL)) {
        return NULL;
    }
    f->m -= *r;
    return f;
};

/**
 * Subtracts a trapezoidal function from a number
 *
 * @param f trapezoidal function pointer
 * @param r number pointer
 * @return r-f
 */
trapezoidal_function *r_sub_f(float8 *r, trapezoidal_function *f) {
    if ((f == NULL) || (r == NULL)) {
        return NULL;
    }
    return minus_f(f_sub_r(f, r));
}

/**
 * Sums two trapezoidal functions
 * @param x left-hand side function
 * @param y right-hand side function
 * @return x=x+y
 */
trapezoidal_function *f_sum_f(trapezoidal_function *x, trapezoidal_function *y) {
    if ((x == NULL) || (y == NULL)) {
        return NULL;
    }

    x->a += y->a;
    x->m += y->m;
    x->dm += y->dm;
    x->b += y->b;

    return x;
}

/**
 * Subtracts trapezoidal function from other trapezoidal function
 * @param x left-hand side function
 * @param y right-hand side function
 * @return x-y
 */
trapezoidal_function *f_sub_f(trapezoidal_function *x, trapezoidal_function *y) {
    if ((x == NULL) || (y == NULL)) {
        return NULL;
    }

    x->a -= y->a;
    x->m -= y->m;
    x->dm -= y->dm;
    x->b -= y->b;

    return x;
}

/**
 * Multiplies trapezoidal function by a number
 * @param f left-hand side function
 * @param r right-hand side number
 * @return f*r
 */
trapezoidal_function *f_mul_r(trapezoidal_function *f, float8 *r) {
    if ((f == NULL) || (r == NULL)) {
        return NULL;
    }

    f->a * = *r;
    f->m * = *r;
    f->dm * = *r;
    f->b * = *r;

    return f;
}

/**
 * Multiplies trapezoidal function by a number
 * @param r left-hand side number
 * @param f right-hand side function
 * @return r*f
 */
trapezoidal_function *r_mul_f(float8 *r, trapezoidal_function *f) {
    if ((f == NULL) || (r == NULL)) {
        return NULL;
    }
    return f_mul_r(f, r);
}

/**
 * Divides trapezoidal function by a number
 * @param f left-hand side function
 * @param r right-hand side number
 * @return f*r
 */
trapezoidal_function *f_div_r(trapezoidal_function *f, float8 *r) {
    if ((f == NULL) || (r == NULL) || (r == 0)) {
        return NULL;
    }

    f->a /= *r;
    f->m /= *r;
    f->dm /= *r;
    f->b /= *r;

    return f;
}

/**
 * Divides a number by trapezoidal function
 * @param r left-hand side number
 * @param f right-hand side function
 * @return f*r
 */
trapezoidal_function *r_div_f(float8 *r, trapezoidal_function *f) {
    if ((f == NULL) || (r == NULL) || (r == 0)) {
        return NULL;
    }

    f->a = *r / f->a;
    f->m = *r / f->m;
    f->dm = *r / f->dm;
    f->b = *r / f->b;

    return f;
}

/**
 * Multiplies trapezoidal function by another function
 * @param a left-hand side function
 * @param b right-hand side function
 * @return a*b
 */
trapezoidal_function *f_mul_f(trapezoidal_function *a, trapezoidal_function *b) {
    if ((a == NULL) || (b == NULL)) {
        return NULL;
    }

    trapezoidal_function *f = new_trapezoidal_function();
    float8 al, an, ao, bl, bn, bo;

    al = a->m - a->a;
    an = a->m + a->dm;
    ao = an + a->b;

    bl = b->m - b->a;
    bn = b->m + b->dm;
    bo = bn + b->b;

    f->m = a->m * b->m;
    f->a = f->m - (al * bl);
    f->dm = (an * bn) - f->m;
    f->b = (ao * bo) - f->dm;

    return f;
}

/**
 * Divides trapezoidal function by another function
 * @param a left-hand side function
 * @param b right-hand side function
 * @return a/b
 */
trapezoidal_function *f_div_f(trapezoidal_function *a, trapezoidal_function *b) {
    float8 al, an, ao, bl, bn, bo;

    al = a->m - a->a;
    an = a->m + a->dm;
    ao = an + a->b;

    bl = b->m - b->a;
    bn = b->m + b->dm;
    bo = bn + b->b;

    if (a == NULL || b == NULL || bl == 0 || b->m == 0 || bn == 0 || bo == 0) {
        return NULL;
    }

    trapezoidal_function *f = new_trapezoidal_function();

    f->m = a->m / b->m;
    f->a = f->m - (al / bl);
    f->dm = (an / bn) - f->m;
    f->b = (ao / bo) - f->dm;

    return f;
}

/**
 * Finds the trapezoidal function with smaller value
 * @param a left-hand side function
 * @param b right-hand side function
 * @return the function with smaller value
 */
trapezoidal_function *trapezoidal_function_min(trapezoidal_function *a, trapezoidal_function *b) {
    if (a == NULL || b == NULL) {
        return NULL;
    }
    if (a->m < b->m) {
        return a;
    }
    return b;
}

/**
 * Finds the trapezoidal function with bigger value
 * @param a left-hand side function
 * @param b right-hand side function
 * @return the function with bigger value
 */
trapezoidal_function *trapezoidal_function_max(trapezoidal_function *a, trapezoidal_function *b) {
    if (a == NULL || b == NULL) {
        return NULL;
    }
    if (a->m > b->m) {
        return a;
    }
    return b;
}


/**
 * Compares two trapezoidal functions
 * @param a left-hand side function
 * @param b right-hand side function
 * @return true if functions are equal, false otherwise
 */
bool is_equal(trapezoidal_function *a, trapezoidal_function *b) {
    if (a == NULL || b == NULL) {
        return false;
    }
    return (a->a == b->a) && (a->m == b->m) && (a->dm == b->dm) && (a->b == b->b);
}

/**
 * Compares two trapezoidal functions
 * @param a left-hand side function
 * @param b right-hand side function
 * @return true if left-hand side function is lower than right-hand side, false otherwise
 */
bool is_lower(trapezoidal_function *a, trapezoidal_function *b) {
    if (a == NULL || b == NULL) {
        return false;
    }
    return (a->m < b->m);
}

/**
 * Compares two trapezoidal functions
 * @param a left-hand side function
 * @param b right-hand side function
 * @return true if left-hand side function is greater than right-hand side, false otherwise
 */
bool is_greater(trapezoidal_function *a, trapezoidal_function *b) {
    if (a == NULL || b == NULL) {
        return false;
    }
    return (a->m + a->dm > b->m + b->dm);
}

/**
 * Compares two trapezoidal functions
 * @param a left-hand side function
 * @param b right-hand side function
 * @return true if left-hand side function is greater or equal than right-hand side, false otherwise
 */
bool is_greater_equal(trapezoidal_function *a, trapezoidal_function *b) {
    if (a == NULL || b == NULL) {
        return false;
    }
    return is_greater(a, b) || is_equal(a, b);
}

/**
 * Compares two trapezoidal functions
 * @param a left-hand side function
 * @param b right-hand side function
 * @return true if left-hand side function is lower or equal than right-hand side, false otherwise
 */
bool is_lower_equal(trapezoidal_function *a, trapezoidal_function *b) {
    if (a == NULL || b == NULL) {
        return false;
    }
    return is_lower(a, b) || is_equal(a, b);
}

/**
 * Compares two trapezoidal functions
 * @param a left-hand side function
 * @param b right-hand side function
 * @return true if left-hand side function is not equal than right-hand side, false otherwise
 */
bool not_equal(trapezoidal_function *a, trapezoidal_function *b) {
    if (a == NULL || b == NULL) {
        return false;
    }
    return (a->a != b->a) || (a->m != b->m) || (a->dm != b->dm) || (a->b != b->b);
}

/**
 * Compares two trapezoidal functions
 * @param a left-hand side function
 * @param b right-hand side function
 * @return -1 if a<b, 0 if a=b, 1 if a>b
 */
int trapezoidal_function_abs_cmp(trapezoidal_function *a, trapezoidal_function *b) {
    return is_lower(a, b)
           ? -1
           : is_greater(a, b)
             ? 1
             : 0;
}

/**
 * Calculates the degree of membership of value x to function f
 * @param x numeric value
 * @param f trapezoidal function
 * @return the degree of membership of value x to function f
 */
float8 degree(float8 x, trapezoidal_function f) {
    float8 l = f.m - f.a;
    float8 m = f.m;
    float8 n = f.m + f.dm;
    float8 o = f.m + f.dm + f.b;

    if (x >= m && x <= n) {
        return 1;
    }
    if (x > l && x < m) {
        return (x - l) / (m - l);
    }
    if (x > n && x < o) {
        return (o - x) / (o - n);
    }
    return 0;
};


/**
 * Calculates the degree of membership of value x to function f
 * @param x pointer to a numeric value
 * @param f pointer to a trapezoidal function
 * @return pointer to the degree of membership of value x to function f
 */
float8 *degreerf(float8 *x, trapezoidal_function *f) {
    if (x == NULL || f == NULL) {
        return NULL;
    }

    float8 *result = (float8 *) palloc(sizeof(float8));
    *result = degree(*x, *f);
    return result;
};

/**
 * Calculates the degree of membership of value x to function f
 * @param f pointer to a trapezoidal function
 * @param x pointer to a numeric value
 * @return pointer to a numeric value, with overridden value of the degree of membership of value x to function f
 */
float8 *degreefr(trapezoidal_function *f, float8 *x) {
    if (x == NULL || f == NULL) {
        return NULL;
    }
    *x = degree(*x, *f);
    return x;
};

/**
 * Finds max of four
 * @param a
 * @param b
 * @param c
 * @param d
 * @return The value which is the highest out of a, b, c, d
 */
float max4(float a, float b, float c, float d) {
    if (a < b) {
        a = b;
    }
    if (a < c) {
        a = c;
    }
    if (a < d) {
        a = d;
    }
    return a;
};

/**
 * Calculates the degree of membership basing on edges of two trapezoidal functions
 * @param xD1 edge point of first trapezoidal function
 * @param xG1 edge point of first trapezoidal function
 * @param xD2 edge point of second trapezoidal function
 * @param xG2 edge point of second trapezoidal function
 * @return the (partial result) degree of membership of trapezoidal function
 */
float e(float xD1, float xG1, float xD2, float xG2) {
    if ((xD1 < xD2 && xG1 > xG2) || (xD2 < xD1 && xG2 > xG1)) {
        return (xD1 - xD2) / ((xG2 - xD2) - (xG1 - xD1));
    }
    return 0;
};

/**
 * Calculates the degree of membership of function x to function y
 * @param x trapezoidal function
 * @param y trapezoidal function
 * @return f the degree of membership of function x to function y
 */
float8 degreeftofft(trapezoidal_function x, trapezoidal_function y) {
    if ((x.m <= y.m && x.m + x.dm >= y.m) || (y.m <= x.m && y.m + y.dm >= x.m)) {
        return 1;
    }
    return max4(
            e(x.m - x.a, x.m, y.m - y.a, y.m),
            e(x.m - x.a, x.m, y.m + y.dm + y.b, y.m + y.dm),
            e(x.m + x.dm + x.b, x.m + x.dm, y.m - y.a, y.m),
            e(x.m + x.dm + x.b, x.m + x.dm, y.m + y.dm + y.b, y.m + y.dm)
    );
}

/**
 * Calculates the degree of membership of function x to function y
 * @param x pointer to trapezoidal function
 * @param y pointer to trapezoidal function
 * @return f pointer to the degree of membership of function x to function y
 */
float8 *degreeotrapezoidal_function(trapezoidal_function *x, trapezoidal_function *y) {
    if (x == NULL || y == NULL) {
        return NULL;
    }

    float8 *result = (float8 *) palloc(sizeof(float8));
    *result = degreeftofft(*x, *y);
    return result;
}

/**
 * State function for MAX aggregate function
 * @param state
 * @param next_data
 * @return
 */
trapezoidal_function_extended *state_max(trapezoidal_function_extended *state, trapezoidal_function *next_data) {
    if (state == NULL || next_data == NULL) {
        return NULL;
    }
    if (state->ext == 0) {
        state->ext++;
        trapezoidal_function_assign(next_data, &(state->f));
        return state;
    };
    trapezoidal_function_assign(trapezoidal_function_max(&(state->f), next_data), &(state->f));

    return state;
};

/**
 * State function for MIN aggregate function
 * @param state
 * @param next_data
 * @return
 */
trapezoidal_function_extended *state_min(trapezoidal_function_extended *state, trapezoidal_function *next_data) {
    if (state == NULL || next_data == NULL) {
        return NULL;
    }
    if (state->ext == 0) {
        state->ext++;
        assigntrapezoidal_function(next_data, &(state->f));
        return state;
    };
    assigntrapezoidal_function(trapezoidal_functionmin(&(state->f), next_data), &(state->f));

    return state;
};


/**
 * Final function for AVG aggregate function
 * @param state pointer to an extended trapezoidal function
 * @return pointer to trapezoidal function
 */
trapezoidal_function *final_avg(trapezoidal_function_extended *state) {
    if (state == NULL) {
        return NULL;
    }
    trapezoidal_function *result = new_trapezoidal_function();

    result->a = state->f.a / state->ext;
    result->m = state->f.m / state->ext;
    result->dm = state->f.dm / state->ext;
    result->b = state->f.b / state->ext;

    return result;
}

//funkcja state dla funkcji agregujacej average
/**
 * State function for AVG aggregate function
 * @param state pointer to an extended trapezoidal function
 * @param next pointer to trapezoidal function
 * @return the pointer to next extended trapezoidal function state
 */
trapezoidal_function_extended *state_avg(trapezoidal_function_extended *state, trapezoidal_function *next) {
    trapezoidal_function_extended *result = new_trapezoidal_function_extended();

    result->ext += 1;
    f_sum_f(&result->f, next);

    return result;
}


// SUBQUERIES

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
    trapezoidal_function_assign(ft, &result->f)
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

/**
 * Creates an extended trapezoidal function with not equal operator
 * @param ft pointer to trapezoidal function
 * @param ext pointer to extension
 * @return a pointer to a new extended trapezoidal function (with an extension and operator)
 */
trapezoidal_function_extended *to_fext_not_equal(trapezoidal_function *ft, float8 *ext) {
    return to_fext(ft, ext, "*<>");
};

/**
 * Creates an extended trapezoidal function with greater operator
 * @param ft pointer to trapezoidal function
 * @param ext pointer to extension
 * @return a pointer to a new extended trapezoidal function (with an extension and operator)
 */
trapezoidal_function_extended *to_fext_greater(trapezoidal_function *ft, float8 *ext) {
    return to_fext(ft, ext, "*>");
};

/**
 * Creates an extended trapezoidal function with greater or equal operator
 * @param ft pointer to trapezoidal function
 * @param ext pointer to extension
 * @return a pointer to a new extended trapezoidal function (with an extension and operator)
 */
trapezoidal_function_extended *to_fext_greater_equal(trapezoidal_function *ft, float8 *ext) {
    return to_fext(ft, ext, "*>=");
};

/**
 * Creates an extended trapezoidal function with lower operator
 * @param ft pointer to trapezoidal function
 * @param ext pointer to extension
 * @return a pointer to a new extended trapezoidal function (with an extension and operator)
 */
trapezoidal_function_extended *to_fext_lower(trapezoidal_function *ft, float8 *ext) {
    return to_fext(ft, ext, "*<");
};

/**
 * Creates an extended trapezoidal function with lower or equal operator
 * @param ft pointer to trapezoidal function
 * @param ext pointer to extension
 * @return a pointer to a new extended trapezoidal function (with an extension and operator)
 */
trapezoidal_function_extended *to_fext_lower_equal(trapezoidal_function *ft, float8 *ext) {
    return to_fext(ft, ext, "*<=");
};

/**
 * Defuzzifies a value with respect to an operator and threshold (extension)
 * @param degree numeric value describing a value
 * @param op operator
 * @param threshold numeric value describing a threshold
 * @return Defuzzified degree
 */
bool defuzzy(float8 degree, char op[4], float8 threshold) {
    if (strcmp(op, "*=") == 0) {
        return degree == threshold;
    }
    if (op == "*<>") {
        return degree != threshold;
    }
    if (strcmp(op, "*<") == 0) {
        return degree < threshold;
    }
    if (strcmp(op, "*<=") == 0) {
        return degree <= threshold;
    }
    if (strcmp(op, "*>") == 0) {
        return degree > threshold;
    }
    if (strcmp(op, "*>=") == 0) {
        return degree >= threshold;
    }

    return true;
}

/**
 * Defuzzifies a numeric value passed to an extended trapezoidal function
 * @param fext pointer to extended trapezoidal function
 * @param data pointer to numeric value
 * @return Defuzzified numeric value
 */
bool defuzzy_fext_r(trapezoidal_function_extended *fext, float8 *data) {
    if (fext == NULL || data == NULL) {
        return false;
    }
    return defuzzy(degree(*data, fext->f), fext->op, fext->ext);
}

/**
 * Defuzzifies a numeric value passed to an extended trapezoidal function and negates it
 * @param fext pointer to extended trapezoidal function
 * @param data pointer to numeric value
 * @return Defuzzified numeric value
 */
bool not_defuzzy_fext_r(trapezoidal_function_extended *fext, float8 *data) {
    if (fext == NULL || data == NULL) {
        return false;
    }
    return !defuzzy_fext_r(fext, data);
}

/**
 * Defuzzifies a numeric value passed to an extended trapezoidal function
 * @param data pointer to numeric value
 * @param fext pointer to extended trapezoidal function
 * @return Defuzzified numeric value
 */
bool defuzzy_r_fext(float8 *data, trapezoidal_function_extended *fext) {
    return defuzzy_fext_r(fext, data);
}

/**
 * Defuzzifies a numeric value passed to an extended trapezoidal function and negates it
 * @param data pointer to numeric value
 * @param fext pointer to extended trapezoidal function
 * @return Defuzzified numeric value
 */
bool not_defuzzy_r_fext(float8 *data, trapezoidal_function_extended *fext) {
    return not_defuzzy_fext_r(data, fext);
}

/**
 * Defuzzifies a trapezoidal function value passed to an extended trapezoidal function
 * @param fext pointer to extended trapezoidal function
 * @param ft pointer to trapezoidal function
 * @return Defuzzified trapezoidal function value
 */
bool defuzzy_fext_ft(trapezoidal_function_extended *fext, trapezoidal_function *ft) {
    if (fext == NULL || ft == NULL) {
        return false;
    }
    return defuzzy(degreeftofft(fext->f, *ft), fext->op, fext->ext);
}

/**
 * Defuzzifies a trapezoidal function value passed to an extended trapezoidal function and negates it
 * @param fext pointer to extended trapezoidal function
 * @param ft pointer to trapezoidal function
 * @return Defuzzified trapezoidal function value
 */
bool not_defuzzy_fext_ft(trapezoidal_function_extended *fext, trapezoidal_function *ft) {
    if (fext == NULL || ft == NULL) {
        return false;
    }
    return !defuzzy_fext_ft(fext, ft);
}

/**
 * Defuzzifies a trapezoidal function value passed to an extended trapezoidal function
 * @param ft pointer to trapezoidal function
 * @param fext pointer to extended trapezoidal function
 * @return Defuzzified trapezoidal function value
 */
bool defuzzy_ft_fext(trapezoidal_function *ft, trapezoidal_function_extended *fext) {
    return defuzzy_fext_ft(fext, ft);
}

/**
 * Defuzzifies a trapezoidal function value passed to an extended trapezoidal function and negates it
 * @param ft pointer to trapezoidal function
 * @param fext pointer to extended trapezoidal function
 * @return Defuzzified trapezoidal function value
 */
bool not_defuzzy_ft_fext(trapezoidal_function *ft, trapezoidal_function_extended *fext) {
    return not_defuzzy_fext_ft(fext, ft);
}

/*
 * Linguistic values
 */
