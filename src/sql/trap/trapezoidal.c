#include "postgres.h"
#include <stdlib.h>

#include "../general/general.h"

text *toText(char *s) {
    text *result = (text *) palloc(VARHDRSZ + strlen(s));
    result->vl_len = VARHDRSZ + strlen(s);
    memcpy(result->vl_dat, s, strlen(s));
    return result;
}

//*****************definicja typu trapezoidal_function***********************

typedef struct {
    float8 a, m, dm, b;
} trapezoidal_function;

//**************definicja typu trapezoidal_function_extended*********************

typedef struct {
    float8 ext;
    trapezoidal_function f;
    char op[4];
} trapezoidal_function_extended;


void trapezoidal_function_clear(trapezoidal_function *f) {
    f->a = 0;
    f->m = 0;
    f->dm = 0;
    f->b = 0;
}

void trapezoidal_function_assign(trapezoidal_function *s, trapezoidal_function *d) {
    if (s == NULL)
        d = NULL;
    else {
        d->a = s->a;
        d->m = s->m;
        d->dm = s->dm;
        d->b = s->b;
    }
}

//*******************funkcje wykorzystywane przez funkcje trapezoidal_function_in************** 

int charpos(char *source, char ch) {
    int i;
    for (i = 0; i < strlen(source); i++)
        if (source[i] == ch) {
            return i;
        }
    return -1;
};

trapezoidal_function *trapezoidal_function_in(char *str) {
    float8 l, m, n, o;
    trapezoidal_function *result = (trapezoidal_function *) palloc(sizeof(trapezoidal_function));

    bool existsL = charpos(str, '/') >= 0;
    bool existsN = charpos(str, '~') >= 0;
    bool existsO = charpos(str, '\\') >= 0;

    if (existsL) {
        // zeskanuj i ukroc poczatek az do / wlacznie
        sscanf(str, "%lf", &l);
        strcpy(str, str + charpos(str, '/') + 1);
    };

    // zeskanuj m i jesli nie bylo l to l = m
    sscanf(str, "%lf", &m);

    if (!existsL)
        l = m;

    if (existsN) {
        strcpy(str, str + charpos(str, '~') + 1);
        // zeskanuj i ukroc poczatek az do / wlacznie
        sscanf(str, "%lf", &n);
    } else
        n = m;

    if (existsO) {
        strcpy(str, str + charpos(str, '\\') + 1);
        // zeskanuj i ukroc poczatek az do / wlacznie
        sscanf(str, "%lf", &o);
    } else
        o = n;

    result->a = m - l;
    result->m = m;
    result->dm = n - m;
    result->b = o - n;

    return (result);
}

//**********************funkcja wyjsciowa dla typu trapezoidal_function*****************************

char *trapezoidal_function_out(trapezoidal_function *f) {
    char *result = (char *) palloc(512);
    char result_cz[512];

    strcpy(result, "");
    strcpy(result_cz, "");

    // parametry
    if (f->a != 0) {
        sprintf(result_cz, "%.2f/", (f->m) - (f->a));
        strcat(result, result_cz);
    };
    sprintf(result_cz, "%.2f", f->m);
    strcat(result, result_cz);
    if (f->dm != 0) {
        sprintf(result_cz, "~%.2f", ((f->m) + (f->dm)));
        strcat(result, result_cz);
    };
    if (f->b != 0) {
        sprintf(result_cz, "\\%.2f", ((f->m) + (f->dm) + (f->b)));
        strcat(result, result_cz);
    };

    return (result);
}

//***************poczatek funkcji definiujacych wyrazy rozmyte*******************

trapezoidal_function *about_r(float8 l, float8 m, float8 n, float8 o) {
    trapezoidal_function *f = (trapezoidal_function *) palloc(sizeof(trapezoidal_function));

    f->a = m - l;
    f->m = m;
    f->dm = n - m;
    f->b = o - n;

    return f;
}

trapezoidal_function *about(float8 *l, float8 *m, float8 *n, float8 *o) {
    return about_r(*l, *m, *n, *o);
}



//****************************operacje arytmetyczne na liczbach rozmytych******************

trapezoidal_function *minus_f(trapezoidal_function *f) {

    float8 b2 = 0;

    if (f == NULL)
        return NULL;

    b2 = f->a;
    f->m = -(f->m + f->dm);
    f->dm = f->dm;
    f->a = f->b;
    f->b = b2;

    return f;
}

