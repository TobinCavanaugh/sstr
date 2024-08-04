//
// Created by tobin on 2024-08-04.
//

#ifndef SSTR_TEST_FROM_H
#define SSTR_TEST_FROM_H

/// Basic functionality test
/// \return
int test_$from_0() {
    $ s = $from("Hello Cruel World");
    return strcmp("Hello Cruel World", s) == 0;
}

/// From null test
/// \return
int test_$from_1() {
    $ s = $from(NULL);
    return strcmp("", s) == 0;
}

/// From nothing test
/// \return
int test_$from_2() {
    $ s = $from("");
    return strcmp("", s) == 0;
}

/// From a heap string test
/// \return
int test_$from_3() {
    char *tmp = "A foolish consistency is the hobgoblin of little minds, adored by little statesmen and philosophers and divines";
    char *x = malloc(strlen(tmp) + 1);
    strcpy(x, tmp);

    $ s = $from(x);
    free(x);
    return strcmp(s, tmp) == 0;
}

#endif//SSTR_TEST_FROM_H
