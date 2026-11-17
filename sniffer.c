#include <stdio.h>
#include <pcap.h>

/* https://www.tcpdump.org/pcap.html */
/* Ethernet addresses are 6 bytes */
#define ETHER_ADDR_LEN	6

/* Ethernet header */
struct sniff_ethernet {
	u_char ether_dhost[ETHER_ADDR_LEN]; /* Destination host address */
	u_char ether_shost[ETHER_ADDR_LEN]; /* Source host address */
	u_short ether_type; /* IP? ARP? RARP? etc */
};

/* ethernet headers are always exactly 14 bytes */
#define SIZE_ETHERNET 14
const struct sniff_ethernet *ethernet; /* The ethernet header */

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

	printf("IEEE802_11_RADIOTAP header: %i\n", pcap_datalink(handle)); // 127 https://www.tcpdump.org/linktypes.html

	const u_char *packet;		/* The actual packet */
	struct pcap_pkthdr header;	/* The header that pcap gives us */

	packet = pcap_next(handle, &header);
	printf("Jacked a packet with length of [%d]\n", header.len);

	ethernet = (struct sniff_ethernet*)(packet);
	
	/* Tests */
	printf("\n\n\n");
	for(unsigned int i = 0; i < ETHER_ADDR_LEN; i++) printf("%c", ethernet->ether_dhost[i]);
	printf("\n");
	for(unsigned int i = 0; i < ETHER_ADDR_LEN; i++) printf("%c", ethernet->ether_shost[i]);
	printf("\n");
	printf("%d", ethernet->ether_type);
	printf("\n");

	// End
	pcap_close(handle);

	return(0);
}