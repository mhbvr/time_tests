// Compare ptp time and system time
// Created by mih on 10/26/16.
//

#include "time.h"
#include "stdio.h"
#include "fcntl.h"
#include <unistd.h>
#include <stdlib.h>


#define DEVICE "/dev/ptp0"

#define CLOCKFD 3
#define FD_TO_CLOCKID(fd)   ((~(clockid_t) (fd) << 3) | CLOCKFD)
#define CLOCKID_TO_FD(clk)  ((unsigned int) ~((clk) >> 3))
#define CLOCK_INVALID -1


clockid_t phc_open(char *phc)
{
	clockid_t clkid;
	int fd = open(phc, O_RDWR);

	if (fd < 0)
		return CLOCK_INVALID;
	clkid = FD_TO_CLOCKID(fd);
	return clkid;
}


void phc_close(clockid_t clkid)
{
	if (clkid == CLOCK_INVALID)
		return;

	close(CLOCKID_TO_FD(clkid));
}

long delta_ns(struct timespec begin, struct timespec end) {
    return (end.tv_sec - begin.tv_sec) * 1000000000 + end.tv_nsec - begin.tv_nsec;
}


int main(int argc, char **argv) {
    struct timespec sys_start, phc_start, sys_ts, phc_ts;
    clockid_t phc_clock;
    long i, n;

    if (argc < 2) {
        fprintf(stderr, "Set number of measurements");
        exit(EXIT_FAILURE);
    }
    n = atol(argv[1]);


    phc_clock = phc_open(DEVICE);
    if (clock_gettime(CLOCK_REALTIME, &sys_start))
        perror("clock_gettime() CLOCK_REALTIME");
    if (clock_gettime(phc_clock, &phc_start))
        perror("clock_gettime() phc device");

    for (i = 0; i < n; i++) {
        clock_gettime(CLOCK_REALTIME, &sys_ts);
        clock_gettime(phc_clock, &phc_ts);
        printf("%li %li\n", delta_ns(sys_start, sys_ts), delta_ns(phc_start, phc_ts));
    }
    exit(EXIT_SUCCESS);
}

