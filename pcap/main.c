#include <stdio.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "pcap.h"

uint8_t buf[10240];

int main(int argc, char *argv[])
{
  uint32_t dst_ip, src_ip;
	uint32_t old = 0;
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
  memset(buf, 0, sizeof(buf));	
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
	uint16_t tmp_sum = 0;
  uint16_t tcp_len = 0, tcp_po = 6;
	size_t heirenwenhao;
	if((n = fread(buf, szbyte, pcap_file_header_size, fp)) == 0)
	{
		printf("Wrong file.\n");
		exit(0);
	}

	print_pcap_file_header((struct pcap_file_header_t *)buf);
	while((n = fread(buf, szbyte, pcap_header_size, fp)) > 0)
	{
    heirenwenhao = ((struct pcap_header_t *)buf)->caplen;
		print_pcap_header((struct pcap_header_t *)buf);

		if((n = fread(buf, szbyte, eth_header_size, fp)) == 0)
		{
			printf("Wrong file.\n");
			exit(0);
		}
		print_ether_header((struct etherframe_header_t *)buf);
		heirenwenhao -= 14;
		if((n = fread(buf, szbyte, ip_header_size, fp)) == 0)
		{
			printf("Wrong file.\n");
			exit(0);
		}
		printf("\nIPpack len : %d\n", ntohs(((struct ip_header_t *)buf)->len));
		tcp_len = ntohs(((struct ip_header_t *)buf)->len) - 20;
		heirenwenhao -= (tcp_len + 20);
		dst_ip = ((struct ip_header_t *)buf)->dst_ip;
	  src_ip = ((struct ip_header_t *)buf)->src_ip;

		print_ip_header((struct ip_header_t *)buf);
	    
		tmp_sum = ((struct ip_header_t *)buf)->check_sum;
		((struct ip_header_t *)buf)->check_sum = 0;
		printf("The IPpack check sum is :  0x%04x\n\n", ntohs(check_sum((uint16_t *)buf, ip_header_size, 0)));
		((struct ip_header_t *)buf)->check_sum = tmp_sum;

		if((n = fread(buf, szbyte, tcp_len, fp)) == 0)
		{
			printf("Wrong file.\n");
			exit(0);
		}
		print_tcp_header((struct tcp_header_t *)buf);

		old = 0;
		old += (dst_ip >> 16) + (dst_ip & 0xffff);
		old += (src_ip >> 16) + (src_ip & 0xffff);
		old += htons(tcp_po);
		old += htons(tcp_len);
		
	  tmp_sum = ((struct tcp_header_t *)buf)->check_sum;
	  ((struct tcp_header_t *)buf)->check_sum = 0;
		printf("The TCPpack check sum is :  0x%04x\n\n", ntohs(check_sum((uint16_t *)buf, n, old)));
		if(heirenwenhao)
		{
				fread(buf, szbyte, heirenwenhao, fp);
		}
	}
	fclose(fp);
	return 0;
}
