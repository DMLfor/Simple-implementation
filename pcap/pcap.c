#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/ip.h>
#include "pcap.h"

void num2protocol(int num)
{
	if(num == 6)
	{
		printf("TCP\n");
	}
	else printf("other\n");
}

void my_ntoa(uint32_t ipaddr, char *str_ip)
{
	unsigned char tmp[4];
	uint32_t getbyte = 0xff000000;
	int numbyte, i;
	for(i = 3; i>=1; i--)
	{
		numbyte = (ipaddr & getbyte) >>(8*i);
		sprintf(tmp, "%d.", numbyte);
		strcat(str_ip, tmp);
		getbyte >>= 8;
	}
	numbyte = (ipaddr & getbyte) >>(8*i);
	sprintf(tmp, "%d", numbyte);
	strcat(str_ip, tmp);
	getbyte >>= 8;	
}
uint16_t check_sum(uint16_t *ptr, size_t len, uint32_t old)
{
	uint32_t sum = 0;
	uint16_t answer = 0;
	uint16_t *tmpptr = ptr;
	sum += old;
	while(len >= 1)
	{
		sum += *tmpptr;
		++ tmpptr;
		len -= 2;
	}
	if(len)
		*(uint8_t *)(&answer) = *(int8_t *)tmpptr;

	sum = (sum >> 16) + (sum & 0xffff);
	sum += sum >> 16;
	answer = ~sum;
	return answer;
}
void print_pcap_file_header(struct pcap_file_header_t *pcap_file_header)
{
	printf("Magic : 0x%08x\nMajor : 0x%04x\nMinor : 0x%04x\nThisZone : 0x%08x\nSigFigs ：0x%08x\nSapLen : 0x%08x\nLinkType : 0x%08x\n\n",
			pcap_file_header->Magic,
			pcap_file_header->Major,
			pcap_file_header->Minor,
			pcap_file_header->ThisZone,
			pcap_file_header->SigFigs,
			pcap_file_header->SnapLen,
			pcap_file_header->LinkType);

}

void print_pcap_header(struct pcap_header_t *pcap_header)
{
	printf("time : %u\ncaplen : %u\nlen : %u\n\n",pcap_header->tval.tv_sec, pcap_header->caplen, pcap_header->len);

}
//htonl
//htons
void print_ip_header(struct ip_header_t *ip_header)
{
	char str_ip[20];
	printf("IP version : %u\n", ip_header->version_and_header_len>>4);
	printf("IP header_len : %u\n", ip_header->version_and_header_len & 0xf);
	printf("IP diff serciece: 0x%02x\n", ip_header->tos);
	printf("IP package len : %u\n", htons(ip_header->len));
	printf("IP ident : %u\n", htons(ip_header->pack_id));
	printf("IP flags : 0x%02x\n", htons(ip_header->slice_info)>>13);
	printf("IP offset : %u\n", htons(ip_header->slice_info) & 0x3ff);
	printf("IP ttl : %u\n", ip_header->ttl);
	printf("IP protocol : "), num2protocol(ip_header->protocol);
	printf("IP checksum : 0x%04x\n", htons(ip_header->check_sum));
  memset(str_ip, 0, sizeof(str_ip));
	my_ntoa(htonl(ip_header->src_ip), str_ip);
  printf("IP src ip : %s\n", str_ip);
	memset(str_ip, 0, sizeof(str_ip));
	my_ntoa(htonl(ip_header->dst_ip), str_ip);
	printf("IP dst ip : %s\n\n", str_ip);
}

void print_ether_header(struct etherframe_header_t * etherframe_header)
{
	int i = 0;
	printf("ETH dst macIP :");
	for(i = 0; i<6; i++)
	{
		printf("%02x", etherframe_header->dstaddr[i]);
		if(i != 5)
			printf(":");
		else printf("\n");
	}

	printf("ETH src macIP :");
	for(i = 0; i<6; i++)
	{
		printf("%02x", etherframe_header->srcaddr[i]);
		if(i != 5)
			printf(":");
		else printf("\n");
	}

	printf("ETH type :%02x\n\n", etherframe_header->type);

}
void print_tcp_header(struct tcp_header_t *tcp_header)
{
	printf("TCP src port : %u\n", htons(tcp_header->src_port));
	printf("TCP dst prot : %u\n", htons(tcp_header->dsr_port));
	printf("TCP seq : %u\n", htonl(tcp_header->seq));
	printf("TCP ack : %u\n", htonl(tcp_header->ack));
	printf("TCP header len : %d\n", htons(tcp_header->header_len_and_flags)>>13);
	printf("TCP flags : 0x%03x\n", htons(tcp_header->header_len_and_flags) & 0x7f);
	printf("TCP window size : %u\n", htons(tcp_header->window_size));
	printf("TCP check sum: 0x%04x\n", htons(tcp_header->check_sum));
	printf("TCP surgent point: %x\n\n", htons(tcp_header->surgent_point));
}
