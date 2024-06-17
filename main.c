#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stdint.h>

#include "sw.h"
#include "sstr.h"

int main() {

    $ path = "C:\\users\\tobinc\\";

    path = $append_fmt(path, "%d-%d-%s", 100, 50, "--");
    path = $append_fmt(path, "%d-%d", 10, 10);

    printf("%s\n", path);

    path = $substr(path, 0, 12);

    printf("%s\n", path);

    return 1;
}
