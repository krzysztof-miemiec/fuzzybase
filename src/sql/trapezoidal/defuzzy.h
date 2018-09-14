#ifndef DEFUZZY_H
#define DEFUZZY_H

#include "../general/extension.h"
#include "postgres.h"
#include "function.h"

bool defuzzy(float8 degree, char op[4], float8 threshold);

bool defuzzy_fext_r(trapezoidal_function_extended *fext, float8 *data);

bool not_defuzzy_fext_r(trapezoidal_function_extended *fext, float8 *data);

bool defuzzy_r_fext(float8 *data, trapezoidal_function_extended *fext);

bool not_defuzzy_r_fext(float8 *data, trapezoidal_function_extended *fext);

bool defuzzy_fext_ft(trapezoidal_function_extended *fext, trapezoidal_function *ft);

bool not_defuzzy_fext_ft(trapezoidal_function_extended *fext, trapezoidal_function *ft);

bool defuzzy_ft_fext(trapezoidal_function *ft, trapezoidal_function_extended *fext);

bool not_defuzzy_ft_fext(trapezoidal_function *ft, trapezoidal_function_extended *fext);


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
    if (strcmp(op, "*<>") == 0) {
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

PG_FUNC_2(defuzzy_fext_r, bool, BOOL, trapezoidal_function_extended*, POINTER, float8 *, POINTER);

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

PG_FUNC_2(not_defuzzy_fext_r, bool, BOOL, trapezoidal_function_extended*, POINTER, float8 *, POINTER);

/**
 * Defuzzifies a numeric value passed to an extended trapezoidal function
 * @param data pointer to numeric value
 * @param fext pointer to extended trapezoidal function
 * @return Defuzzified numeric value
 */
bool defuzzy_r_fext(float8 *data, trapezoidal_function_extended *fext) {
    return defuzzy_fext_r(fext, data);
}

PG_FUNC_2(defuzzy_r_fext, bool, BOOL, float8 *, POINTER, trapezoidal_function_extended*, POINTER);

/**
 * Defuzzifies a numeric value passed to an extended trapezoidal function and negates it
 * @param data pointer to numeric value
 * @param fext pointer to extended trapezoidal function
 * @return Defuzzified numeric value
 */
bool not_defuzzy_r_fext(float8 *data, trapezoidal_function_extended *fext) {
    return not_defuzzy_fext_r(fext, data);
}

PG_FUNC_2(not_defuzzy_r_fext, bool, BOOL, float8 *, POINTER, trapezoidal_function_extended*, POINTER);

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

PG_FUNC_2(defuzzy_fext_ft, bool, BOOL, trapezoidal_function_extended*, POINTER, trapezoidal_function*, POINTER);

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

PG_FUNC_2(not_defuzzy_fext_ft, bool, BOOL, trapezoidal_function_extended*, POINTER, trapezoidal_function*, POINTER);

/**
 * Defuzzifies a trapezoidal function value passed to an extended trapezoidal function
 * @param ft pointer to trapezoidal function
 * @param fext pointer to extended trapezoidal function
 * @return Defuzzified trapezoidal function value
 */
bool defuzzy_ft_fext(trapezoidal_function *ft, trapezoidal_function_extended *fext) {
    return defuzzy_fext_ft(fext, ft);
}

PG_FUNC_2(defuzzy_ft_fext, bool, BOOL, trapezoidal_function*, POINTER, trapezoidal_function_extended*, POINTER);

/**
 * Defuzzifies a trapezoidal function value passed to an extended trapezoidal function and negates it
 * @param ft pointer to trapezoidal function
 * @param fext pointer to extended trapezoidal function
 * @return Defuzzified trapezoidal function value
 */
bool not_defuzzy_ft_fext(trapezoidal_function *ft, trapezoidal_function_extended *fext) {
    return not_defuzzy_fext_ft(fext, ft);
}

PG_FUNC_2(not_defuzzy_ft_fext, bool, BOOL, trapezoidal_function*, POINTER, trapezoidal_function_extended*, POINTER);

#endif