/*NOTES MOVED TO BOTTOM OF FILE*/
/*!!! sstr.h relies on statement expressions. !!!*/

#ifndef SSTR_SSTR_H
#define SSTR_SSTR_H

#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stdint.h>

//#define sstr_alloca(size) ({char * ptr = (char*) __builtin_alloca(size); ptr;})
#define sstr_alloca(size) ({ char * a_x = (char*) alloca(size); a_x;})

/// Returns 1 if the string is NULL or empty
#define strnoe(_s_a) ({char * ss_a = _s_a; (ss_a == NULL || ss_a[0] == '\0');})

/// Basic macro for preventing IDE/compiler from yelling at me
#define SSTR_API __attribute__((unused))

/// Definition for a string. Highly recommended to limit its use to
/// only stack strings for the sake of your sanity.
#define $ char *

/// Used with combination with $end(1). Creates a nested function
/// as to allow arena allocation like behavior. Use $realize to
/// convert a stack $ to a heap string.
/// @param NAME : Unique name to link with $end
#define $begin(NAME) SSTR_API void __run_ ## NAME (void){

/// Used in combination with $begin(1)
/// @param NAME : Unique name to link with $begin
#define $end(NAME) } __run_ ## NAME ();

/// Manually allocates stack memory for your string
/// @param _a : The source C string literal
/// @returns $ : The newly created $
#define $from(_a) ({                        \
    $ f_a = _a;                             \
    $ f_new = "";                           \
    if(f_a != NULL) {                       \
        int f_len = strlen(f_a);            \
        f_new = ($) sstr_alloca(f_len + 1); \
        memcpy(f_new, f_a, f_len + 1);      \
    }                                       \
    f_new;                                  \
})


/// Creates a new $ with the corresponding size and matching data.
/// This is primarily an internal function, and is not particularly safe. You
/// should have no good reason to use this.
/// @param r_a : The base $ to be resized
/// @param size : The size of the new $
/// @returns $ : The new $
#define $resize(r_a, size) ({                  \
    $ re_a = r_a;                              \
    $ r_res = sstr_alloca(size);               \
    r_res[0] = '\0';                           \
    if(re_a != NULL) {                         \
        memcpy(r_res, re_a, strlen(re_a) + 1); \
    }                                          \
    r_res;                                     \
})

/// Creates a $ from a C printf style format and args.
/// @param _fmt : The format to create the string from
/// @param ... : The varargs to fill into the format
/// @returns $ : A $ of the correct formatting
#define $from_fmt(_fmt, ...) ({                     \
    char * fmt = _fmt;                              \
    /*Calculate length of string*/                  \
    int flen = snprintf(NULL, 0, fmt, __VA_ARGS__); \
    char *f_res = sstr_alloca(flen + 1);            \
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
#define $append(_a, _b) ({                                \
    $ a_a = _a;                                           \
    $ a_b = _b;                                           \
                                                          \
    $ a_res = NULL;                                       \
                                                          \
    /*Do our normal logic if both args are valid*/        \
    if(!strnoe(a_a) && !strnoe(a_b)) {                    \
        int a_alen = strlen(a_a);                         \
        int a_blen = strlen(a_b);                         \
        a_res = $resize(a_a, a_alen + a_blen + 1);        \
        internal_$append_helper(a_res, a_a, a_alen, a_b); \
    }                                                     \
    /*If _a is null, _b is our fallback*/                 \
    if(strnoe(a_a) && !strnoe(a_b)) {                     \
        a_res = $from(a_b);                               \
    }                                                     \
    /*If _b is null, _a is our fallback*/                 \
    if(strnoe(a_b) && !strnoe(a_a)) {                     \
        a_res = $from(a_a);                               \
    }                                                     \
    /*If both are NULL, "" is our fallback*/              \
    if(strnoe(a_a) && strnoe(a_b)) {                      \
        a_res = "";                                       \
    }                                                     \
                                                          \
    a_res;                                                \
})

SSTR_API static void internal_$insert_helper($ _str, $ i_res, $ _add,
                                             int index, int startLen, int addLen) {
    int rightSize = (startLen - index);
    $ tmp = sstr_alloca(rightSize + 1);

    /*
     * Could probably use memmove for this, but im lazy and moving this
     * looks scary
     */

    /*Copy in our default content, this caused a little bug but thanks to this
     * being in a function it was super easy to debug. */
    memcpy(i_res, _str, startLen);

    /*Grab the content to the right of our index and put it into our tmp*/
    memcpy(tmp, _str + index, rightSize + 1);

    /*Place that grabbed temporary string and place it at the end of our str*/
    memcpy(i_res + (index + addLen), tmp, rightSize);

    /*Place our addstring in the center, overwriting the old content*/
    memcpy(i_res + index, _add, addLen);
}

