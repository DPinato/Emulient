#include "l2helper.h"

L2Helper::L2Helper() {
	headerSize = sizeof(struct ether_header);
	frameSize = headerSize;
	sendbuf = new uint8_t [frameSize*sizeof(uint8_t)];	// this holds the whole L2 header + L2 payload
	eh = (struct ether_header *) sendbuf;
	srcMac = new uint8_t [6];
	dstMac = new uint8_t [6];
	payloadSize = 0;
	dot1q = false;

}

L2Helper::~L2Helper() {
	delete sendbuf;
	delete eh;
	delete srcMac;
	delete dstMac;
}

void L2Helper::init() {
	dot1q = false;
	payloadSize = 0;
	headerSize = sizeof(struct ether_header);
	frameSize = headerSize;

	// check if sendbuf was already allocated
	if (sendbuf != NULL) { sendbuf = (uint8_t *)realloc(sendbuf, frameSize*sizeof(uint8_t)); }

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
	// set the payload of the L2 frame
	// q indicates whether the header has dot1q, for frame size calculation
	payloadSize = size;
	l2Payload = new uint8_t [payloadSize * sizeof(uint8_t)];
	memcpy(l2Payload, data, (payloadSize * sizeof(uint8_t)));

	// change the size of sendbuf, since it needs to include the L2 payload
	if (!dot1q) { headerSize = (int)sizeof(struct ether_header); }
	frameSize = headerSize + payloadSize;
	qDebug() << "setPayload(), frameSize: "<< frameSize
			 << "\theaderSize: " << headerSize
			 << "\tpayloadSize: " << payloadSize
			 << "\tdot1q: " << dot1q;

	sendbuf = (uint8_t *)realloc(sendbuf, frameSize * sizeof(uint8_t));
	if (sendbuf == NULL) {
		std::cerr << "Unable to reallocate in L2Helper::setPayload, tmpSize: " << frameSize;
	}

	memcpy(&sendbuf[headerSize*sizeof(uint8_t)], l2Payload, payloadSize);

}

void L2Helper::setDot1qHeader(uint16_t tpid, uint8_t pcp, uint8_t dei, uint16_t vlanID) {
	// insert the 802.1Q header right after the source MAC address
	// this should be run before setPayload()
	tpid = tpid;
	pcp = pcp;
	dei = dei;
	vlanID = vlanID;
	dot1q = true;

	// move over the L2 payload by 4 bytes
	if (dot1q && frameSize <= (int)sizeof(struct ether_header)) { frameSize += 4; }
	headerSize = sizeof(struct ether_header)+4;
	qDebug() << "setDot1qHeader(), frameSize: "<< frameSize
			 << "\theaderSize: " << headerSize
			 << "\tpayloadSize: " << payloadSize;

	sendbuf = (uint8_t *)realloc(sendbuf, frameSize*sizeof(uint8_t));	// increase frame buffer by 4 Bytes
	memcpy(&sendbuf[headerSize], l2Payload, payloadSize);

	// put back the ethertype, note that it has already gone through htons()
	sendbuf[headerSize-1] = (uint8_t)(eh->ether_type>>8);
	sendbuf[headerSize-2] = (uint8_t)(eh->ether_type&0xFF);


	// insert 802.1Q fields
	// | TPID (16-bits) | PCP (3 bits) | DEI (1 bit) | VLAN tag (12 bits) |
	uint16_t tpidTmp = tpid;
	sendbuf[headerSize-6] = (uint8_t)(tpidTmp>>8);		// left-most
	sendbuf[headerSize-5] = (uint8_t)(tpidTmp&0xFF);	// right-most, the AND operation is probably unnecessary
//	qDebug() << sendbuf[headerSize-6] << "\t" << sendbuf[headerSize-5];

	// do TCI, i.e. PCP, DEI and VLAN tag
	uint16_t tciTmp = (pcp<<13);
	tciTmp += (dei<<12);
	tciTmp += vlanID;
	sendbuf[headerSize-4] = (uint8_t)(tciTmp>>8);		// left-most
	sendbuf[headerSize-3] = (uint8_t)(tciTmp&0xFF);	// right-most, the AND operation is probably unnecessary
//	qDebug() << sendbuf[headerSize-4] << "\t" << sendbuf[headerSize-3];

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

uint8_t *L2Helper::getSendbuf() {
	return sendbuf;
}

uint8_t *L2Helper::getPayload() {
	return l2Payload;
}

int L2Helper::getFrameSize() {
	return frameSize;
}

int L2Helper::getPayloadSize() {
	return payloadSize;
}

uint16_t L2Helper::getTpid() {
	return tpid;
}

uint8_t L2Helper::getPcp() {
	return pcp;
}

uint8_t L2Helper::getDei() {
	return dei;
}

uint16_t L2Helper::getVlanID() {
	return vlanID;
}

bool L2Helper::hasDot1Q() {
	return dot1q;
}
