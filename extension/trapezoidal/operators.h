#ifndef TRAPEZOIDAL_OPERATORS_H
#define TRAPEZOIDAL_OPERATORS_H

#include "../general/extension.h"
#include "function.h"

trapezoidal_function *minus_f(trapezoidal_function *f);

trapezoidal_function *f_sum_r(trapezoidal_function *f, float8 r);

trapezoidal_function *r_sum_f(float8 r, trapezoidal_function *f);

trapezoidal_function *f_sub_r(trapezoidal_function *f, float8 r);

trapezoidal_function *r_sub_f(float8 r, trapezoidal_function *f);

trapezoidal_function *f_sum_f(trapezoidal_function *x, trapezoidal_function *y);

trapezoidal_function *f_sub_f(trapezoidal_function *x, trapezoidal_function *y);

trapezoidal_function *f_mul_r(trapezoidal_function *f, float8 r);

trapezoidal_function *r_mul_f(float8 r, trapezoidal_function *f);

trapezoidal_function *f_div_r(trapezoidal_function *f, float8 r);

trapezoidal_function *r_div_f(float8 r, trapezoidal_function *f);

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
    if (f == NULL) {
        return NULL;
    }
    trapezoidal_function *result = new_trapezoidal_function();

    result->m = -(f->m + f->dm);
    result->dm = f->dm;
    result->a = f->b;
    result->b = f->a;

    return result;
}

PG_FUNC_1(minus_f, trapezoidal_function*, POINTER, trapezoidal_function*, POINTER);

/**
 * Adds a number to a trapezoidal function
 *
 * @param f trapezoidal function pointer
 * @param r number pointer
 * @return f+r
 */
trapezoidal_function *f_sum_r(trapezoidal_function *f, float8 r) {
    if (f == NULL) {
        return NULL;
    }
    trapezoidal_function *result = new_trapezoidal_function();
    trapezoidal_function_assign(f, result);
    result->m += r;
    return result;
}

PG_FUNC_2_POINTER(f_sum_r, trapezoidal_function*, POINTER, float8, FLOAT8);

/**
 * Adds a trapezoidal function to a number
 *
 * @param r number pointer
 * @param f trapezoidal function pointer
 * @return r+f
 */
trapezoidal_function *r_sum_f(float8 r, trapezoidal_function *f) {
    return f_sum_r(f, r);
};

PG_FUNC_2_POINTER(r_sum_f, float8, FLOAT8, trapezoidal_function*, POINTER);

/**
 * Subtracts a number from a trapezoidal function
 *
 * @param r number pointer
 * @param f trapezoidal function pointer
 * @return f-r
 */
trapezoidal_function *f_sub_r(trapezoidal_function *f, float8 r) {
    if (f == NULL) {
        return NULL;
    }
    trapezoidal_function *result = new_trapezoidal_function();
    trapezoidal_function_assign(f, result);
    result->m -= r;
    return result;
};

PG_FUNC_2_POINTER(f_sub_r, trapezoidal_function*, POINTER, float8, FLOAT8);

/**
 * Subtracts a trapezoidal function from a number
 *
 * @param f trapezoidal function pointer
 * @param r number pointer
 * @return r-f
 */
trapezoidal_function *r_sub_f(float8 r, trapezoidal_function *f) {
    return minus_f(f_sub_r(f, r));
}

PG_FUNC_2_POINTER(r_sub_f, float8, FLOAT8, trapezoidal_function*, POINTER);

/**
 * Sums two trapezoidal functions
 * @param x left-hand side function
 * @param y right-hand side function
 * @return x=x+y
 */
trapezoidal_function *f_sum_f(trapezoidal_function *x, trapezoidal_function *y) {
    if (x == NULL || y == NULL) {
        return NULL;
    }
    trapezoidal_function *result = new_trapezoidal_function();

    result->a = x->a + y->a;
    result->m = x->m + y->m;
    result->dm = x->dm + y->dm;
    result->b = x->b + y->b;

    return result;
}

PG_FUNC_2_POINTER(f_sum_f, trapezoidal_function*, POINTER, trapezoidal_function*, POINTER);

/**
 * Subtracts trapezoidal function from other trapezoidal function
 * @param x left-hand side function
 * @param y right-hand side function
 * @return x-y
 */
trapezoidal_function *f_sub_f(trapezoidal_function *x, trapezoidal_function *y) {
    if (x == NULL || y == NULL) {
        return NULL;
    }
    trapezoidal_function *result = new_trapezoidal_function();

    result->a = x->a - y->a;
    result->m = x->m - y->m;
    result->dm = x->dm - y->dm;
    result->b = x->b - y->b;

    return result;
}

PG_FUNC_2_POINTER(f_sub_f, trapezoidal_function*, POINTER, trapezoidal_function*, POINTER);

/**
 * Multiplies trapezoidal function by a number
 * @param f left-hand side function
 * @param r right-hand side number
 * @return f*r
 */
