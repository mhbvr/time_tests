// Test resolution on clock_gettime
// Created by mih on 10/25/16.
//

#include "time.h"
#include "stdlib.h"
#include "stdio.h"


long delta_ns(struct timespec begin, struct timespec end) {
    return (end.tv_sec - begin.tv_sec) * 1000000000 + end.tv_nsec - begin.tv_nsec;
}


void histogram(int buckets, long bucket_int, long *data, long n) {
    long* hist = (long *)malloc((buckets+1)*sizeof(long));
    long i;

    for (i = 0; i < n; i++) {
        long bu
        if (data[i]/bucket_int > buckets-1) {
        }
    }
}


int main(int argc, char **argv) {
    struct timespec start, end;
    long n = atol(argv[1]);
    int i;

    for (i = 0 ;i < n; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &end);
        printf("delta: %li\n",delta_ns(start, end));
    }
    return EXIT_SUCCESS;
}
