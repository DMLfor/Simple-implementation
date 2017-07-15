#ifndef _PCAP_H_
#define _PCAP_H_
#include <stdio.h>
#include <sys/time.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
//size_t fwrite(const void* buffer, size_t size, size_t count, FILE* stream);  
//-- buffer:指向数据块的指针  
//-- size:每个数据的大小，单位为Byte(例如：sizeof(int)就是4)  
//-- count:数据个数  
//-- stream:文件指针  

//size_t fread(void *buffer, size_t size, size_t count, FILE *stream); 
//size_t fread(void *buffer, size_t size, size_t count, FILE *stream);  
//-- buffer:指向数据块的指针  
//-- size:每个数据的大小，单位为Byte(例如：sizeof(int)就是4)  
//-- count:数据个数  
//-- stream:文件指针  

struct pcap_file_header_t
{
	uint32_t Magic;
	uint16_t Major;
	uint16_t Minor;
	uint32_t ThisZone; //time zone
	uint32_t SigFigs;
	uint32_t SnapLen;
	uint32_t LinkType;
};

struct my_timeval
{
	uint32_t tv_sec;
	uint32_t tv_usec;
};

struct pcap_header_t
{
	struct my_timeval tval;
	uint32_t caplen;
	uint32_t len;
};

struct etherframe_header_t
{
	uint8_t  dstaddr[6];
	uint8_t  srcaddr[6];
	uint16_t type;
};

struct fcs_t
{
	uint32_t fcs;
};

struct ip_header_t
{
	uint8_t version_and_header_len;
	uint8_t tos;
	uint16_t len;
	uint16_t pack_id;
	uint16_t slice_info;
	uint8_t ttl;
	uint8_t protocol;
	uint16_t check_sum;
	uint32_t src_ip;
	uint32_t dst_ip;
};

struct tcp_header_t
{
	uint16_t src_port;
	uint16_t dsr_port;
	uint32_t seq;
	uint32_t ack;
	uint16_t header_len_and_flags;
	uint16_t window_size;
	uint16_t check_sum;
	uint16_t surgent_point;
};

void print_pcap_file_header(struct pcap_file_header_t *pcap_file_header);

void print_pcap_header(struct pcap_header_t *pcap_header_t);

void print_ether_header(struct etherframe_header_t *etherframe_header);

void print_ip_header(struct ip_header_t *ip_header);

void print_tcp_header(struct tcp_header_t *tcp_header);

void num2protocol(int num);

void my_ntoa(uint32_t ipaddr, char *str_ip);

uint16_t check_sum(uint16_t *ptr, size_t len);
#endif
