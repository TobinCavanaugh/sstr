//
// Created by tobin on 2024-08-04.
//

#ifndef  SSTR_BENCHMARK_H
#define  SSTRBENCHMARK_H

#include "sstr.h"
#include "sw.h"

#define BENCHMARK_ITERATIONS 1000
//#define BENCHMARK_ITERATIONS 1

void bench_$append() {

    char *base = "Object-oriented programming is an exceptionally bad idea which could only have originated in California.";
    char *app = " - Edsger Dijkstra";

    /*sstr.h benchmark*/
    {
        double sstr_us = sw_start_us();

        int i = 0;
        for (; i < BENCHMARK_ITERATIONS; i++) {
            $begin(__)
                volatile $ a = base;
                a = $append(base, app);
            $end(__)
        }

        sstr_us = sw_stop_us(sstr_us);
        printf("$append @ %d iterations: %fus\n", BENCHMARK_ITERATIONS, sstr_us);
    }

    /*C heap benchmark*/
    {
        double c_us = sw_start_us();

        int i = 0;
        for (; i < BENCHMARK_ITERATIONS; i++) {
            int baseLen = strlen(base);
            int appLen = strlen(app);

            char *s = halloc(baseLen + 1);
            strcpy(s, base);

            s = realloc(s, baseLen + appLen + 1);
            strcpy(s + baseLen, app);

//            printf("(%s)", s);

            hfree(s);
        }


        c_us = sw_stop_us(c_us);
        printf("heap @ %d iterations:    %fus\n", BENCHMARK_ITERATIONS, c_us);
    }

    /*C fixed buffer benchmark*/
    {
        double cs_us = sw_start_us();

        int i = 0;
        for (; i < BENCHMARK_ITERATIONS; i++) {
            volatile char s[128];
            strcpy(s, base);
            strcpy(s + strlen(base), app);
//            printf("(%s)", s);
        }

        cs_us = sw_stop_us(cs_us);
        printf("array @ %d iterations:   %fus\n", BENCHMARK_ITERATIONS, cs_us);
    }
}

void bench_all() {
    bench_$append();
}


#endif //SSTR_BENCHMARK_H
