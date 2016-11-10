// Ping on udp with timestamps
// Created by mih on 11/2/16.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#include "common.h"

#define BUFLEN 1024
#define PORT 8888


int main(int argc, char **argv) {

    char *to = argv[optind];
    char *to_port = argv[optind + 1];

    struct timestamp ts_data;
    struct timespec recv_ts;

    /* Create socket and set options */
    int sock;

    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        die("socket()");
    }

    /* Set address INADDR_ANY and port */
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = 0;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    /* Bind socket */
    if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        die("bind()");
    }

    /* Get server ADDR */
    struct addrinfo hints;
    struct addrinfo *dst;
    int res;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = 0;
    hints.ai_protocol = IPPROTO_UDP;

    res = getaddrinfo(to, to_port, &hints, &dst);
    if (res != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res));
        exit(EXIT_FAILURE);
    }


    /* Sending data */
    printf("Sending data...\n");
    fflush(stdout);
    size_t len = sizeof(struct timestamp);
    int i;
    long delta[30];
    for (i=0; i < 30; i++) {
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts_data.send);
        sendto(sock, (void *) &ts_data, len, 0, (const struct sockaddr *) dst->ai_addr, sizeof(struct sockaddr));
        recv(sock, (void *) &ts_data, len, 0);
        clock_gettime(CLOCK_MONOTONIC_RAW, &recv_ts);
        delta[i] = delta_ns(ts_data.send, recv_ts);
    }
    for (i=0; i < 30; i++) {
        printf("A->B: 0 B->A: 0, A->B->A: %li\n", delta[i]);
        //printf("A->B: %li B->A: %li, A->B->A: %li\n", delta_ns(ts_data.send, ts_data.echo), delta_ns(ts_data.echo, recv_ts),delta_ns(ts_data.send, recv_ts));
    }
    close(sock);
    return EXIT_SUCCESS;
}