#ifndef UTILS_H
#define UTILS_H

#include "postgres.h"

text *to_text(char *s);
int charpos(char *source, char ch);
float max4(float a, float b, float c, float d);

text *to_text(char *s) {
    text *result = (text *) palloc(VARHDRSZ + strlen(s));
    SET_VARSIZE(result, VARHDRSZ + strlen(s));
    memcpy(result->vl_dat, s, strlen(s));
    return result;
}

/**
 * Finds position of a character in string
 * @param source string
 * @param ch character
 * @return position of a character in string, -1 if not found
 */
int charpos(char *source, char ch) {
    int i;
    for (i = 0; i < strlen(source); i++) {
        if (source[i] == ch) {
            return i;
        }
    }
    return -1;
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

#endif
