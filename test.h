//
// Created by tobin on 2024-07-31.
//

#ifndef SSTR_TEST_H
#define SSTR_TEST_H

#include "sstr.h"
#include <stdio.h>
#include <string.h>

#include "tests/test_append.h"
#include "tests/test_from.h"
#include "tests/test_insert.h"
#include "tests/test_realize.h"
#include "tests/test_stackify.h."
#include "tests/test_substr.h"


void test_all() {
    printf("Append      Tests:  ");
    printf("%d  ", test_$append_0());
    printf("%d  ", test_$append_1());
    printf("%d  ", test_$append_2());
    printf("%d  ", test_$append_3());
    printf("%d  ", test_$append_4());
    printf("%d  ", test_$append_5());

    printf("\n");

    printf("Insert      Tests:  ");
    printf("%d  ", test_$insert_0());
    printf("%d  ", test_$insert_1());
    printf("%d  ", test_$insert_2());
    printf("%d  ", test_$insert_3());
    printf("%d  ", test_$insert_4());
    printf("%d  ", test_$insert_5());
    printf("%d  ", test_$insert_6());
    printf("%d  ", test_$insert_7());

    printf("\n");


    printf("From        Tests:  ");


    printf("%d  ", test_$from_0());
    printf("%d  ", test_$from_1());
    printf("%d  ", test_$from_2());
    printf("%d  ", test_$from_3());

    printf("\n");

    printf("Realize     Tests:  ");

    printf("%d  ", test_$realize_0());
    printf("%d  ", test_$realize_1());
    printf("%d  ", test_$realize_2());

    printf("\n");

    printf("Stackify    Tests:  ");

    printf("%d  ", test_$stackify_0());
    printf("%d  ", test_$stackify_1());
    printf("%d  ", test_$stackify_2());
    printf("\n");

    printf("Substring   Tests:  ");
    printf("%d  ", test_$substr_0());
    printf("%d  ", test_$substr_1());
    printf("%d  ", test_$substr_2());
    printf("%d  ", test_$substr_3());
    printf("%d  ", test_$substr_4());
    printf("%d  ", test_$substr_5());
    printf("%d  ", test_$substr_6());

    printf("\n");
}


#endif //SSTR_TEST_H
