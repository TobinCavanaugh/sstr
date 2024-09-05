//
// Created by tobin on 2024-09-03.
//

#ifndef SSTR_EXT_H
#define SSTR_EXT_H

#include "sstr.h"

#define $remove_at(_base$_ra, _index, _len) ({                                         \
    char * base$_ra = $from(_base$_ra);                                                \
    i32 index = _index;                                                                \
    i32 len = _len;                                                                    \
                                                                                       \
    $ new$_ra = $from(base$_ra);                                                       \
    mem_move(new$_ra + index, new$_ra + index + len, str_len(base$_ra) - index - len); \
    new$_ra[str_len(base$_ra) - len] = '\0' ;                                          \
    new$_ra;                                                                           \
})

// if(index < 0) { int tmp = len; len += index; index += tmp; }
// mem_move(str->data + index, str->data + index + length, (startLen - index - length) * sizeof(chr));


#define $replace(_base$_r, _old$, _new$) ({                       \
    $ base$_r = $from(_base$_r);                                  \
    $ old$ = _old$;                                               \
    $ new$_r = _new$;                                             \
                                                                  \
    u64 cursor = 0;                                               \
    for(; cursor < str_len(base$_r); cursor++) {                  \
        u8 found = 1;                                             \
        u64 x = 0;                                                \
        for(; x < str_len(old$); x++) {                           \
            if(base$_r[cursor + x] != old$[x]) {                  \
                found = 0;                                        \
                break;                                            \
            }                                                     \
        }                                                         \
                                                                  \
        if(found){                                                \
            base$_r = $remove_at(base$_r, cursor, str_len(old$)); \
            base$_r = $insert(base$_r, cursor, new$_r);           \
            cursor += str_len(new$_r) - 1;                        \
        }                                                         \
    }                                                             \
    /*Remove and insert, increment cursor by newLen*/             \
    base$_r;                                                      \
})

#endif //SSTR_EXT_H
