//
// Created by tobin on 2024-08-02.
//

#ifndef  SSTR_TEST_STACKIFY_H
#define  SSTR_TEST_STACKIFY_H

#include "../sstr.h"

/// Test stackifying a standard string
/// \return
int test_$stackify_0() {
    $ tmp = "ABCDEF";
    char *x = halloc(strlen(tmp));
    strcpy(x, tmp);

    $ stack = $stackify(x);
    hfree(x);

    return str_cmp(tmp, stack) == 0;
}

/// Test stackifying null
/// \return
int test_$stackify_1() {
    return str_cmp("", $stackify(NULL)) == 0;
}

/// Test stackifying nothing
/// \return
int test_$stackify_2() {
    return str_cmp("", $stackify("")) == 0;
}

#endif //SSTR_TEST_STACKIFY_H
