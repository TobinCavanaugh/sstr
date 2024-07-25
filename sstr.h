//
// Created by tobin on 6/17/2024.
//
/// \file

#include "../mem/salloc.h"
#include "../str/str.h"

#ifndef SSTR_SSTR_H
#define SSTR_SSTR_H

/// Definition for a string. Highly recommended to limit its use to
/// only stack strings for the sake of your sanity.
#define $ char *

/// Used with combination with $end(1). Creates a nested function
/// as to allow arena salloction like behavior. Use $realize to
/// convert a stack $ to a heap string.
/// @param NAME : Unique name to link with $end
/// @returns void
#define $begin(NAME) void __run_ ## NAME (void){

/// Used in combination with $begin(1)
/// @param NAME : Unique name to link with $begin
/// @returns void
#define $end(NAME) } __run_ ## NAME ();

/// Manually salloctes stack memory for your string
/// @param a : The source C string literal
/// @returns $ : The newly created $
#define $from(a) ({                     \
    char * tmp = a;                     \
    u64 len = str_len(tmp);             \
    $ f_new = salloc(len + 1);          \
    mem_copy(f_new, tmp, len + 1);      \
    f_new;                              \
})

/// Creates a new $ with the corresponding size and matching data
/// @param a : The base $ to be resized
/// @param size : The size of the new $
/// @returns $ : The new $
#define $resize(a, size) ({                     \
    char * atmp = a;                            \
    char * r_res = salloc(size);                \
    mem_copy(r_res, atmp, str_len(atmp) + 1);   \
    r_res;                                      \
})

/// Creates a $ from a C printf style format and args.
/// @param fmt : The format to create the string from
/// @param ... : The varargs to fill into the format
/// @returns $ : A $ of the correct formatting
#define $from_fmt(fmt, ...) ({                          \
  char * tmpfmt = fmt;                                  \
  /*Calculate length of string*/                        \
  u64 flen = snprintf(NULL, 0, tmpfmt, __VA_ARGS__);    \
  char *f_res = salloc(flen + 1);                       \
  sprintf(f_res, tmpfmt, __VA_ARGS__);                  \
  f_res;                                                \
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
#define $append(a, b) ({                        \
    char * base = a;                            \
    char * add = b;                             \
    u64 alen = str_len(base);                   \
    u64 blen = str_len(add);                    \
    $ a_res = $resize(base, alen + blen + 1);   \
    str_copy(a_res, base);                      \
    str_copy(a_res + alen, add);                \
    a_res;                                      \
})

/// Inserts _add into the $ _str at _index
/// @param baseStr : The base string
/// @param _index : The index in _str for _add to be inserted at. This will be
/// clamped between [0 and str_len+1].
/// @param addStr : The $ to be inserted
/// @returns $ : A $ with the same contents as _str but with _add inserted.
#define $insert(baseStr, _index, addStr) ({                 \
    $ i_res = $from("");                                    \
    char * _str = baseStr;                                  \
    char * _add = addStr;                                   \
                                                            \
    u64 index = _index;                                     \
    u64 startLen = str_len(_str);                           \
    u64 addLen = str_len(_add);                             \
                                                            \
    if(addLen == 0)                                         \
    {                                                       \
        i_res = $from("");                                  \
        i_res;                                              \
    }                                                       \
                                                            \
    if(index > startLen)                                    \
    {                                                       \
        index = startLen;                                   \
    }                                                       \
                                                            \
    if(index < 0)                                           \
    {                                                       \
        index = 0;                                          \
    }                                                       \
                                                            \
    i_res = $resize(_str, startLen + addLen + 1 + 10);      \
                                                            \
    {                                                       \
        u64 rightSize = (startLen - index);                 \
        $ tmp = salloc(rightSize + 1);                      \
                                                            \
        mem_copy(tmp, _str + index, rightSize + 1);         \
        mem_copy(i_res + (index + addLen), tmp, rightSize); \
        mem_copy(i_res + index, _add, addLen);              \
    }                                                       \
                                                            \
    i_res[startLen + addLen] = '\0';                        \
    i_res;                                                  \
})

/// Takes a substring of a $ from start with len
/// @param _base : The base $
/// @param _start : The start index. In the case this is negative, the negative
/// numbers will be subtracted from length. This means that an index of -1 and
/// a length of 3 will result in the first 2 characters being read.
/// @param _len : The length of the substringa
/// @returns $ : The resulting substring as a stack string
#define $substr(_base, _start, _len) ({     \
    char *a = _base;                        \
    u64 alen = str_len(a);                  \
    u64 len = _len;                         \
    u64 start = _start;                     \
    $ s_res = NULL;                         \
                                            \
    if(start < 0){                          \
        len += start;                       \
        start = 0;                          \
    }                                       \
                                            \
    if(len <= 0){                           \
        s_res = $from("");                  \
        s_res;                              \
    }                                       \
                                            \
    while(start + len > alen){              \
        len--;                              \
        if(len <= 0){                       \
            s_res = $from("");              \
            s_res;                          \
        }                                   \
    }                                       \
                                            \
    s_res = salloc(len + 1);                \
                                            \
    mem_copy(s_res, a + start, len);          \
    s_res[len] = '\0';                      \
                                            \
    s_res;                                  \
})

/// Creates a heap sallocted string from the $
/// @param a : The $ to be stack allocated
/// @returns char * : A char pointer to the newly sallocted string
#define $realize(a) ({              \
    char * _a = a;                  \
    u64 len = str_len(_a);          \
    char * new = malloc(len + 1);   \
    mem_copy(new, _a, len + 1);     \
    new;                            \
})

/// Creates a stack sallocted string from the $
/// @param a : The $ to be sallocted
/// @returns $ : The stack string
#define $stackify(a) ({             \
    char * _a = a;                  \
    u64 len = str_len(_a);          \
    $ new = salloc(len);            \
    mem_copy(new, _a, len + 1);     \
    new;                            \
})


#endif //SSTR_SSTR_H