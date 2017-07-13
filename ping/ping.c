#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include "ping.h"

int packsize, nsend = 0, nrecv = 0;

uint16_t check_sum(uint16_t *icmp_head, int len)
{
	uint32_t sum = 0;
	uint16_t *ptr = icmp_head;
	uint16_t answer = 0;
	while(len>1)
	{
		sum += *ptr;
		++ptr;
		len -= 2;
	}
	if(len == 1)
	{
		*(unsigned char *)(&answer) = *(unsigned char *)ptr;
		sum += answer;
	}
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;
	return answer;
}

void print_head(char *ip)
{
	packsize = sizeof(struct icmp) + sizeof(struct timeval);
	printf("Ping %s with  %d bytes of data.\n", ip, packsize);
}

void send_ping(int sockfd, struct sockaddr_in *addr)
{
	char buf[128];
	socklen_t addrlen = sizeof(struct sockaddr_in);
	struct icmp *echo;
	memset(buf, 0, sizeof(buf));
	echo = (struct icmp *)buf;
	echo->icmp_type = 8;
	echo->icmp_code = 0;
	echo->icmp_cksum = 0;
	echo->icmp_id = getpid();
	echo->icmp_seq = nsend;
	struct timeval *tval = (struct timeval *)echo->icmp_data;
	gettimeofday(tval, NULL);
	echo->icmp_cksum = check_sum((uint16_t *)echo, packsize);

	if(sendto(sockfd, buf, sizeof(struct icmp), 0,	(struct sockaddr *)addr, addrlen) < 0)
	{
		printf("Send ping fail.");
		return ;
	}
	++ nsend;
}

void recv_ping(int sockfd, struct sockaddr_in *addr)
{
	// 
	char buf[128];
	struct ip *ip;
	struct icmp *icmp;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	ssize_t n;
	int ttl, maxfd = sockfd + 1, time;
	struct timeval timeo, *tvsend, tvrecv;
	fd_set rset;
	unsigned char *p, ipaddr[128];
	memset(buf, 0, sizeof(buf));
	timeo.tv_sec = 3;
	timeo.tv_usec = 0;
	
	FD_ZERO(&rset);
	FD_SET(sockfd, &rset);

	while(1)
	{
		if((n = select(maxfd, &rset, NULL, NULL, &timeo)) == -1)
		{
			printf("Select Error!\n");
			exit(1);
		}
		if(n <= 0)
		{
			printf("Request Time Out!\n");
			fflush(stdout);
			break;
		}

		if((n = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)addr, &addrlen)) == -1)
			printf("Recv Ping Message Error!\n");
		
		gettimeofday(&tvrecv, NULL);
		ip = (struct ip *)buf;
		ttl = ip->ip_ttl;

		p = (unsigned char *)&ip->ip_src;
		sprintf(ipaddr, "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);

		if(strcmp(ipaddr, "127.0.0.1") == 0)
			continue;
		if(ip->ip_p != IPPROTO_ICMP)
			continue;

		icmp = (struct icmp *)(buf + sizeof(struct ip));
		if(icmp->icmp_type == ICMP_ECHOREPLY)
		{
			if(icmp->icmp_id == getpid())
			{
				tvsend = (struct timeval *)icmp->icmp_data;
				tv_sub(&tvrecv, tvsend);
				time = tvrecv.tv_sec * 1000 + tvrecv.tv_usec / 1000;
				++ nrecv;
				printf("Reply %d bytes from %s, time = %d ms, TTL = %d, icmp_seq = %d\n", packsize, ipaddr, time,ttl, nsend);
				break;
			}
			else continue;
		}
		else continue;

	
	}
}

void tv_sub(struct timeval *tvrecv, struct timeval *tvsend)
{
	if(tvrecv->tv_usec < tvsend->tv_usec)
	{
		-- tvrecv->tv_sec;
		tvrecv->tv_usec += 1000*1000;
	}
	tvrecv->tv_sec -= tvsend->tv_sec;
	tvrecv->tv_usec -= tvsend->tv_usec;
}
void ping(char *ip)
{
	int sockfd = -1, times = 0;
	struct sockaddr_in dstaddr;
	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

	if(sockfd == -1)
	{
		printf("sockd fail.\n");
		exit(0);
	}
//	memset(dstaddr, 0, sizeof(struct sockaddr_in));
	dstaddr.sin_family = AF_INET;
	dstaddr.sin_port = htons(0);
	
	if(inet_pton(AF_INET, ip, &dstaddr.sin_addr) == -1)
	{
		printf("GET IP fail.");
		exit(0);
	}
	print_head(ip);	
	while(times < PINGNUMS)
	{
		send_ping(sockfd, &dstaddr);
		recv_ping(sockfd, &dstaddr);
		times ++;
	}

}
