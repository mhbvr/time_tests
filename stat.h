//
// Created by mih on 11/11/16.
//

#ifndef TIME_TESTS_STAT_H
#define TIME_TESTS_STAT_H

#include <stdint.h>
#include <time.h>
#include <cstdio>
#include <cmath>
#include <vector>

static inline long delta_ns(struct timespec begin, struct timespec end) {
    return (end.tv_sec - begin.tv_sec) * 1000000000 + end.tv_nsec - begin.tv_nsec;
}
#endif //TIME_TESTS_STAT_H
