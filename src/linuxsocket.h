#ifndef LINUXSOCKET_H
#define LINUXSOCKET_H

// #define DEFAULT_IF	"eth0"

#include "mainwindow.h"

class LinuxSocket {
public:
	LinuxSocket(uint8_t *mac, std::string interface);
	~LinuxSocket();

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
	std::string ifName;

	uint8_t *sockDstMac;

};

#endif // LINUXSOCKET_H
