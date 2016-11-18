//
// Created by mih on 11/11/16.
//


#include <random>
#include <iostream>
#include "stat.h"


class Point {
public:
    Point(struct timespec timestamp, uint64_t value):
            timestamp(timestamp),
            value(value) {}
    Point() = default;

    struct timespec timestamp;
    uint64_t value;
};


class LatHist {
    uint64_t max_hist_value;
    uint8_t log_interval;
    uint64_t max_outliers;
    uint64_t max_buckets;
    uint64_t sum = 0;
    uint64_t sqr_sum = 0;
    std::vector<uint64_t> buckets;
    std::vector<Point> outliers;

public:
    LatHist(uint32_t max_hist_value, uint8_t log_interval, uint32_t max_outliers):
            max_hist_value(max_hist_value),
            log_interval(log_interval),
            max_outliers(max_outliers),
            max_buckets(max_hist_value/(1 << log_interval)),
            buckets(max_buckets, 0),
            outliers(max_outliers) {}
    uint64_t min_value = 0;
    uint64_t max_value = 0;
    uint64_t tot_points = 0;
    uint64_t tot_outliers = 0;

    void add_value(uint64_t value){
        struct timespec timestamp;
        int err;
        err = clock_gettime(CLOCK_REALTIME, &timestamp);
        if (err < 0) {
            perror("clock_gettime()");
            return;
        }
        add_value(value, timestamp);
    }

    void add_value(uint64_t value, struct timespec timestamp){
        uint64_t bucket;

        ++tot_points;
        sum += value;
        sqr_sum += value*value;
        if (value>max_value) {
            max_value = value;
        }

        if (value < min_value) {
            min_value = value;
        }

        if (value > max_hist_value) {
            if (tot_outliers < max_outliers) {
                outliers[tot_outliers] = (Point(timestamp, value));
            }
            ++tot_outliers;
        } else {
            bucket = value/(1 << log_interval);
            ++buckets[bucket];
        }
    }

    double avg() {
        if (tot_points > 0){
            return sum/tot_points;
        } else {
            return 0;
        }
    }

    double sigma() {
        if (tot_points > 1){
            return std::sqrt(sqr_sum/(tot_points-1) - (sum/(tot_points-1))*(sum/(tot_points-1)));
        } else {
            return 0;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, LatHist &hist) {
        uint64_t n = 0;
        Point p;
        os << "# Number of points: " << hist.tot_points << std::endl;
        os << "# Max value: " << hist.max_value << std::endl;
        os << "# Min value: " << hist.min_value << std::endl;
        os << "# Average: " << hist.avg() << std::endl;
        os << "# Sigma: " << hist.sigma() << std::endl;
        os << "# Number of outliers (>" << hist.max_buckets*(1 << hist.log_interval) << "): " << hist.tot_outliers << std::endl;
        os << "# Histogram:" << std::endl;
        for (uint64_t val : hist.buckets) {
            os << n * (1 << hist.log_interval) << " " << (n + 1) * (1 << hist.log_interval) << " " << val << std::endl;
            ++n;
        }
        os << "# Outliers:" << std::endl;
        for (uint64_t i = 0; i < hist.tot_outliers; i++) {
            p = hist.outliers[i];
            os << p.timestamp.tv_sec * 1000000000 +  p.timestamp.tv_nsec << " " << p.value << std::endl;
        }
        return os;
    }

};


int main(int argv, char**argc) {
    int i;
    struct timespec start, end, tmp;

    LatHist hist(1000, 3, 1000);

    for(i=0; i<1000000; i++) {
        tmp = start;
        clock_gettime(CLOCK_REALTIME, &start);
        if (i > 0)
            hist.add_value(delta_ns(tmp, end), start);
        clock_gettime(CLOCK_REALTIME, &end);
    }
    std::cout << hist;

}