trapezoidal_function *f_sum_r(trapezoidal_function *f, float8 *r) {

    if ((f == NULL) || (r == NULL))
        return NULL;

    f->m += *r;
    return f;
}

trapezoidal_function *r_sum_f(float8 *r, trapezoidal_function *f) {
    if ((f == NULL) || (r == NULL))
        return NULL;

    return f_sum_r(f, r);
};

trapezoidal_function *f_sub_r(trapezoidal_function *f, float8 *r) {
    if ((f == NULL) || (r == NULL))
        return NULL;

    f->m -= *r;
    return f;
};

trapezoidal_function *r_sub_f(float8 *r, trapezoidal_function *f) {
    if ((f == NULL) || (r == NULL))
        return NULL;

    return minus_f(f_sub_r(f, r));
}

trapezoidal_function *f_sum_f(trapezoidal_function *x, trapezoidal_function *y) {
    if ((x == NULL) || (y == NULL))
        return NULL;

    x->a += y->a;
    x->m += y->m;
    x->dm += y->dm;
    x->b += y->b;

    return x;
}

trapezoidal_function *f_sub_f(trapezoidal_function *x, trapezoidal_function *y) {
    if ((x == NULL) || (y == NULL))
        return NULL;

    x->a -= y->a;
    x->m -= y->m;
    x->dm -= y->dm;
    x->b -= y->b;

    return x;
}

trapezoidal_function *f_mul_r(trapezoidal_function *f, float8 *r) {
    if ((f == NULL) || (r == NULL))
        return NULL;

    f->a * = *r;
    f->m * = *r;
    f->dm * = *r;
    f->b * = *r;

    return f;
}

trapezoidal_function *r_mul_f(float8 *r, trapezoidal_function *f) {
    if ((f == NULL) || (r == NULL))
        return NULL;
    return f_mul_r(f, r);
}

trapezoidal_function *f_div_r(trapezoidal_function *f, float8 *r) {
    if ((f == NULL) || (r == NULL) || (r == 0))
        return NULL;

    f->a /= *r;
    f->m /= *r;
    f->dm /= *r;
    f->b /= *r;

    return f;
}

trapezoidal_function *r_div_f(float8 *r, trapezoidal_function *f) {
    if ((f == NULL) || (r == NULL) || (r == 0))
        return NULL;

    f->a = *r / f->a;
    f->m = *r / f->m;
    f->dm = *r / f->dm;
    f->b = *r / f->b;

    return f;
}


