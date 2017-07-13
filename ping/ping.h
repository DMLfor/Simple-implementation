#ifndef _PING_
#define _PING_
#include <netinet/in.h>
#define PINGNUMS 10

void print_head(char *ip);

void send_ping(int sockfd, struct sockaddr_in *addr);

void recv_ping(int sockfd, struct sockaddr_in *addr);

uint16_t check_sum(uint16_t *icmp_head, int len);

void ping(char *ip);

void tv_sub(struct timeval * tvrecv, struct timeval * tvsend);

char *host_to_ip(const char *hostname);
#endif


