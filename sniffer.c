#include <stdio.h>
#include <pcap.h>

int main(int argc, char *argv[])
{
	char errbuf[PCAP_ERRBUF_SIZE];
	char *dev = argv[1];

	printf("Device: %s\n", dev);
    
	pcap_t *handle;

	handle = pcap_open_live(dev, BUFSIZ, 0, 1000, errbuf);
	if (handle == NULL) {
		fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
		return(2);
	}

	printf("Layer 2 header: %i\n", pcap_datalink(handle)); // 127

	const u_char *packet;		/* The actual packet */
	struct pcap_pkthdr header;	/* The header that pcap gives us */

	/* Grab a packet */
	packet = pcap_next(handle, &header);
	/* Print its length */
	printf("Jacked a packet with length of [%d]\n", header.len);
	/* And close the session */
	pcap_close(handle);

	return(0);
}