trapezoidal_function *f_mul_f(trapezoidal_function *a, trapezoidal_function *b) {
    trapezoidal_function *f = NULL;

    float8 al, an, ao, bl, bn, bo;

    if ((a == NULL) || (b == NULL))
        return NULL;

    f = (trapezoidal_function *) palloc(sizeof(trapezoidal_function));

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

trapezoidal_function *f_div_f(trapezoidal_function *a, trapezoidal_function *b) {
    trapezoidal_function *f = NULL;

    float8 al, an, ao, bl, bn, bo;

    al = a->m - a->a;
    an = a->m + a->dm;
    ao = an + a->b;

    bl = b->m - b->a;
    bn = b->m + b->dm;
    bo = bn + b->b;

    if ((a == NULL) || (b == NULL) || (bl == 0) || (b->m == 0) || (bn == 0) || (bo == 0))
        return NULL;

    f = (trapezoidal_function *) palloc(sizeof(trapezoidal_function));


    f->m = a->m / b->m;
    f->a = f->m - (al / bl);
    f->dm = (an / bn) - f->m;
    f->b = (ao / bo) - f->dm;

    return f;
}

//********************** funkcje obliczajace wieksza i mniejsza z wartosci trapezoidal_function***********

trapezoidal_function *trapezoidal_functionmin(trapezoidal_function *f1, trapezoidal_function *f2) {
    if ((f1 == NULL) || (f2 == NULL))
        return NULL;

    if (f1->m < f2->m)
        return f1;
    else
        return f2;
}

trapezoidal_function *trapezoidal_functionmax(trapezoidal_function *f1, trapezoidal_function *f2) {
    if ((f1 == NULL) || (f2 == NULL))
        return NULL;
    if (f1->m > f2->m)
        return f1;
    else
        return f2;
}

trapezoidal_function *trapezoidal_function_extended_to_trapezoidal_function(trapezoidal_function_extended *last_state) {
    if (last_state == NULL)
        return NULL;
    return &(last_state->f);
};

trapezoidal_function_extended *statemax(trapezoidal_function_extended *state, trapezoidal_function *next_data) {
    if ((state == NULL) || (next_data == NULL))
        return NULL;

    if (state->ext == 0) {
        state->ext++;
        assigntrapezoidal_function(next_data, &(state->f));
        return state;
    };
    assigntrapezoidal_function(trapezoidal_functionmax(&(state->f), next_data), &(state->f));

    return state;
};

trapezoidal_function_extended *statemin(trapezoidal_function_extended *state, trapezoidal_function *next_data) {
    if ((state == NULL) || (next_data == NULL))
        return NULL;

    if (state->ext == 0) {
        state->ext++;
        assigntrapezoidal_function(next_data, &(state->f));
        return state;
    };
    assigntrapezoidal_function(trapezoidal_functionmin(&(state->f), next_data), &(state->f));

    return state;
};

//*************************porownania logiczne elementow rozmytych (frazy order i group by)*****


bool is_equal(trapezoidal_function *ft1, trapezoidal_function *ft2) {
    if ((ft1 == NULL) || (ft2 == NULL))
        return false;
    return (ft1->a == ft2->a) && (ft1->m == ft2->m) && (ft1->dm == ft2->dm) && (ft1->b == ft2->b);
}

bool is_lower(trapezoidal_function *ft1, trapezoidal_function *ft2) {
    if ((ft1 == NULL) || (ft2 == NULL))
        return false;

    return (ft1->m < ft2->m);
}

bool is_greater(trapezoidal_function *ft1, trapezoidal_function *ft2) {
    if ((ft1 == NULL) || (ft2 == NULL))
        return false;

    return (ft1->m + ft1->dm > ft2->m + ft2->dm);
}

bool is_greater_equal(trapezoidal_function *ft1, trapezoidal_function *ft2) {
    if ((ft1 == NULL) || (ft2 == NULL))
        return false;
    return (is_greater(ft1, ft2) || is_equal(ft1, ft2));
}

bool is_lower_equal(trapezoidal_function *ft1, trapezoidal_function *ft2) {
    if ((ft1 == NULL) || (ft2 == NULL))
        return false;
    return (is_lower(ft1, ft2) || is_equal(ft1, ft2));
}

bool not_equal(trapezoidal_function *ft1, trapezoidal_function *ft2) {
    if ((ft1 == NULL) || (ft2 == NULL))
        return false;
    return (ft1->a != ft2->a) || (ft1->m != ft2->m) || (ft1->dm != ft2->dm) || (ft1->b != ft2->b);
}

//  trapezoidal_functionorzona  na potrzeby indeksu btree na typie trapezoidal_function
int trapezoidal_function_abs_cmp(trapezoidal_function *a, trapezoidal_function *b) {
    \
  if (is_lower(a, b))
        return -1;
    if (is_greater(a, b))
        return 1;
    return 0;

}

//*****************stopien przynaleznosci podanej wartosci rzeczywistej do zbioru rozmytego**************

float8 degree(float8 x, trapezoidal_function f) {

    float8 l = f.m - f.a;
    float8 m = f.m;
    float8 n = f.m + f.dm;
    float8 o = f.m + f.dm + f.b;

    if ((x >= m) && (x <= n))
        return 1;

    if ((x > l) && (x < m))
        return ((x - l) / (m - l));

    if ((x > n) && (x < o))
        return ((o - x) / (o - n));

    if ((x <= l) || (x >= o))
        return 0;

};


// funkcje o parametrach - porownywanie wyrazu rozmytego z wartoscia rzeczywista

float8 *degreerf(float8 *r, trapezoidal_function *f) {
    float8 *result;

    if ((r == NULL) || (f == NULL))
        return NULL;

    result = (float8 *) palloc(sizeof(float8));
    // r posluzy tutaj jako rezultat
    *result = degree(*r, *f);
    return result;
};

float8 *degreefr(trapezoidal_function *f, float8 *r) {
    if ((r == NULL) || (f == NULL))
        return NULL;

    // r posluzy tutaj jako rezultat
    *r = degree(*r, *f);
    return r;
};



//*************funkcje wykorzystywane przez funkcje porownujaca dwa elenety rozmyte**************

float max4(float a, float b, float c, float d) {
    if (a < b)
        a = b;
    if (a < c)
        a = c;
    if (a < d)
        a = d;
    return a;
};

float e(float xD1, float xG1, float xD2, float xG2) {
    if (((xD1 < xD2) && (xG1 > xG2)) || ((xD2 < xD1) && (xG2 > xG1)))
        return (xD1 - xD2) / ((xG2 - xD2) - (xG1 - xD1));
    else
        return 0;
};

//porownanie dwoch elementow trapezoidal_function

float8 degreeftofft(trapezoidal_function x, trapezoidal_function y) {

    if (((x.m <= y.m) && ((x.m + x.dm) >= y.m))
        || ((y.m <= x.m) && ((y.m + y.dm) >= x.m)))
        return 1;
    else
        return max4(
                e(x.m - x.a, x.m, y.m - y.a, y.m),
                e(x.m - x.a, x.m, y.m + y.dm + y.b, y.m + y.dm),
                e(x.m + x.dm + x.b, x.m + x.dm, y.m - y.a, y.m),
                e(x.m + x.dm + x.b, x.m + x.dm, y.m + y.dm + y.b, y.m + y.dm));
}

float8 *degreeotrapezoidal_function(trapezoidal_function *x, trapezoidal_function *y) {

    float8 *result;

    if ((x == NULL) || (y == NULL))
        return NULL;

    result = (float8 *) palloc(sizeof(float8));
    *result = degreeftofft(*x, *y);
    return result;
}



//*******************funkcje definiujace typ trapezoidal_function_extended*****************

trapezoidal_function_extended *trapezoidal_function_extended_in(char *str) {
    float8 ext;
    trapezoidal_function_extended *result = (trapezoidal_function_extended *) palloc(
            sizeof(trapezoidal_function_extended));
    trapezoidal_function *f = NULL;

    // zeskanuj wartosc ext
    sscanf(str, "%lf", &ext);
    strcpy(str, str + charpos(str, '|') + 1);

    f = trapezoidal_function_in(str);


    // przepisanie pomocniczych zmiennych lokalnych do resultu
    result->ext = ext;
    result->f.a = f->a;
    result->f.m = f->m;
    result->f.dm = f->dm;
    result->f.b = f->b;

    return (result);
}

char *trapezoidal_function_extended_out(trapezoidal_function_extended *x) {
    char *result = (char *) palloc(512);

    strcpy(result, "");

    // parametry
    if (x->f.a != 0)
        sprintf(result + strlen(result), "%.2f/", (x->f.m) - (x->f.a));

    // m jest wyswietlane zawsze
    sprintf(result + strlen(result), "%.2f", x->f.m);

    if (x->f.dm != 0)
        sprintf(result + strlen(result), "~%.2f", ((x->f.m) + (x->f.dm)));

    if (x->f.b != 0)
        sprintf(result + strlen(result), "\\%.2f", ((x->f.m) + (x->f.dm) + (x->f.b)));

    sprintf(result + strlen(result), " %s ", x->op);
    sprintf(result + strlen(result), "%.2f", x->ext);

    return (result);
}

//****************AVERAGE**********************************

//final function dla funkcji agregujacej average

trapezoidal_function *finalavg(trapezoidal_function_extended *x) {

    trapezoidal_function *result = NULL;

    if (x == NULL)
        return NULL;

    result = (trapezoidal_function *) palloc(sizeof(trapezoidal_function));

    result->a = x->f.a / x->ext;
    result->m = x->f.m / x->ext;
    result->dm = x->f.dm / x->ext;
    result->b = x->f.b / x->ext;

    return result;
}

//funkcja state dla funkcji agregujacej average

trapezoidal_function_extended *stateavg(trapezoidal_function_extended *state, trapezoidal_function *nextdate) {

    trapezoidal_function_extended *result = (trapezoidal_function_extended *) palloc(
            sizeof(trapezoidal_function_extended));

    result->ext = state->ext + 1;
    result->f.a = state->f.a + nextdate->a;
    result->f.m = state->f.m + nextdate->m;
    result->f.dm = state->f.dm + nextdate->dm;
    result->f.b = state->f.b + nextdate->b;

    return result;
}


//**************************************PODZAPYTANIA*****************************

// funkcja rozszerza typ trapezoidal_function o prog defuzzyfikacji

trapezoidal_function_extended *to_fext(trapezoidal_function *ft, float8 *ext, char
op[4]) {

    trapezoidal_function_extended *result = NULL;

    if ((ft == NULL) || (ext == NULL) || (op == NULL))
        return
                NULL;

    result = (trapezoidal_function_extended *) palloc(sizeof(trapezoidal_function_extended));

    result->
            ext = *ext;
    result->f.
            a = ft->a;
    result->f.
            m = ft->m;
    result->f.
            dm = ft->dm;
    result->f.
            b = ft->b;
    strncpy(result
                    ->op, op, 4);

    return
            result;
}

trapezoidal_function_extended *to_fext_equal(trapezoidal_function *ft, float8 *ext) {
    return to_fext(ft, ext, "*=");
};

trapezoidal_function_extended *to_fext_not_equal(trapezoidal_function *ft, float8 *ext) {
    return to_fext(ft, ext, "*<>");
};

trapezoidal_function_extended *to_fext_greater(trapezoidal_function *ft, float8 *ext) {
    return to_fext(ft, ext, "*>");
};

trapezoidal_function_extended *to_fext_greater_equal(trapezoidal_function *ft, float8 *ext) {
    return to_fext(ft, ext, "*>=");
};

trapezoidal_function_extended *to_fext_lower(trapezoidal_function *ft, float8 *ext) {
    return to_fext(ft, ext, "*<");
};

trapezoidal_function_extended *to_fext_lower_equal(trapezoidal_function *ft, float8 *ext) {
    return to_fext(ft, ext, "*<=");
};


// uniwersalna defuzyfikacja

bool defuzzy(float8 degree, char op[4], float8 threshold) {

    if (strcmp(op, "*=") == 0)
        return degree == threshold;
    if (op == "*<>")
        return degree != threshold;
    if (strcmp(op, "*<") == 0)
        return degree < threshold;
    if (strcmp(op, "*<=") == 0)
        return degree <= threshold;
    if (strcmp(op, "*>") == 0)
        return degree > threshold;
    if (strcmp(op, "*>=") == 0)
        return degree >= threshold;

    return true;
}

// A czyli fext i real
//*************************podzapytania typu ALL,ANY, IN, NOT IN (fext. real)******************

// defuzzyfikacja wartoci typu trapezoidal_function_extended z wartoscia dokadna

bool defuzzy_A(trapezoidal_function_extended *fext, float8 *data) {

    float8 degreex = 0;

    if ((fext == NULL) || (data == NULL))
        return false;

    degreex = degree(*data, fext->f);
    return defuzzy(degreex, fext->op, fext->ext);

}

bool not_defuzzy_A(trapezoidal_function_extended *fext, float8 *data) {
    if ((fext == NULL) || (data == NULL))
        return false;
    return !defuzzy_A(fext, data);
}

//*************************podzapytania typu ALL,ANY, IN, NOT IN (real, fext)******************
// B
// defuzzyfikacja wartoci dokladnej z wartoscia typu trapezoidal_function_extended

bool defuzzy_B(float8 *data, trapezoidal_function_extended *fext) {
    return defuzzy_A(fext, data);
}

bool not_defuzzy_B(float8 *data, trapezoidal_function_extended *fext) {
    if ((fext == NULL) || (data == NULL))
        return false;
    return !defuzzy_B(data, fext);
}


// C
//*************************podzapytania typu ALL,ANY, IN, NOT IN (fext, ft)******************

// defuzzyfikacja wartoci typu trapezoidal_function_extended z wartoscia typu trapezoidal_function


bool defuzzy_C(trapezoidal_function_extended *fext, trapezoidal_function *ft) {

    float8 degreex = 0;

    if ((fext == NULL) || (ft == NULL))
        return false;

    degreex = degreeftofft(fext->f, *ft);
    return defuzzy(degreex, fext->op, fext->ext);
}

bool not_defuzzy_C(trapezoidal_function_extended *fext, trapezoidal_function *ft) {

    if ((fext == NULL) || (ft == NULL))
        return false;

    return (!defuzzy_C(fext, ft));
}


// D
//*************************podzapytania typu ALL,ANY, IN, NOT IN (ft, fext)******************


// defuzzyfikacja wartoci typu trapezoidal_function z wartoscia typu trapezoidal_function_extended

bool defuzzy_D(trapezoidal_function *ft, trapezoidal_function_extended *fext) {

    if ((fext == NULL) || (ft == NULL))
        return false;

    return defuzzy_C(fext, ft);
}

bool not_defuzzy_D(trapezoidal_function *ft, trapezoidal_function_extended *fext) {
    if ((fext == NULL) || (ft == NULL))
        return false;

    return (!defuzzy_D(ft, fext));
}

// wartosci lingwistyczne 

trapezoidal_function *prawie_zaden() { return about_r(0.00, 0.00, 0.05, 0.10); }

trapezoidal_function *prawie_wszystkie() { return about_r(0.09, 0.95, 1.00, 1.00); }

trapezoidal_function *okolo_jedna_czwarta() { return about_r(0.10, 0.20, 0.30, 0.40); }

trapezoidal_function *okolo_jedna_trzecia() { return about_r(0.18, 0.28, 0.38, 0.48); }

trapezoidal_function *okolo_polowa() { return about_r(0.35, 0.45, 0.55, 0.65); }

trapezoidal_function *okolo_dwie_trzecie() { return about_r(0.51, 0.61, 0.71, 0.81); }

trapezoidal_function *okolo_trzy_czwarte() { return about_r(0.60, 0.70, 0.80, 0.90); }

trapezoidal_function *okolo_jeden() { return about_r(0, 1, 1, 2); }

trapezoidal_function *okolo_kilka() { return about_r(1, 3, 9, 12); }

trapezoidal_function *okolo_kilkanascie() { return about_r(8, 12, 19, 22); }

trapezoidal_function *okolo_kilkadziesiat() { return about_r(20, 30, 90, 120); }

trapezoidal_function *okolo_kilkaset() { return about_r(100, 300, 900, 1200); }

trapezoidal_function *okolo_minuta() { return about_r(40, 60, 60, 80); }

trapezoidal_function *okolo_kwadrans() { return about_r(10 * 60, 15 * 60, 15 * 60, 20 * 60); }

trapezoidal_function *okolo_godzina() { return about_r(40 * 60, 60 * 60, 60 * 60, 80 * 60); }

trapezoidal_function *okolo_tydzien() { return about_r(3, 7, 7, 11); }

trapezoidal_function *okolo_miesiac() { return about_r(20, 28, 31, 39); }

trapezoidal_function *okolo_rok() { return about_r(160, 365, 366, 570); }

text *sekundy_to_str(trapezoidal_function *sekundy) {

    if (sekundy == NULL)
        return toText("");

    if (is_equal(sekundy, okolo_minuta()))
        return toText("okolo_minuta");
    if (is_equal(sekundy, okolo_kwadrans()))
        return toText("okolo_kwadrans");
    if (is_equal(sekundy, okolo_godzina()))
        return toText("okolo_godzina");

    return toText(trapezoidal_function_out(sekundy));
}

text *dni_to_str(trapezoidal_function *dni) {

    if (dni == NULL)
        return toText("");

    if (is_equal(dni, okolo_tydzien()))
        return toText("okolo_tydzien");
    if (is_equal(dni, okolo_miesiac()))
        return toText("okolo_miesiac");
    if (is_equal(dni, okolo_rok()))
        return toText("okolo_rok");

    return toText(trapezoidal_function_out(dni));

}



//**********************************  pochodne odsetka* *****************************


float8 *odsetek_uni_final_func(twoint *last_state, trapezoidal_function *lingw) {
    float8 odsetek = 0;
    if ((last_state == NULL) || (lingw == NULL))
        return NULL;

    odsetek = ((float8) last_state->bool_count / (last_state->count));
    return degreerf(&odsetek, lingw);
}

float8 *odsetek_prawie_zaden(twoint *last_state) {
    return odsetek_uni_final_func(last_state, prawie_zaden());
}

float8 *odsetek_prawie_wszystkie(twoint *last_state) {
    return odsetek_uni_final_func(last_state, prawie_wszystkie());
}

float8 *odsetek_okolo_jedna_czwarta(twoint *last_state) {
    return odsetek_uni_final_func(last_state, okolo_jedna_czwarta());
}

float8 *odsetek_okolo_jedna_trzecia(twoint *last_state) {
    return odsetek_uni_final_func(last_state, okolo_jedna_trzecia());
}

float8 *odsetek_okolo_polowa(twoint *last_state) {
    return odsetek_uni_final_func(last_state, okolo_polowa());
}

float8 *odsetek_okolo_dwie_trzecie(twoint *last_state) {
    return odsetek_uni_final_func(last_state, okolo_dwie_trzecie());
}

float8 *odsetek_okolo_trzy_czwarte(twoint *last_state) {
    return odsetek_uni_final_func(last_state, okolo_trzy_czwarte());
}

