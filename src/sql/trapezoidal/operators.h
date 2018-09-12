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

PG_FUNCTION_INFO_V1(pg_minus_f);

Datum pg_minus_f(PG_FUNCTION_ARGS) {
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(0);
    trapezoidal_function *result = minus_f(f);
    PG_RETURN_POINTER(result);
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

PG_FUNCTION_INFO_V1(pg_f_sum_r);

Datum pg_f_sum_r(PG_FUNCTION_ARGS) {
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(0);
    float8 *r = (float8 *) PG_GETARG_POINTER(1);
    trapezoidal_function *result = f_sum_r(f, r);
    PG_RETURN_POINTER(result);
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

PG_FUNCTION_INFO_V1(pg_r_sum_f);

Datum pg_r_sum_f(PG_FUNCTION_ARGS) {
    float8 *r = (float8 *) PG_GETARG_POINTER(0);
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(1);
    trapezoidal_function *result = r_sum_f(r, f);
    PG_RETURN_POINTER(result);
}

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

PG_FUNCTION_INFO_V1(pg_f_sub_r);

Datum pg_f_sub_r(PG_FUNCTION_ARGS) {
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(0);
    float8 *r = (float8 *) PG_GETARG_POINTER(1);
    trapezoidal_function *result = f_sub_r(f, r);
    PG_RETURN_POINTER(result);
}

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

PG_FUNCTION_INFO_V1(pg_r_sub_f);

Datum pg_r_sub_f(PG_FUNCTION_ARGS) {
    float8 *r = (float8 *) PG_GETARG_POINTER(0);
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(1);
    trapezoidal_function *result = r_sub_f(r, f);
    PG_RETURN_POINTER(result);
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

PG_FUNCTION_INFO_V1(pg_f_sum_f);

Datum pg_f_sum_f(PG_FUNCTION_ARGS) {
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(0);
    trapezoidal_function *f2 = (trapezoidal_function *) PG_GETARG_POINTER(1);
    trapezoidal_function *result = f_sum_f(f, f2);
    PG_RETURN_POINTER(result);
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

PG_FUNCTION_INFO_V1(pg_f_sub_f);

Datum pg_f_sub_f(PG_FUNCTION_ARGS) {
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(0);
    trapezoidal_function *f2 = (trapezoidal_function *) PG_GETARG_POINTER(1);
    trapezoidal_function *result = f_sub_f(f, f2);
    PG_RETURN_POINTER(result);
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

    f->a *= *r;
    f->m *= *r;
    f->dm *= *r;
    f->b *= *r;

    return f;
}

PG_FUNCTION_INFO_V1(pg_f_mul_r);

Datum pg_f_mul_r(PG_FUNCTION_ARGS) {
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(0);
    float8 *r = (float8 *) PG_GETARG_POINTER(1);
    trapezoidal_function *result = f_mul_r(f, r);
    PG_RETURN_POINTER(result);
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

PG_FUNCTION_INFO_V1(pg_r_mul_f);

Datum pg_r_mul_f(PG_FUNCTION_ARGS) {
    float8 *r = (float8 *) PG_GETARG_POINTER(0);
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(1);
    trapezoidal_function *result = r_mul_f(r, f);
    PG_RETURN_POINTER(result);
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

PG_FUNCTION_INFO_V1(pg_f_div_r);

Datum pg_f_div_r(PG_FUNCTION_ARGS) {
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(0);
    float8 *r = (float8 *) PG_GETARG_POINTER(1);
    trapezoidal_function *result = f_div_r(f, r);
    PG_RETURN_POINTER(result);
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

PG_FUNCTION_INFO_V1(pg_r_div_f);

Datum pg_r_div_f(PG_FUNCTION_ARGS) {
    float8 *r = (float8 *) PG_GETARG_POINTER(0);
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(1);
    trapezoidal_function *result = r_div_f(r, f);
    PG_RETURN_POINTER(result);
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

PG_FUNCTION_INFO_V1(pg_f_mul_f);

Datum pg_f_mul_f(PG_FUNCTION_ARGS) {
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(0);
    trapezoidal_function *f2 = (trapezoidal_function *) PG_GETARG_POINTER(1);
    trapezoidal_function *result = f_mul_f(f, f2);
    PG_RETURN_POINTER(result);
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

PG_FUNCTION_INFO_V1(pg_f_div_f);

Datum pg_f_div_f(PG_FUNCTION_ARGS) {
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(0);
    trapezoidal_function *f2 = (trapezoidal_function *) PG_GETARG_POINTER(1);
    trapezoidal_function *result = f_div_f(f, f2);
    PG_RETURN_POINTER(result);
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

PG_FUNCTION_INFO_V1(pg_trapezoidal_function_min);

Datum pg_trapezoidal_function_min(PG_FUNCTION_ARGS) {
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(0);
    trapezoidal_function *f2 = (trapezoidal_function *) PG_GETARG_POINTER(1);
    trapezoidal_function *result = trapezoidal_function_min(f, f2);
    PG_RETURN_POINTER(result);
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

PG_FUNCTION_INFO_V1(pg_trapezoidal_function_max);

Datum pg_trapezoidal_function_max(PG_FUNCTION_ARGS) {
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(0);
    trapezoidal_function *f2 = (trapezoidal_function *) PG_GETARG_POINTER(1);
    trapezoidal_function *result = trapezoidal_function_max(f, f2);
    PG_RETURN_POINTER(result);
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

PG_FUNCTION_INFO_V1(pg_is_equal);

Datum pg_is_equal(PG_FUNCTION_ARGS) {
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(0);
    trapezoidal_function *f2 = (trapezoidal_function *) PG_GETARG_POINTER(1);
    bool result = is_equal(f, f2);
    PG_RETURN_BOOL(result);
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

PG_FUNCTION_INFO_V1(pg_is_lower);

Datum pg_is_lower(PG_FUNCTION_ARGS) {
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(0);
    trapezoidal_function *f2 = (trapezoidal_function *) PG_GETARG_POINTER(1);
    bool result = is_lower(f, f2);
    PG_RETURN_BOOL(result);
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

PG_FUNCTION_INFO_V1(pg_is_greater);

Datum pg_is_greater(PG_FUNCTION_ARGS) {
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(0);
    trapezoidal_function *f2 = (trapezoidal_function *) PG_GETARG_POINTER(1);
    bool result = is_greater(f, f2);
    PG_RETURN_BOOL(result);
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

PG_FUNCTION_INFO_V1(pg_is_greater_equal);

Datum pg_is_greater_equal(PG_FUNCTION_ARGS) {
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(0);
    trapezoidal_function *f2 = (trapezoidal_function *) PG_GETARG_POINTER(1);
    bool result = is_greater_equal(f, f2);
    PG_RETURN_BOOL(result);
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

PG_FUNCTION_INFO_V1(pg_is_lower_equal);

Datum pg_is_lower_equal(PG_FUNCTION_ARGS) {
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(0);
    trapezoidal_function *f2 = (trapezoidal_function *) PG_GETARG_POINTER(1);
    bool result = is_lower_equal(f, f2);
    PG_RETURN_BOOL(result);
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

PG_FUNCTION_INFO_V1(pg_not_equal);

Datum pg_not_equal(PG_FUNCTION_ARGS) {
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(0);
    trapezoidal_function *f2 = (trapezoidal_function *) PG_GETARG_POINTER(1);
    bool result = not_equal(f, f2);
    PG_RETURN_BOOL(result);
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

PG_FUNCTION_INFO_V1(pg_trapezoidal_function_abs_cmp);

Datum pg_trapezoidal_function_abs_cmp(PG_FUNCTION_ARGS) {
    trapezoidal_function *f = (trapezoidal_function *) PG_GETARG_POINTER(0);
    trapezoidal_function *f2 = (trapezoidal_function *) PG_GETARG_POINTER(1);
    int result = trapezoidal_function_abs_cmp(f, f2);
    PG_RETURN_INT16(result);
}

#endif
