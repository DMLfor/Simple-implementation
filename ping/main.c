#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ping.h"
char ip[100];
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("./ping ip.");
		exit(0);
	}
	strncpy(ip, argv[1], strlen(argv[1]));
	ping(ip);

	return 0;
}

