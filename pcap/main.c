#include <stdio.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <unistd.h>
#include "pcap.h"
uint8_t buf[10240];
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("file name.");
		exit(0);
	}
	FILE *fp = NULL;
	fp = fopen(argv[1], "rb");
	if(fp == NULL)
	{
		printf("file open fail.");
		exit(0);
	}
	
	struct pcap_file_header_t *pcap_file_header;
	struct pcap_header_t *pcap_header;
	struct etherframe_header_t *etherframe_header;
	struct ip_header_t *ip_header;
	struct tcp_header_t *tcp_header;
	size_t n, szbyte = sizeof(uint8_t);
	size_t pcap_file_header_size = sizeof(struct pcap_file_header_t),
		   pcap_header_size = sizeof(struct pcap_header_t),
		   ip_header_size = sizeof(struct ip_header_t),
		   tcp_header_size = sizeof(struct tcp_header_t),
		   eth_header_size = sizeof(struct etherframe_header_t);
	int16_t tmp_sum = 0;

	if((n = fread(buf, szbyte, pcap_file_header_size, fp) == 0))
	{
		printf("Wrong file.\n");
		exit(0);
	}	
	print_pcap_file_header((struct pcap_file_header_t *)buf);
	
	if((n = fread(buf, szbyte, pcap_header_size, fp) == 0))
	{
		printf("Wrong file.\n");
		exit(0);
	}
	print_pcap_header((struct pcap_header_t *)buf);

	if((n = fread(buf, szbyte, eth_header_size, fp) == 0))
	{
		printf("Wrong file.\n");
		exit(0);
	}
	print_ether_header((struct etherframe_header_t *)buf);

	if((n = fread(buf, szbyte, ip_header_size, fp) == 0))
	{
		printf("Wrong file.\n");
		exit(0);
	}
	print_ip_header((struct ip_header_t *)buf);
	
	tmp_sum = ((struct ip_header_t *)buf)->check_sum;
	((struct ip_header_t *)buf)->check_sum = 0;
	printf("The IPpack check sum is :  0x%04x\n\n", ntohs(check_sum((uint16_t *)buf, ip_header_size)));
	((struct ip_header_t *)buf)->check_sum = tmp_sum;
	if((n = fread(buf, szbyte, tcp_header_size, fp) == 0))
	{
		printf("Wrong file.\n");
		exit(0);
	}
	print_tcp_header((struct tcp_header_t *)buf);
	
	fclose(fp);
	return 0;
}
