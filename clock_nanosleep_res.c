//
// Created by mih on 1/13/17.
//

#include "common.h"


int main(int argc, char **argv) {
    struct timespec start, end, interval;

    long ns_interval  = atol(argv[1]);
    interval.tv_nsec = ns_interval;

    int num  = atol(argv[2]);
    interval.tv_nsec = ns_interval;

    int i;

    for (i = 0 ;i < num; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        clock_nanosleep(CLOCK_MONOTONIC, 0, &interval, NULL);
        clock_gettime(CLOCK_MONOTONIC, &end);
        printf("actual interval: %li\n",delta_ns(start, end));
    }
    return EXIT_SUCCESS;
}
