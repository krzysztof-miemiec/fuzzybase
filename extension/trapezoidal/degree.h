#ifndef DEGREE_H
#define DEGREE_H

#include "postgres.h"
#include "../general/utils.h"
#include "../general/extension.h"
#include "function.h"

float8 degree(float8 x, trapezoidal_function f);

float8 degreerf(float8 x, trapezoidal_function *f);

float8 degreefr(trapezoidal_function *f, float8 x);

float8 e(float8 xD1, float8 xG1, float8 xD2, float8 xG2);

float8 degreeftofft(trapezoidal_function x, trapezoidal_function y);

float8 degreeff(trapezoidal_function *x, trapezoidal_function *y);

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
float8 degreerf(float8 x, trapezoidal_function *f) {
    if (f == NULL) {
        return 0;
    }
    return degree(x, *f);
};

PG_FUNC_2(degreerf, float8, FLOAT8, float8, FLOAT8, trapezoidal_function*, POINTER);

/**
 * Calculates the degree of membership of value x to function f
 * @param f pointer to a trapezoidal function
 * @param x pointer to a numeric value
 * @return pointer to a numeric value, with overridden value of the degree of membership of value x to function f
 */
float8 degreefr(trapezoidal_function *f, float8 x) {
    if (f == NULL) {
        return 0;
    }
    return degree(x, *f);
};

PG_FUNC_2(degreefr, float8, FLOAT8, trapezoidal_function*, POINTER, float8, FLOAT8);

/**
 * Calculates the degree of membership basing on edges of two trapezoidal functions
 * @param xD1 edge point of first trapezoidal function
 * @param xG1 edge point of first trapezoidal function
 * @param xD2 edge point of second trapezoidal function
 * @param xG2 edge point of second trapezoidal function
 * @return the (partial result) degree of membership of trapezoidal function
 */
float8 e(float8 xD1, float8 xG1, float8 xD2, float8 xG2) {
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
float8 degreeff(trapezoidal_function *x, trapezoidal_function *y) {
    if (x == NULL || y == NULL) {
        return 0;
    }

    return degreeftofft(*x, *y);
}

PG_FUNC_2(degreeff, float8, FLOAT8, trapezoidal_function*, POINTER, trapezoidal_function*, POINTER);

#endif
