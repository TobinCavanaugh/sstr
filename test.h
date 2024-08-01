//
// Created by tobin on 2024-07-31.
//

#ifndef SSTR_TEST_H
#define SSTR_TEST_H

#include "sstr.h"
#include <stdio.h>
#include <string.h>

#include "tests/test_append.h"
#include "tests/test_insert.h"
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
