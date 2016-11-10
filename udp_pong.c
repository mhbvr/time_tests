// Ping on udp with timestamps
// Created by mih on 11/2/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "common.h"

#define BUFLEN 1024
#define PORT 8888




int main(int argc, char **argv) {

    /* Create socket and set options */
    int sock;

    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        die("socket()");
    }

    /* Set source address and port */
    struct sockaddr_in srv_addr, client_addr;
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(PORT);
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    socklen_t addr_len = sizeof(struct sockaddr_in);
    /* Bind socket */
    if( bind(sock, (struct sockaddr*)&srv_addr, sizeof(srv_addr) ) == -1) {
        die("bind()");
    }

    struct timestamp ts_data;

    /* Data receive loop */
    while(1) {
        recvfrom(sock, (void *)&ts_data, timesptamp_len, 0, (struct sockaddr *)&client_addr, &addr_len);
        //clock_gettime(CLOCK_REALTIME, &ts_data.echo);
        sendto(sock, (void *)&ts_data, timesptamp_len, 0, (struct sockaddr *)&client_addr, sizeof(struct sockaddr_in));
    }
    close(sock);
    return EXIT_SUCCESS;
}