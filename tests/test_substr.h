//
// Created by tobin on 2024-08-01.
//

#ifndef SSTR_TEST_SUBSTR_H
#define SSTR_TEST_SUBSTR_H

/// Basic substring test
/// \return
int test_$substr_0() {
    $ base = "012345";
    $ sub = $substr(base, 0, 2);
    return strcmp(sub, "01") == 0;
}

/// Substring with index and length of 0
/// \return
int test_$substr_1() {
    $ base = "012345";
    $ sub = $substr(base, 0, 0);
    return strcmp(sub, "") == 0;
}

/// Substring with index -100 and length 101, sampling the first char
/// \return
int test_$substr_2() {
    $ base = "012345";
    $ sub = $substr(base, -100, 101);
    return strcmp(sub, "0") == 0;
}

/// Substring with index and length positively out of bounds
/// \return
int test_$substr_3() {
    $ base = "0123456789";
    $ sub = $substr(base, 1000, 1000);
    return strcmp(sub, "") == 0;
}

/// Substring with index and length negatively out of bounds
/// \return
int test_$substr_4() {
    $ base = "0123456789";
    $ sub = $substr(base, -1000, -1000);
    return strcmp(sub, "") == 0;
}

/// Test with index 0 and positive & negative out of bounds length
/// \return
int test_$substr_5() {
    $ base = "0123456789";
    //Should negative length get the string from the index backwards?...
    $ subNeg = $substr(base, 0, -1000);
    $ subPos = $substr(base, 0, 1000);
    return ((strcmp(subNeg, "") == 0) && (strcmp(subPos, base) == 0));
}

/// Test with null string
/// \return
int test_$substr_6(){
    $ res = $substr(NULL, 7, 10);
    return strcmp(res, "") == 0;
}

#endif //SSTR_TEST_SUBSTR_H
