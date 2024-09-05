//
// Created by tobin on 2024-07-31.
//

#ifndef SSTR_TEST_H
#define SSTR_TEST_H

#include "sstr.h"
// #include <stdio.h>
// #include <string.h>
#include "../str/str_cmp.h"

#include "tests/test_append.h"
#include "tests/test_from.h"
#include "tests/test_insert.h"
#include "tests/test_realize.h"
#include "tests/test_stackify.h."
#include "tests/test_substr.h"


void test_all() {
    put_f("Append      Tests:  ");
    put_f("{0}  ", test_$append_0());
    put_f("{0}  ", test_$append_1());
    put_f("{0}  ", test_$append_2());
    put_f("{0}  ", test_$append_3());
    put_f("{0}  ", test_$append_4());
    put_f("{0}  ", test_$append_5());

    put_f("\n");

    put_f("Insert      Tests:  ");
    put_f("{0}  ", test_$insert_0());
    put_f("{0}  ", test_$insert_1());
    put_f("{0}  ", test_$insert_2());
    put_f("{0}  ", test_$insert_3());
    put_f("{0}  ", test_$insert_4());
    put_f("{0}  ", test_$insert_5());
    put_f("{0}  ", test_$insert_6());
    put_f("{0}  ", test_$insert_7());

    put_f("\n");


    put_f("From        Tests:  ");


    put_f("{0}  ", test_$from_0());
    put_f("{0}  ", test_$from_1());
    put_f("{0}  ", test_$from_2());
    put_f("{0}  ", test_$from_3());

    put_f("\n");

    put_f("Realize     Tests:  ");

    put_f("{0}  ", test_$realize_0());
    put_f("{0}  ", test_$realize_1());
    put_f("{0}  ", test_$realize_2());

    put_f("\n");

    put_f("Stackify    Tests:  ");

    put_f("{0}  ", test_$stackify_0());
    put_f("{0}  ", test_$stackify_1());
    put_f("{0}  ", test_$stackify_2());
    put_f("\n");

    put_f("Substring   Tests:  ");
    put_f("{0}  ", test_$substr_0());
    put_f("{0}  ", test_$substr_1());
    put_f("{0}  ", test_$substr_2());
    put_f("{0}  ", test_$substr_3());
    put_f("{0}  ", test_$substr_4());
    put_f("{0}  ", test_$substr_5());
    put_f("{0}  ", test_$substr_6());

    put_f("\n");
}


#endif //SSTR_TEST_H
