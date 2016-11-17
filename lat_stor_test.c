//
// Created by mih on 11/10/16.
//

#include "utils.h"
#include <math.h>
#include <stdio.h>


void baseline_test(uint32_t n) {
    struct timespec start, end;
    uint32_t i;

    uint64_t sum = 0;
    uint64_t sqr_sum = 0;

    for (i = 0 ;i < n; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &end);
        sum += delta_ns(start, end);
        sqr_sum += (delta_ns(start, end)*delta_ns(start, end));
    }
    printf("# Baseline test for time interval resolution\n");
    printf("# Avg: %li\n",sum/n);
    printf("# Sigma: %f\n",sqrt(sqr_sum/n - ((sum/n)*(sum/n))));
}


void buffer_test(uint32_t n) {
    struct timespec start, end;
    uint32_t i;

    uint64_t sum = 0;
    uint64_t sqr_sum = 0;
    struct buffer *buff = alloc_lin_storage(n);
    struct point p;

    for (i = 0 ;i < n; i++) {
        p.ts = start;
        p.latency = delta_ns(start, end);
        clock_gettime(CLOCK_MONOTONIC, &start);
        buffer_add_point(&p, buff);
        clock_gettime(CLOCK_MONOTONIC, &end);
        sum += delta_ns(start, end);
        sqr_sum += delta_ns(start, end)*delta_ns(start, end);
    }
    printf("# Time interval resolution with linear buffer storage\n");
    printf("# Avg: %li\n",sum/n);
    printf("# Sigma: %f\n",sqrt(sqr_sum/n - ((sum/n)*(sum/n))));
}


void hist_test(uint32_t n) {
    struct timespec start, end;
    uint32_t i;

    uint64_t sum = 0;
    uint64_t sqr_sum = 0;
    struct hist *hist = alloc_hist(100, 1, 1000);
    struct point p;

    for (i = 0 ;i < n; i++) {
        p.ts = start;
        p.latency = delta_ns(start, end);
        clock_gettime(CLOCK_MONOTONIC, &start);
        hist_add_point(&p, hist);
        clock_gettime(CLOCK_MONOTONIC, &end);
        sum += delta_ns(start, end);
        sqr_sum += delta_ns(start, end)*delta_ns(start, end);
    }
    printf("# Time interval resolution with histogram storage\n");
    printf("# Avg: %li\n",sum/n);
    printf("# Sigma: %f\n",sqrt(sqr_sum/n - ((sum/n)*(sum/n))));
    printf("# Hist avg: %li\n", hist_avg(hist));
    printf("# Hist sigma: %f\n", hist_sigma(hist));
    printf("# # of outliers: %i\n", hist->n_outliers);
}


int main(int argc, char **argv) {
    long n = atol(argv[1]);

    baseline_test(n);
    buffer_test(n);
    hist_test(n);
    return EXIT_SUCCESS;
}