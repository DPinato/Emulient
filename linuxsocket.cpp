#include "linuxsocket.h"

LinuxSocket::LinuxSocket(uint8_t *mac) {
	// initialise the socket object
	// for testing leave this stuff all here for now
	setDstMacAddress(mac);	// just in case

	strcpy(ifName, DEFAULT_IF);		// get interface name

	// Open RAW socket to send on
	if ((sockfd = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW)) == -1) {
		perror("socket");
	}


	/* Get the index of the interface to send on */
	memset(&if_idx, 0, sizeof(struct ifreq));
	strncpy(if_idx.ifr_name, ifName, IFNAMSIZ-1);
	if (ioctl(sockfd, SIOCGIFINDEX, &if_idx) < 0) { perror("SIOCGIFINDEX"); }


	/* Get the MAC address of the interface to send on */
	memset(&if_mac, 0, sizeof(struct ifreq));
	strncpy(if_mac.ifr_name, ifName, IFNAMSIZ-1);
	if (ioctl(sockfd, SIOCGIFHWADDR, &if_mac) < 0) { perror("SIOCGIFHWADDR"); }

	socket_address.sll_ifindex = if_idx.ifr_ifindex;	// index of network device
	socket_address.sll_halen = ETH_ALEN;	// address length

	/* Destination MAC */
	// this is the one that actually matters, it shows up in the frame header
	socket_address.sll_addr[0] = sockDstMac[0];
	socket_address.sll_addr[1] = sockDstMac[1];
	socket_address.sll_addr[2] = sockDstMac[2];
	socket_address.sll_addr[3] = sockDstMac[3];
	socket_address.sll_addr[4] = sockDstMac[4];
	socket_address.sll_addr[5] = sockDstMac[5];


}

LinuxSocket::~LinuxSocket() {
	delete[] sockDstMac;
}

int LinuxSocket::send(int length, uint8_t *buffer) {
	// using the socket already initialised, send the buffer of data to the socket
	int bytesSent = sendto(sockfd, (uint8_t *)buffer, length, 0
						   , (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll));
//    if (sendto(sockfd, sendbuf, tx_len, 0, (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll)) < 0)
	if (bytesSent < 0) { printf("Send failed\n"); }

	qDebug() << "SENT FRAME, bytesSent: " << bytesSent;

	return bytesSent;

}

void LinuxSocket::setDstMacAddress(uint8_t *mac) {
	sockDstMac = new uint8_t [6 * sizeof(uint8_t)];
	memcpy(sockDstMac, mac, 6 * sizeof(uint8_t));

}

int LinuxSocket::getSockfd() {
	return sockfd;
}

ifreq LinuxSocket::getIfIdx() {
	return if_idx;
}

ifreq LinuxSocket::getIfMac() {
	return if_mac;
}
