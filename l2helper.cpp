#include "l2helper.h"

L2Helper::L2Helper(int length) {

	sendbuf = new char [length];	// this holds the whole L2 header + L2 payload
	eh = (struct ether_header *) sendbuf;
	srcMac = new uint8_t [6];
	dstMac = new uint8_t [6];
	frameSize = 14; // minimum header size for Ethernet II

}

L2Helper::~L2Helper() {
	delete sendbuf;
	delete eh;
	delete srcMac;
	delete dstMac;
}

void L2Helper::setEtherHeader(ether_header *h) {
	eh = h;
}

void L2Helper::setSrcMac(uint8_t *src) {
	eh->ether_shost[0] = src[0];
	eh->ether_shost[1] = src[1];
	eh->ether_shost[2] = src[2];
	eh->ether_shost[3] = src[3];
	eh->ether_shost[4] = src[4];
	eh->ether_shost[5] = src[5];
}

void L2Helper::setDstMac(uint8_t *dst) {
	eh->ether_dhost[0] = dst[0];
	eh->ether_dhost[1] = dst[1];
	eh->ether_dhost[2] = dst[2];
	eh->ether_dhost[3] = dst[3];
	eh->ether_dhost[4] = dst[4];
	eh->ether_dhost[5] = dst[5];
}

void L2Helper::setEtherType(uint16_t eType) {
	eh->ether_type = htons(eType);
}

void L2Helper::setPayload(uint8_t *data, int size) {
	payload = new uint8_t [size];
	payload = (uint8_t*)data;	// TODO: use memcopy here
	payloadSize = size;
	frameSize += payloadSize;
	memcpy(&sendbuf[14], payload, payloadSize);

}

ether_header *L2Helper::getEtherHeader() {
	return eh;
}

uint8_t *L2Helper::getSrcMac() {
	return srcMac;
}

uint8_t *L2Helper::getDstMac() {
	return dstMac;
}

uint16_t L2Helper::getEtherType() {
	return eh->ether_type;
}

char *L2Helper::getSendbuf() {
	return sendbuf;
}

uint8_t *L2Helper::getPayload() {
	return payload;
}

int L2Helper::getFrameSize() {
	return frameSize;
}

int L2Helper::getPayloadSize() {
	return payloadSize;
}
