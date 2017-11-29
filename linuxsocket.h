#ifndef LINUXSOCKET_H
#define LINUXSOCKET_H

// #define DEFAULT_IF	"eth0"

#include "mainwindow.h"

class LinuxSocket {
public:
	LinuxSocket(uint8_t *mac);

	int send(int length, uint8_t *buffer);		// set the frame constructed


	// set
	void setInterfaceName(char *name);	// not implemented yet
	void setDstMacAddress(uint8_t *mac);

	// get
	char *getInterfaceName();	// not implemented yet
	int getSockfd();
	struct ifreq getIfIdx();
	struct ifreq getIfMac();



private:

	int sockfd;
	struct ifreq if_idx;
	struct ifreq if_mac;

	struct sockaddr_ll socket_address;
	char ifName[IFNAMSIZ];

	uint8_t sockDstMac[6];	// I am not sure whether this is REALLY needed for the socket

};

#endif // LINUXSOCKET_H
