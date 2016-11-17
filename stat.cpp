//
// Created by mih on 11/11/16.
//

#include <time.h>
#include "stat.h"


class Histrogram {
    uint64_t tot_points;
    uint32_t max_buckets;
    uint32_t max_outliers;
    uint8_t log_interval;
    uint32_t tot_outliers;
    uint32_t i_outlier;
    uint64_t sum;
    uint64_t sqr_sum;
    uint64_t *buckets;
    uint64_t *outliers;

public:
    void add_value(uint64_t value){

    }

    void add_value(uint64_t value, str  uct timespec timestamp){

    }
};

int main(int argv, char**argc) {
    return 0;
}