#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "sw.h"

#define u_len uintptr_t

typedef enum {
    STACK,
    HEAP,
} STRING_MODE;

//typedef struct {
//    char *data;
//    uint8_t mode;
//} $;

#define $ char *

#define $from(c) ({ int len = strlen(c); char* a = alloca(len + 1); memcpy(a, c, len + 1); a; })
#define resize(a, size) {char * tmp = a; a = alloca(size); memcpy(a, tmp, size); }
#define $strmod(a) {void run(void){a} run(); }

#define realize(a) { int len = strlen(a); char * tmp = a; a = malloc(len + 1); memcpy(a, tmp, len + 1);}

//HEAP -> STACK
#define stackify(a) { \
    int len = strlen(a);  \
    char * tmp = a;       \
    a = alloca(len + 1);  \
    memcpy(a, tmp, len + 1); \
    free(tmp); }

#define $append(a, b) { \
    int alen = strlen(a); \
    int blen = strlen(b); \
    resize(a, alen + blen + 1); \
    memcpy(a + alen, b, blen + 1); \
}

#define $from_fmt(fmt, ...) ({ \
  /*Calculate length of string*/                             \
  int flen = snprintf(NULL, 0, fmt, __VA_ARGS__); \
  char *a = alloca(flen + 1); \
  sprintf(a, fmt, __VA_ARGS__); \
  a; \
})

#define sf_begin void ___RUN___(){

#define sf_end } ___RUN___();

#define exp __COUNTER__

//#define CONCAT_(a, b) a##b
//#define CONCAT(a, b) CONCAT_(a, b)
//#define varname(a) CONCAT(b##_, __LINE__)

//#define start 63
//#define begin CONCAT(void __portal##_, start) () {
//#define end }} CONCAT(__portal##_, start)()

#define format  "--%d_%s--"
#define args 100, "124142"

inline void Print() {
    $ a = $from_fmt(format, args);
    $append(a, "\n");
//            printf("%s", a);
}

int main() {

    int max = 100;

    double start = sw_start_us();
    int i = 0;
    for (; i < max; i++) {
        sf_begin
            $ a = $from("");
            $append(a, "\n");
        sf_end;
    }
    sw_print_us(start);

    double alt = sw_start_us();
    i = 0;
    for (; i < max; i++) {
        char *buf = NULL;

        int res = snprintf(buf, 0, format, args);
        buf = malloc((res + 1) * sizeof(char));
        sprintf(buf, format, args);

        buf = realloc(buf, strlen(buf) + 1);
        strcat(buf, "\n");

        free(buf);
    }
    sw_print_us(alt);



//    printf("\n%s", a);

    return 1;
}
