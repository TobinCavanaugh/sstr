#include <stdio.h>
#include "sstr.h"
#include "sw.h"

void *PrintThing(int x, float y, $ z) {
    $ str = $from_fmt("%d, %f, %s", x, y, z);

    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    //Get the timestamp
    $ working = $from_fmt("%s", asctime(timeinfo));

    //Remove newline at the end
    working[strlen(working) - 1] = '\0';

    //Insert a pipe character between the two strings
    working = $insert(working, strlen(working), " | ");

    //Append our values string
    working = $append(working, str);

    return $realize(working);
}

int main() {

    $ tmp = $from("");
    tmp = $append($append($append(tmp, "-"), "-"), "-");
    tmp = $append_fmt($append_fmt(tmp, "%d", -1), "%d", -1);
    tmp = $insert($insert(tmp, 0, "[O]"), 0, "[O]");

    tmp = $substr($substr(tmp, 0, 4), 0, 5);
    printf("%s\n", tmp);

    return 1;

    char *res = $realize(tmp);
    tmp = $stackify(res);

    printf("%s\n", tmp);

    int i = 10;
    for (; i >= 0; i--) {
        char *res = PrintThing(100, .5f, "String");
        printf("%s\n", res);
        free(res);
    }

//    int i = 5;
//    for (; i >= 0; i--) {
//        $begin(a)
//            $ a = $from_fmt("%d", i);
//            printf("%s\n", a);
//        $end(a)
//    }


    return 0;
}
