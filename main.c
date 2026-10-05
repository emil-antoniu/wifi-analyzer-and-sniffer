#include <stdio.h>
#include <pcap.h>

int main(int argc, char *argv[])
{
	char errbuf[PCAP_ERRBUF_SIZE];
	char *dev = argv[1];

	printf("Device: %s\n", dev);
    
	return(0);
}