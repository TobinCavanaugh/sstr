//
// Created by tobin on 2024-08-02.
//

#ifndef SSTR_TEST_REALIZE_H
#define SSTR_TEST_REALIZE_H

/// Test basic functionality
/// \return
int test_$realize_0() {
    char *x = $realize("Test");
    int r = str_cmp("Test", x) == 0;
    hfree(x);
    return r;
}

/// Realize empty string
/// \return
int test_$realize_1() {
    char *x = $realize("");
    int r = str_cmp("", x) == 0;
    hfree(x);
    return r;
}

/// Realize a null string
/// \return
int test_$realize_2() {
    char *x = $realize(NULL);
    int r = str_cmp("", x) == 0;
    hfree(x);
    return r;
}

#endif //SSTR_TEST_REALIZE_H
