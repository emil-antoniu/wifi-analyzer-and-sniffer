#include <stdio.h>
#include <pcap.h>

int main(int argc, char *argv[])
{
	char *dev, errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs;
    pcap_findalldevs(&alldevs, errbuf);

	if (alldevs == NULL) {
		fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
		return(2);
	}

	printf("Device: %s\n", (*alldevs->next).name);
    
	return(0);
}