//
// Created by tobin on 2024-08-02.
//

#ifndef  SSTR_TEST_STACKIFY_H
#define  SSTR_TEST_STACKIFY_H

#include "../sstr.h"

int test_$stackify_0() {
    $ tmp = "ABCDEF";
    char *x = malloc(strlen(tmp));
    strcpy(x, tmp);

    $ stack = $stackify(x);
    free(x);

    return strcmp(tmp, stack) == 0;
}

int test_$stackify_1() {
    return strcmp("", $stackify(NULL)) == 0;
}

int test_$stackify_2() {
    return strcmp("", $stackify("")) == 0;
}

#endif //SSTR_TEST_STACKIFY_H
