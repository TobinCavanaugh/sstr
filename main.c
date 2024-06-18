#include <stdio.h>
#include "sstr.h"
#include "sw.h"

#define $begin(a) int __run_ ## a(){

#define $end(a) } __run_ ## a ();

int main()
{
    double us = sw_start_us();

    int i = 100000;
    for (; i >= 0; i--)
    {
        $begin(a)
            $ a = $from("Hello");
            a = $append(a, " World!");
        $end(a)
    }

    sw_print_us(us);

    return 0;
}
