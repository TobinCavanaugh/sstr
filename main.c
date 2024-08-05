#include <stdio.h>
#include "sstr.h"
#include "test.h"
#include "benchmark.h"

int main() {


    test_all();
    printf("---\n");
    bench_all();

    return 0;
}
