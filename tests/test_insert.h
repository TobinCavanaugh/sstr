//
// Created by tobin on 2024-08-01.
//

#ifndef SSTR_TEST_INSERT_H
#define SSTR_TEST_INSERT_H

#include "../sstr.h"
#include <string.h>


/// Baseline index 0 test
/// \return
int test_$insert_0() {
    $ x = $insert("00", 0, "1");
    return strcmp(x, "100") == 0;
}

/// Baseline end test
/// \return
int test_$insert_1() {
    $ x = $insert("10", 2, "0");
    return strcmp(x, "100") == 0;
}

/// Testing out of bounds - insert index
/// \return
int test_$insert_2() {
    $ x = $insert("BC", -100, "A");
    return strcmp(x, "ABC") == 0;
}

/// Testing out of bounds + insert index
/// \return
int test_$insert_3() {
    $ x = $insert("AB", 100, "C");
    return strcmp(x, "ABC") == 0;
}

/// Testing inserting null into something
/// \return
int test_$insert_4() {
    $ x = $insert("A", 0, NULL);
    return strcmp(x, "A") == 0;
}

/// Testing inserting something into null
/// \return
int test_$insert_5() {
    $ x = $insert(NULL, 0, "AA");
    return strcmp(x, "AA") == 0;
}

/// Testing inserting null into null
/// \return
int test_$insert_6() {
    $ x = $insert(NULL, 0, NULL);
    return strcmp(x, "") == 0;
}

/// Testing nested insert
/// \return
int test_$insert_7() {
    $ x = $insert($insert($insert($insert(NULL, 0, "4"), 0, "3"), 0, "2"), 0, "1");
    return strcmp(x, "1234") == 0;
}

#endif //SSTR_TEST_INSERT_H
