/* Class used to help with the creation of what will go inside the L2 frame payload
 * L3 headers and L3 payload too
 *
 *
 *
 */


#ifndef L3HELPER_H
#define L3HELPER_H

#include "mainwindow.h"

class L3Helper
{
public:
	L3Helper(int headerLength);
	~L3Helper();

	void init();	// reset variables


	// set
	void setVersion(uint8_t v);	// version1
	void setIHL(uint8_t l);		// Internet header length
//	void setTOS(uint8_t t);		// DSCP + ECN, I am just going to separate DSCP and ECN
	void setDSCP(uint8_t d);	// DSCP, 6 bits
	void setECN(uint8_t e);		// ECN, 2 bits
	void setTotLength(uint16_t l);	// total length of entire packet, header + data
	void setIdentification(uint16_t i);		// id
//	void setFragOffset(uint16_t f);	// flags + fragment offset, separate this
	void setFlags(uint16_t f);		// flags, 3 bits
	void setFragOffset(uint16_t f);	// fragment offset, 15 bits
	void setTTL(uint8_t t);
	void setProtocol(uint8_t p);
	void setChecksum(uint16_t c);
	void setSrcIP(uint32_t ip);
	void setDstIP(uint32_t ip);

	void setL3PayloadSize(int size);
	void setL3Payload(uint8_t *buf, int size);


	// get
	struct iphdr *getIPHeader();
	uint8_t *getSendbuf();
	uint8_t getVersion();
	uint8_t getIHL();
	uint8_t *getL3Payload();
	int getL3PayloadSize();


	// other
	static uint32_t ip4To32bitUint(std::string ip);
	static std::string uintToIp4Str(uint32_t ip);
	uint16_t computeIPv4Checksum();
	uint16_t verifyIPv4Checksum();


	// debug
	void showSendBuf(int l);


private:
	uint8_t *sendbuf;		// L3 header + L3 payload
						// its size is IHL until setL3PayloadSize() is called
	uint8_t *l3Payload;	// L3 payload
	int payloadSize;	// L3 payload size, in bytes

	struct iphdr *iph;

	// I don't remember exactly why I decided to put these here
	// I think its because the iphdr struct does not have an entry for version
	uint8_t version;
	uint8_t ihl;

};

#endif // L3HELPER_H
