#!/usr/bin/python

import sys
import math
import random

class Hist(object):
    def __init__(self, min, max, n_buckets=None, bucket_int=None):
        if max <= min:
            raise ValueError("max <= min for hist")

        self.min = min
        self.max = max

        if n_buckets:
            self.n_bickets = n_buckets
            self.bucket_int = (max - min)/float(n_buckets)
        elif bucket_int:
            self.bucket_int = bucket_int
            self.n_buckets = int((max - min)/float(bucket_int))
            if self.n_buckets <= 1:
                raise ValueError("Too big bucket_int. 1 or 0 bucket in hist")

        self.buckets = [0] * self.n_buckets
        self.less = 0
        self.more = 0
        self.num = 0
        self.sum = 0
        self.sum_sqr = 0

    def add_value(self, val):
        self.num += 1
        self.sum += val
        self.sum_sqr += val**2

        if val > self.max:
            self.more += 1
        elif val < self.min:
            self.less += 1
        else:
            bucket = int((val - self.min)/self.bucket_int)
            self.buckets[bucket] += 1

    def avg(self):
        if self.num:
            return self.sum/self.num
        else:
            return None

    def sigma(self):
        if self.num > 1:
            sigma_sqr = self.sum_sqr/(self.num-1) - (self.avg()*self.num/(self.num-1))**2
            return math.sqrt(sigma_sqr)
        else:
            return None

    def iter_buckets(self):
        #yield ("#Less {0}:".format(self.min), self.less)
        for i, b in enumerate(self.buckets):
            yield (self.min + (i+1)*self.bucket_int, b)
        #yield ("#More {0}:".format(self.max), self.more)

    def pprint(self):
        print "# Number of values: {0}".format(self.num)
        print "# Avg: {0}".format(self.avg())
        print "# Sigma: {0}".format(self.sigma())
        print "# Histogram:"
        print "# Less {0}:".format(self.min), self.less
        for j, v in self.iter_buckets():
            print j, v
        print "# More {0}:".format(self.max), self.more

def test():
    h = Hist(0, 20, bucket_int=0.5)

    for i in range(10000):
        l = random.gauss(10,3)
        h.add_value(l)

    h.pprint()

if __name__ == "__main__":
    test()