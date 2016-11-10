//
// Created by mih on 11/10/16.
//

#ifndef TIME_TESTS_UTILS_H
#define TIME_TESTS_UTILS_H

#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define OK             0
#define STORAGE_FULL  -1
#define OUTLIERS_FULL -2

static inline uint64_t delta_ns(struct timespec begin, struct timespec end) {
    return (end.tv_sec - begin.tv_sec) * 1000000000 + end.tv_nsec - begin.tv_nsec;
}


struct point {
    struct timespec ts;
    uint64_t latency;
};

struct buffer {
    struct point *buff;
    uint32_t len;
    uint32_t i;
};

struct hist {
    uint64_t *buckets;
    uint32_t n_buckets;
    uint8_t log_int;
    struct point *outliers;
    uint32_t n_outliers;
    uint32_t max_outliers;
    uint32_t i_out;
    uint64_t total;
    uint64_t sum;
    uint64_t sqr_sum;
};


struct buffer *alloc_lin_storage(uint32_t);
int8_t buffer_add_point(struct point *, struct buffer *);
struct hist *alloc_hist(uint32_t, uint8_t, uint32_t);
int8_t hist_add_point(struct point *, struct hist *);
uint64_t hist_avg(struct hist *);
double hist_sigma(struct hist *);
#endif //TIME_TESTS_UTILS_H
