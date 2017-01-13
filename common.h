//
// Created by mih on 11/3/16.
//

#ifndef TIME_TESTS_COMMON_H
#define TIME_TESTS_COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Struct to measure communication time */
struct timestamp {
    struct timespec send;
    struct timespec echo;
};

const size_t timesptamp_len = sizeof(struct timestamp);

void die(char *s) {
    perror(s);
    exit(EXIT_FAILURE);
}

static inline long delta_ns(struct timespec begin, struct timespec end) {
    return (end.tv_sec - begin.tv_sec) * 1000000000 + end.tv_nsec - begin.tv_nsec;
}

#endif //TIME_TESTS_COMMON_H
