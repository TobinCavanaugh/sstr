/* Notes:
 * 2024-07-31 | Tobin Cavanaugh | ---------------------------------------------
 * Realized recently I forgot to immediately memoize the arguments of the
 * macros. Whenever you're using macros its key to not re-use the same argument
 * names later in your function, Brian Kernighan talks about this well in his
 * talk on programming idioms, but the short of it is that operators like ++
 * also get passed, as macros are just textual replacement. In the case of a
 * macro taking argument `a`, if whats passed is `i++` any time the argument
 * `a` is used, it will place `i++` in, thus incrementing multiple times. This
 * is a pretty hellish bug, so I'm glad I saw the talk he did on this and a few
 * similar things. Also note I'm migrating all I can to functions to allow for
 * more helpful error lines and debugging.
 */

#ifndef SSTR_SSTR_H
#define SSTR_SSTR_H

#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stdint.h>

#define SSTR_API __attribute__((unused))

/// Definition for a string. Highly recommended to limit its use to
/// only stack strings for the sake of your sanity.
#define $ char *

/// Used with combination with $end(1). Creates a nested function
/// as to allow arena allocation like behavior. Use $realize to
/// convert a stack $ to a heap string.
/// @param NAME : Unique name to link with $end
/// @returns void
#define $begin(NAME) void __run_ ## NAME (void){

/// Used in combination with $begin(1)
/// @param NAME : Unique name to link with $begin
/// @returns void
#define $end(NAME) } __run_ ## NAME ();

/// Manually allocates stack memory for your string
/// @param _a : The source C string literal
/// @returns $ : The newly created $
#define $from(_a) ({                        \
    $ f_a = _a;                             \
    int f_len = strlen(f_a);                \
    char* f_new = alloca(f_len + 1);        \
    memcpy(f_new, f_a, f_len + 1);          \
    f_new;                                  \
})

/// Creates a new $ with the corresponding size and matching data
/// @param a : The base $ to be resized
/// @param size : The size of the new $
/// @returns $ : The new $
#define $resize(r_a, size) ({              \
    $ re_a = r_a;                          \
    char * r_res = alloca(size);           \
    memcpy(r_res, re_a, strlen(re_a) + 1); \
    r_res;                                 \
})

/// Creates a $ from a C printf style format and args.
/// @param _fmt : The format to create the string from
/// @param ... : The varargs to fill into the format
/// @returns $ : A $ of the correct formatting
#define $from_fmt(_fmt, ...) ({                     \
    char * fmt = _fmt;                              \
    /*Calculate length of string*/                  \
    int flen = snprintf(NULL, 0, fmt, __VA_ARGS__); \
    char *f_res = alloca(flen + 1);                 \
    sprintf(f_res, fmt, __VA_ARGS__);               \
    f_res;                                          \
})

/// Appends the arguments formatted to fmt to the base. Uses the standard
/// C formatting. Think printf
/// @param af_a : The base $
/// @param fmt : The format string for the following varargs
/// @param ... : The varags, comma separated
/// @returns $ : The resulting combined string.
#define $append_fmt(af_a, fmt, ...) ({    \
    $ af_b = $from_fmt(fmt, __VA_ARGS__); \
    $ af_res = $append(af_a, af_b);       \
    af_res;                               \
})

SSTR_API static void internal_$append_helper($ a_res, $ a, int alen, $ b) {
    strcpy(a_res, a);
    strcpy(a_res + alen, b);
}

/// Appends b to a.
/// @param _a : The base $
/// @param _b : The $ to be appended
/// @returns $ : The resulting combined string
#define $append(_a, _b) ({                            \
    $ a_a = _a;                                       \
    $ a_b = _b;                                       \
    int a_alen = strlen(a_a);                         \
    int a_blen = strlen(a_b);                         \
    $ a_res = $resize(a_a, a_alen + a_blen + 1);      \
    internal_$append_helper(a_res, a_a, a_alen, a_b); \
                                                      \
    a_res;                                            \
})

SSTR_API static void internal_$insert_helper($ _str, $ i_res, $ _add,
                                             int index, int startLen, int addLen) {
    int rightSize = (startLen - index);
    $ tmp = alloca(rightSize + 1);

    /*
     * Could probably use memmove for this, but im lazy and moving this
     * looks scary
     */
    memcpy(tmp, _str + index, rightSize + 1);
    memcpy(i_res + (index + addLen), tmp, rightSize);
    memcpy(i_res + index, _add, addLen);
}

/// Inserts _add into the $ _str at _index
/// @param str : The base string
/// @param index : The index in _str for _add to be inserted at. This will be
/// clamped between [0 and strLen+1].
/// @param add : The $ to be inserted
/// @returns $ : A $ with the same contents as _str but with _add inserted.
#define $insert(str, index, add) ({                                      \
    $ i_str = str;                                                       \
    $ i_add = add;                                                       \
    $ i_res;                                                             \
    int _index = index;                                                  \
    int i_startLen = strlen(i_str);                                      \
    int i_addLen = strlen(i_add);                                        \
                                                                         \
    if(_index > i_startLen) {                                            \
        _index = i_startLen;                                             \
    }                                                                    \
                                                                         \
    if(_index < 0) {                                                     \
        _index = 0;                                                      \
    }                                                                    \
                                                                         \
    i_res = $resize(i_str, i_startLen + i_addLen + 1);                   \
                                                                         \
    internal_$insert_helper(i_str, i_res, i_add,                         \
                            _index, i_startLen, i_addLen);               \
                                                                         \
    i_res[i_startLen + i_addLen] = '\0';                                 \
    i_res;                                                               \
})

/// Takes a substring of a $ from start with len
/// @param _a : The base $
/// @param _start : The start index. In the case this is negative, the negative
/// numbers will be subtracted from length. This means that an index of -1 and
/// a length of 3 will result in the first 2 characters being read.
/// @param _len : The length of the substringa
/// @returns $ : The resulting substring as a stack string
#define $substr(_a, _start, _len) ({   \
    $ s_a = _a;                        \
    int s_alen = strlen(s_a);          \
    int s_len = _len;                  \
    int start = _start;                \
    $ s_res = NULL;                    \
                                       \
    if(start < 0){                     \
        s_len += start;                \
        start = 0;                     \
    }                                  \
                                       \
    if(s_len <= 0){                    \
        s_res = $from("");             \
        s_res;                         \
    }                                  \
                                       \
    while(start + s_len > s_alen){     \
        s_len--;                       \
        if(s_len <= 0){                \
            s_res = $from("");         \
            s_res;                     \
        }                              \
    }                                  \
                                       \
    s_res = alloca(s_len + 1);         \
                                       \
    memcpy(s_res, s_a + start, s_len); \
    s_res[s_len] = '\0';               \
                                       \
    s_res;                             \
})

/// Creates a heap allocated string from the $
/// @param _a : The $ to be allocated
/// @returns char * : A char pointer to the newly allocated string
#define $realize(_a) ({           \
    $ rel_a = _a;                 \
    int len = strlen(rel_a);      \
    char * new = malloc(len + 1); \
    memcpy(new, rel_a, len + 1);  \
    new;                          \
})

/// Creates a stack allocated string from the $
/// @param _a : The $ to be allocated
/// @returns $ : The stack string
#define $stackify(_a) ({        \
    $ st_a = _a;                \
    int len = strlen(st_a);     \
    $ new = alloca(len);        \
    memcpy(new, st_a, len + 1); \
    new;                        \
})

#endif //SSTR_SSTR_H