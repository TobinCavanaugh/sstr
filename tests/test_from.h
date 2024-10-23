//
// Created by tobin on 2024-08-04.
//

#ifndef SSTR_TEST_FROM_H
#define SSTR_TEST_FROM_H

/// Basic functionality test
/// \return
int test_$from_0() {
    $ s = $from("Hello Cruel World");
    return str_cmp("Hello Cruel World", s) == 0;
}

/// From null test
/// \return
int test_$from_1() {
    $ s = $from(NULL);
    return str_cmp("", s) == 0;
}

/// From nothing test
/// \return
int test_$from_2() {
    $ s = $from("");
    return str_cmp("", s) == 0;
}

/// From a heap string test
/// \return
int test_$from_3() {
    char* tmp =
        "A foolish consistency is the hobgoblin of little minds, adored by little statesmen and philosophers and divines";
    char* x = halloc(str_len(tmp) + 1);
    str_copy(x, tmp);

    $ s = $from(x);
    hfree(x);
    return str_cmp(s, tmp) == 0;
}

#endif//SSTR_TEST_FROM_H
