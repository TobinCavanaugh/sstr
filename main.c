#include <stdio.h>
#include "sstr.h"
#include "sw.h"

void PrintThing(int x, float y, $ z) {
    $ str = $from_fmt("%d, %f, %s", x, y, z);

    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    //Get the timestamp
    $ working = $from_fmt("%s", asctime(timeinfo));

    //Remove newline at the end
    working[strlen(working) - 1] = '\0';

    //Append our values string
    working = $append(working, str);

    //Insert a pipe character between the two strings
    working = $insert(working, strlen(working), " | ");

//    printf("%s", working);
}

int main() {
    double us = sw_start_us();


    int i = 1000000;
    for (; i >= 0; i--) {
        PrintThing(100, .5f, "String");
    }

//    int i = 5;
//    for (; i >= 0; i--) {
//        $begin(a)
//            $ a = $from_fmt("%d", i);
//            printf("%s\n", a);
//        $end(a)
//    }

    sw_print_us(us);

    return 0;
}