trapezoidal_function *f_mul_r(trapezoidal_function *f, float8 r) {
    if (f == NULL) {
        return NULL;
    }
    trapezoidal_function *result = new_trapezoidal_function();

    result->a = f->a * r;
    result->m = f->m * r;
    result->dm = f->dm * r;
    result->b = f->b * r;

    return result;
}

PG_FUNC_2_POINTER(f_mul_r, trapezoidal_function*, POINTER, float8, FLOAT8);

/**
 * Multiplies trapezoidal function by a number
 * @param r left-hand side number
 * @param f right-hand side function
 * @return r*f
 */
trapezoidal_function *r_mul_f(float8 r, trapezoidal_function *f) {
    return f_mul_r(f, r);
}

PG_FUNC_2_POINTER(r_mul_f, float8, FLOAT8, trapezoidal_function*, POINTER);

/**
 * Divides trapezoidal function by a number
 * @param f left-hand side function
 * @param r right-hand side number
 * @return f*r
 */
trapezoidal_function *f_div_r(trapezoidal_function *f, float8 r) {
    if (f == NULL || r == 0) {
        return NULL;
    }
    trapezoidal_function *result = new_trapezoidal_function();

    result->a = f->a / r;
    result->m = f->m / r;
    result->dm = f->dm / r;
    result->b = f->b / r;

    return result;
}

PG_FUNC_2_POINTER(f_div_r, trapezoidal_function*, POINTER, float8, FLOAT8);

/**
 * Divides a number by trapezoidal function
 * @param r left-hand side number
 * @param f right-hand side function
 * @return f*r
 */
trapezoidal_function *r_div_f(float8 r, trapezoidal_function *f) {
    if (f == NULL || f->a == 0 || f->m == 0 || f->dm == 0 || f->b == 0) {
        return NULL;
    }
    trapezoidal_function *result = new_trapezoidal_function();

    result->a = r / f->a;
    result->m = r / f->m;
    result->dm = r / f->dm;
    result->b = r / f->b;

    return result;
}

PG_FUNC_2_POINTER(r_div_f, float8, FLOAT8, trapezoidal_function*, POINTER);


/**
 * Multiplies trapezoidal function by another function
 * @param a left-hand side function
 * @param b right-hand side function
 * @return a*b
 */
trapezoidal_function *f_mul_f(trapezoidal_function *a, trapezoidal_function *b) {
    if (a == NULL || b == NULL) {
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

PG_FUNC_2_POINTER(f_mul_f, trapezoidal_function*, POINTER, trapezoidal_function*, POINTER);

/**
 * Divides trapezoidal function by another function
 * @param a left-hand side function
 * @param b right-hand side function
 * @return a/b
 */
trapezoidal_function *f_div_f(trapezoidal_function *a, trapezoidal_function *b) {
    if (a == NULL || b == NULL) {
        return NULL;
    }

    float8 al, an, ao, bl, bn, bo;

    al = a->m - a->a;
    an = a->m + a->dm;
    ao = an + a->b;

    bl = b->m - b->a;
    bn = b->m + b->dm;
    bo = bn + b->b;

    if (bl == 0 || b->m == 0 || bn == 0 || bo == 0) {
        return NULL;
    }

    trapezoidal_function *f = new_trapezoidal_function();

    f->m = a->m / b->m;
    f->a = f->m - (al / bl);
    f->dm = (an / bn) - f->m;
    f->b = (ao / bo) - f->dm;

    return f;
}

PG_FUNC_2_POINTER(f_div_f, trapezoidal_function*, POINTER, trapezoidal_function*, POINTER);

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

PG_FUNC_2_POINTER(trapezoidal_function_min, trapezoidal_function*, POINTER, trapezoidal_function*, POINTER);

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

PG_FUNC_2_POINTER(trapezoidal_function_max, trapezoidal_function*, POINTER, trapezoidal_function*, POINTER);

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

PG_FUNC_2(is_equal, bool, BOOL, trapezoidal_function*, POINTER, trapezoidal_function*, POINTER);

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

PG_FUNC_2(is_lower, bool, BOOL, trapezoidal_function*, POINTER, trapezoidal_function*, POINTER);

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

PG_FUNC_2(is_greater, bool, BOOL, trapezoidal_function*, POINTER, trapezoidal_function*, POINTER);

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

PG_FUNC_2(is_greater_equal, bool, BOOL, trapezoidal_function*, POINTER, trapezoidal_function*, POINTER);

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

PG_FUNC_2(is_lower_equal, bool, BOOL, trapezoidal_function*, POINTER, trapezoidal_function*, POINTER);

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

PG_FUNC_2(not_equal, bool, BOOL, trapezoidal_function*, POINTER, trapezoidal_function*, POINTER);

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

PG_FUNC_2(trapezoidal_function_abs_cmp, int, INT16, trapezoidal_function*, POINTER, trapezoidal_function*, POINTER);

#endif
