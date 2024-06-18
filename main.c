#include <stdio.h>

#include "sw.h"
#include "sstr.h"


int main()
{
    $ path = "C:\\users\\tobinc\\";

    $ other = $from$(path);

    printf("%s-%s\n", path, other);

    return 1;
}
