#import "./utils.h"

text *to_text(char *s) {
    text *result = (text *) palloc(VARHDRSZ + strlen(s));
    result->vl_len = VARHDRSZ + strlen(s);
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
