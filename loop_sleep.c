//
// Created by mih on 1/13/17.
//

#include "common.h"


void loop(long ns, double ns_iter) {
    long i, j;
    long n = (int)(ns/ns_iter);
    for (i = 0; i < n; i++){
        ++j;
    }
}

double calibrate() {
    const long N_CALIBRATE = 1000000000;
    struct timespec start, end;
    long delta1, delta2;
    clock_gettime(CLOCK_MONOTONIC, &start);
    loop(N_CALIBRATE,1);
    clock_gettime(CLOCK_MONOTONIC, &end);

    delta1 = delta_ns(start, end);
    clock_gettime(CLOCK_MONOTONIC, &start);
    loop(N_CALIBRATE*2,1);
    clock_gettime(CLOCK_MONOTONIC, &end);
    delta2 = delta_ns(start, end);
    return (delta2-delta1) / 1000000000.0;
}


int main(int argc, char **argv) {
    struct timespec start, end;

    long ns_interval  = atol(argv[1]);

    long num  = atol(argv[2]);


    int i;

    double ns_iter = calibrate();
    printf("ns_iter: %f\n", ns_iter);
    for (i = 0 ;i < num; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        loop(ns_interval, ns_iter);
        clock_gettime(CLOCK_MONOTONIC, &end);
        printf("actual interval: %li\n",delta_ns(start, end));
    }
    return EXIT_SUCCESS;
}