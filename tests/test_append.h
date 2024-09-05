//
// Created by tobin on 2024-08-01.
//

#ifndef SSTR_TEST_APPEND_H
#define SSTR_TEST_APPEND_H

#include "../sstr.h"
#include <string.h>

/// Basic append test
/// \return
int test_$append_0() {
    $ a = $from("base");
    $ b = $from("add");
    $ c = $append(a, b);
    return strcmp(c, "baseadd") == 0;
}

/// Do lots of nested appends
/// \return
int test_$append_1() {
    $ a = $append($append($append($append("-", "-"), "-"), "-"), "-");
    return strcmp(a, "-----") == 0;
}

/// Appending nothing to NULL
/// \return
int test_$append_2() {
    $ x = $append(NULL, $from(""));
    return strcmp(x, "") == 0;
}

/// Appending NULL to nothing
/// \return
int test_$append_3() {
    $ x = $append("", NULL);
    return strcmp(x, "") == 0;
}

/// Appending NULL to NULL
/// \return
int test_$append_4() {
    $ x = $append(NULL, NULL);
    return strcmp(x, "") == 0;
}

/// Append nothing to nothing
/// \return
int test_$append_5(){
    $ x = $append("", "");
    return strcmp(x, "") == 0;
}

#endif //SSTR_TEST_APPEND_H
