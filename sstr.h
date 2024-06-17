//
// Created by tobin on 6/17/2024.
//

#ifndef SSTR_SSTR_H
#define SSTR_SSTR_H

#define $ char *

/// Manually allocates stack memory for your string
/// @param a : The source C string literal
/// @returns $ : The newly created $
#define $from(a) ({                     \
    int len = strlen(a);                \
    char* f_new = alloca(len + 1);      \
    memcpy(f_new, a, len + 1);          \
    f_new;                              \
})

/// Creates a new $ with the corresponding size and matching data
/// @param a : The base $ to be resized
/// @param size : The size of the new $
/// @returns $ : The new $
#define $resize(a, size) ({           \
    char * r_res = alloca(size);      \
    memcpy(r_res, a, strlen(a) + 1);  \
    r_res;                            \
})

/// Creates a $ from a C printf style format and args.
/// @param fmt : The format to create the string from
/// @param ... : The varargs to fill into the format
/// @returns $ : A $ of the correct formatting
#define $from_fmt(fmt, ...) ({                      \
  /*Calculate length of string*/                    \
  int flen = snprintf(NULL, 0, fmt, __VA_ARGS__);   \
  char *f_res = alloca(flen + 1);                   \
  sprintf(f_res, fmt, __VA_ARGS__);                 \
  f_res;                                            \
})

/// Appends the arguments formatted to fmt to the base. Uses the standard
/// C formatting. Think printf
/// @param a : The base $
/// @param fmt : The format string for the following varargs
/// @param ... : The varags, comma separated
/// @returns $ : The resulting combined string.
#define $append_fmt(a, fmt, ...) ({     \
    $ b = $from_fmt(fmt, __VA_ARGS__);  \
    $ af_res = $append(a, b);           \
    af_res;                             \
})

/// Appends b to a.
/// @param a : The base $
/// @param b : The $ to be appended
/// @returns $ : The resulting combined string
#define $append(a, b) ({                    \
    int alen = strlen(a);                   \
    int blen = strlen(b);                   \
    $ a_res = $resize(a, alen + blen + 1);  \
    memcpy(a_res, a, alen);                 \
    memcpy(a_res + alen, b, blen + 1);      \
    a_res;                                  \
})

/// Takes a substring of a from start with len
/// @param a : The base $
/// @param _start : The start index
/// @param _len : The length of the substring
#define $substr(a, _start, _len) ({         \
    int alen = strlen(a);                   \
    int len = _len;                         \
    int start = _start;                     \
    $ s_res = NULL;                         \
                                            \
    if(start < 0){                          \
        len += start;                       \
        start = 0;                          \
    }                                       \
                                            \
    if(len <= 0){                           \
        s_res = $from("");                  \
        goto slice_done;                    \
    }                                       \
                                            \
    while(start + len > alen){              \
        len--;                              \
        if(len <= 0){                       \
            s_res = $from("");              \
            goto slice_done;                \
        }                                   \
    }                                       \
                                            \
    s_res = alloca(len + 1);                \
                                            \
    memcpy(s_res, a + start, len);          \
    s_res[len] = '\0';                      \
                                            \
    slice_done:                             \
    s_res;                                  \
})

/// Creates a heap allocated string from the $
/// @param a : The $ to be converted
/// @returns char * : A char pointer to the newly allocated string
#define $realize(a) ({              \
    int len = strlen(a);            \
    char * new = malloc(len + 1);   \
    memcpy(new, a, len + 1);        \
    new;                            \
})

#endif //SSTR_SSTR_H
