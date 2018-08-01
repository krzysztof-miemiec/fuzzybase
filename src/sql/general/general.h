#ifndef GENERAL_H
#define GENERAL_H

// Prototypes
typedef struct {
    int8 bool_count, count;
} twoint;

float8 *min(float8 *x, float8 *y);

float8 *max(float8 *x, float8 *y);

float8 *neg_dm(float8 *x);

twoint *twoint_from_string(char *str);

char *twoint_to_string(twoint *t);

twoint *percentage_sfunc(twoint *state, bool next_data);

float8 *percentage_final_func(twoint *last_state);

#endif
