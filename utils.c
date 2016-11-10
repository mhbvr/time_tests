//
// Created by mih on 11/10/16.
//

#include "utils.h"


struct buffer *alloc_lin_storage(uint32_t len) {
    struct buffer *stor = (struct buffer *)malloc(sizeof(struct buffer));
    stor->len = len;
    stor->i = 0;
    stor->buff = (struct point *)malloc(sizeof(struct point)*len);
    memset(stor->buff, 0, sizeof(struct point)*len);
    return stor;
}


int8_t buffer_add_point(struct point *p, struct buffer *stor) {
    if (stor->i >= stor->len)
        return STORAGE_FULL;
    memcpy(stor->buff+stor->i, p, sizeof(struct point));
    ++stor->i;
    return OK;
}


struct hist *alloc_hist(uint32_t max_value, uint8_t log_int, uint32_t max_outliers) {
    struct hist *stor = (struct hist *)malloc(sizeof(struct hist));
    stor->log_int = log_int;
    stor->n_buckets = max_value/(1 << log_int);
    stor->buckets = (uint64_t *)malloc(sizeof(uint64_t)*stor->n_buckets);
    memset(stor->buckets, 0, sizeof(uint64_t)*stor->n_buckets);
    stor->max_outliers = max_outliers;
    stor->outliers = (struct point *)malloc(sizeof(struct point)*max_outliers);
    memset(stor->outliers, 0, sizeof(struct point)*max_outliers);
    stor->i_out = 0;
    stor->n_outliers = 0;
    stor->total = 0;
    stor->sum = 0;
    stor->sqr_sum = 0;
    return stor;
}


int8_t hist_add_point(struct point *p, struct hist *stor) {
    uint64_t i_buck = p->latency >> stor->log_int;
    ++stor->total;
    stor->sum += p->latency;
    stor->sqr_sum += p->latency*p->latency;
    if (i_buck < stor->n_buckets) {
        ++stor->buckets[i_buck];
    }
    else if (stor->i_out >= stor->max_outliers) {
        ++stor->n_outliers;
        return OUTLIERS_FULL;
    }
    else {
        memcpy(stor->outliers+stor->i_out, p, sizeof(struct point));
        ++stor->i_out;
        ++stor->n_outliers;
    }
    return OK;
}

uint64_t hist_avg(struct hist *stor) {
    if (stor->total>0)
        return stor->sum/stor->total;
    else
        return 0;
}

double hist_sigma(struct hist *stor) {
    if (stor->total>0)
        return sqrt(stor->sqr_sum/stor->total - ((stor->sum/stor->total)*(stor->sum/stor->total)));
    else
        return 0;
}