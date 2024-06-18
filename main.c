#include <stdio.h>

#include "sw.h"
#include "sstr.h"

int main() {

    $ path = "C:\\users\\tobinc\\";

    path = $insert(path, 0, "test\\");

    printf("%s\n", path);

    return 1;
}