/// Inserts _add into the $ _str at _index
/// @param str : The base string
/// @param index : The index in _str for _add to be inserted at. This will be
/// clamped between [0 and strLen+1].
/// @param add : The $ to be inserted
/// @returns $ : A $ with the same contents as _str but with _add inserted.
#define $insert(str, index, add) ({                            \
    $ i_str = str;                                             \
    $ i_add = add;                                             \
    $ i_res;                                                   \
    int _index = index;                                        \
                                                               \
    /*Do regular business logic*/                              \
    if(!strnoe(i_str) && !strnoe(i_add)){                      \
        int i_startLen = strlen(i_str);                        \
        int i_addLen = strlen(i_add);                          \
                                                               \
        /*Cap our insert point within string bounds*/          \
        if(_index > i_startLen) {                              \
            _index = i_startLen;                               \
        }                                                      \
        if(_index < 0) {                                       \
            _index = 0;                                        \
        }                                                      \
                                                               \
        i_res = sstr_alloca(i_startLen + i_addLen + 1);        \
        internal_$insert_helper(i_str, i_res, i_add,           \
                                _index, i_startLen, i_addLen); \
        i_res[i_startLen + i_addLen] = '\0';                   \
    }                                                          \
                                                               \
    if(!strnoe(i_str) && strnoe(i_add)) {                      \
        i_res = $from(i_str);                                  \
    }                                                          \
                                                               \
    if(strnoe(i_str) && !strnoe(i_add)) {                      \
        i_res = $from(i_add);                                  \
    }                                                          \
                                                               \
    if(strnoe(i_str) && strnoe(i_add)) {                       \
        i_res = $from("");                                     \
    }                                                          \
                                                               \
    i_res;                                                     \
})

/// Takes a substring of a $ from start with len
/// @param _a : The base $
/// @param _start : The start index. In the case this is negative, the negative
/// numbers will be subtracted from length. This means that an index of -1 and
/// a length of 3 will result in the first 2 characters being read.
/// @param _len : The length of the substringa
/// @returns $ : The resulting substring as a stack string
#define $substr(_a, _start, _len) ({             \
    $ s_a = _a;                                  \
    int s_len = _len;                            \
    int s_start = _start;                        \
    $ s_res = NULL;                              \
                                                 \
    /*If we need to do any substr at all*/       \
    if(!strnoe(s_a) && s_len > 0) {              \
        int s_alen = strlen(s_a);                \
        if(s_start < 0){                         \
            s_len += s_start;                    \
            s_start = 0;                         \
        }                                        \
                                                 \
        /*Prevent out of bounds accessing*/      \
        while(s_start + s_len > s_alen) {        \
            s_len--;                             \
        }                                        \
                                                 \
        if(s_len > 0) {                          \
            s_res = sstr_alloca(s_len + 1);      \
            memcpy(s_res, s_a + s_start, s_len); \
            s_res[s_len] = '\0';                 \
        }  else {                                \
            s_res = $from("");                   \
        }                                        \
    }                                            \
                                                 \
    if(s_len <= 0) {                             \
        s_res = $from("");                       \
    }                                            \
                                                 \
    if(strnoe(s_a)) {                            \
        s_res = $from("");                       \
    }                                            \
                                                 \
    s_res;                                       \
})

/// Creates a heap allocated string from the $
/// @param _a : The $ to be allocated
/// @returns char * : A char pointer to the newly allocated string
#define $realize(_a) ({           \
    $ rel_a = _a;                 \
    if(strnoe(_a)) {              \
        rel_a = "";               \
    }                             \
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
                                \
    if(strnoe(_a)) {            \
        st_a = "";              \
    }                           \
                                \
    int len = strlen(st_a);     \
    $ new = sstr_alloca(len);   \
    memcpy(new, st_a, len + 1); \
    new;                        \
})

#endif //SSTR_SSTR_H

/* Notes:
 * Current stability : 8/10
 * WARNING: alloca allocations are not validated in any way. apparently the
 *          POSIX way is to fall back on malloc for this, which is awesome
 *          because it's harder to validate than NULL and also means that
 *          you can get some hard to fix memory leaks. :)
 * TODO: I'd really like to have this be character format agnostic, at least
 * by allowing for local redefining of strlen and that sorta thing...
 *
 * 2024-08-07 | Tobin Cavanaugh | ---------------------------------------------
 * New update here. Of course I've already got my eye on doing a new string
 * library, i'm thinking sstr + fstr + a new cool thing where I make strings
 * into chunks, so minor string edits are nearly instant... indexing might
 * be a pain tho. Either way I added benchmarking of $append to the readme,
 * and I've gotta make more benchmarks, I'm just being lazy.
 *
 * 2024-08-04 | Tobin Cavanaugh | ---------------------------------------------
 * Favorite thing in the world is happening, -O3 causes insert to not work
 * properly. I guess I should count myself lucky that that's the only one thats
 * breaking. The tests have already paid themselves off ten-fold. Shockingly
 * this took me like 10 minutes to fix. Having functions that handle the memcpy
 * and dangerous stuff makes debugging 1,000,000x easier, this should be
 * standard behavior most of the time.
 *
 * 2024-08-01 | Tobin Cavanaugh | ---------------------------------------------
 * [X]: I really should have better comments and error handling in the code.
 * Did a huge pass of error fixes and adding tests. Still trying to avoid
 * using the term 'bug', because that implies the computer is at fault... which
 * is rarely true in C. The error pass caught a bunch of stuff,  and also
 * brought me to add the macro/function strnoe (string null or empty) which
 * returns 1 if its null or empty, and 0 if its not. Sadly had to make this
 * a statement expression, which I'd rather not do, but I have to cuz the
 * potential for errors I talked about in the previous note.
 *
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
