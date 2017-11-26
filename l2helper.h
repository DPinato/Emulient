/* Class used to help with the creation and management of variables and fields
 * for the L2 header.
 *
 * The purpose of this class os to make it so that when a socket is created and a
 * frame is to be sent, only the send() function of the socket needs to be called,
 * using the buffer from the L2Helper
 *
 */

#ifndef L2HELPER_H
#define L2HELPER_H

#include "mainwindow.h"

class L2Helper
{
public:
	L2Helper(int length);
	~L2Helper();

	// SET
	void setEtherHeader(ether_header *h);
	void setSrcMac(uint8_t *src);
	void setDstMac(uint8_t *dst);
	void setEtherType(uint16_t eType);
	void setPayload(uint8_t *data, int size);

	// GET
	ether_header *getEtherHeader();
	uint8_t *getSrcMac();
	uint8_t *getDstMac();
	uint16_t getEtherType();
	uint8_t *getSendbuf();
	uint8_t *getPayload();
	int getFrameSize();
	int getPayloadSize();

private:
	uint8_t *sendbuf;		// complete L2 frame, header + payload

	uint8_t *l2Payload;	// payload of the L2 frame, this is closer to binary
	int payloadSize;	// size of payload, L2 payload
	int frameSize;		// size of the whole frame, L2 header + L2 payload

	struct ether_header *eh;

	uint8_t *srcMac;    // store MAC address as a 6-element array
	uint8_t *dstMac;

	uint64_t srcMacInt; // store MAC address as a 48-bit uint
	uint64_t dstMacInt;
};

#endif // L2HELPER_H
