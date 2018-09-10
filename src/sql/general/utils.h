#ifndef UTILS_H
#define UTILS_H

#include "postgres.h"

text *to_text(char *s);

int charpos(char *source, char ch);

float max4(float a, float b, float c, float d);

#endif
