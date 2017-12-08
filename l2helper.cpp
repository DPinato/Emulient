#include "l2helper.h"

L2Helper::L2Helper() {
	headerSize = sizeof(struct ether_header);
	frameSize = headerSize;
	sendbuf = new uint8_t [frameSize * sizeof(uint8_t)];	// this holds the whole L2 header + L2 payload
	eh = (struct ether_header *) sendbuf;
	payloadSize = 0;


	// initialise these just in case
	dot1q = false;
	vlanID = 0;
	tpid = 0;
	pcp = 0;
	dei = 0;
	etherTypeVar = 0;

}

L2Helper::L2Helper(const L2Helper &obj) {
	// do a deep copy of the object

	// copy single variables
	headerSize = obj.headerSize;
	payloadSize = obj.payloadSize;
	frameSize = obj.frameSize;
	srcMacInt = obj.srcMacInt;
	dstMacInt = obj.dstMacInt;
	dot1q = obj.dot1q;
	tpid = obj.tpid;
	pcp = obj.pcp;
	dei = obj.dei;
	vlanID = obj.vlanID;
	etherTypeVar = obj.etherTypeVar;

	// copy pointers/buffers
	sendbuf = new uint8_t [frameSize * sizeof(uint8_t)];
	l2Payload = new uint8_t [payloadSize * sizeof(uint8_t)];
	eh = (struct ether_header *) sendbuf;	// no need to do memcpy() for this, it already points to sendbuf
	srcMac = new uint8_t [6 * sizeof(uint8_t)];
	dstMac = new uint8_t [6 * sizeof(uint8_t)];

	memcpy(sendbuf, obj.sendbuf, frameSize * sizeof(uint8_t));
	memcpy(l2Payload, obj.l2Payload, payloadSize * sizeof(uint8_t));
	memcpy(srcMac, obj.srcMac, 6 * sizeof(uint8_t));
	memcpy(dstMac, obj.dstMac, 6 * sizeof(uint8_t));

}

L2Helper::~L2Helper() {
	delete[] sendbuf;
	delete eh;
	delete[] srcMac;
	delete[] dstMac;
}

void L2Helper::init() {
	dot1q = false;
	payloadSize = 0;
	headerSize = sizeof(struct ether_header);
	frameSize = headerSize;

}

void L2Helper::setEtherHeader(ether_header *h) {
	eh = h;
}

void L2Helper::setSrcMac(uint8_t *src) {
	srcMac = new uint8_t [6 * sizeof(uint8_t)];
	memcpy(srcMac, src, 6 * sizeof(uint8_t));
	eh->ether_shost[0] = srcMac[0];
	eh->ether_shost[1] = srcMac[1];
	eh->ether_shost[2] = srcMac[2];
	eh->ether_shost[3] = srcMac[3];
	eh->ether_shost[4] = srcMac[4];
	eh->ether_shost[5] = srcMac[5];
}

void L2Helper::setDstMac(uint8_t *dst) {
	dstMac = new uint8_t [6 * sizeof(uint8_t)];
	memcpy(dstMac, dst, 6 * sizeof(uint8_t));
	eh->ether_dhost[0] = dstMac[0];
	eh->ether_dhost[1] = dstMac[1];
	eh->ether_dhost[2] = dstMac[2];
	eh->ether_dhost[3] = dstMac[3];
	eh->ether_dhost[4] = dstMac[4];
	eh->ether_dhost[5] = dstMac[5];
}

void L2Helper::setEtherType(uint16_t eType) {
	etherTypeVar = eType;
	eh->ether_type = htons(etherTypeVar);
}

void L2Helper::setPayload(uint8_t *data, int size) {
	// set the payload of the L2 frame
	// at this point in time, sendbuf only has the header, and it is as large as the header
	payloadSize = size;
	l2Payload = new uint8_t [payloadSize * sizeof(uint8_t)];
	memcpy(l2Payload, data, (payloadSize * sizeof(uint8_t)));


	// change the size of sendbuf, since it needs to include the L2 payload
	if (!dot1q) {headerSize = (int)sizeof(struct ether_header) * sizeof(uint8_t); }
	frameSize = (headerSize + payloadSize) * sizeof(uint8_t);
	qDebug() << "setPayload(), frameSize: "<< frameSize
			 << "\theaderSize: " << headerSize
			 << "\tpayloadSize: " << payloadSize
			 << "\tdot1q: " << dot1q;


	// avoid using realloc()
//	sendbuf = (uint8_t *)realloc(sendbuf, frameSize * sizeof(uint8_t));
	uint8_t *tmpBuf = new uint8_t [headerSize];	// temporary buffer while we enlarge sendbuf
	memcpy(tmpBuf, sendbuf, headerSize);		// copy header in temporary buffer
	delete[] sendbuf;

	sendbuf = new uint8_t [frameSize];		// enlarge sendbuf
	eh = (struct ether_header *) sendbuf;
	memcpy(sendbuf, tmpBuf, headerSize);	// copy header
	memcpy(&sendbuf[headerSize * sizeof(uint8_t)], l2Payload, payloadSize);	// copy payload
	delete[] tmpBuf;

}

void L2Helper::setDot1qHeader(uint16_t tpidV, uint8_t pcpV, uint8_t deiV, uint16_t vlanIDV) {
	// insert the 802.1Q header right after the source MAC address
	// this should be run before setPayload()
	tpid = tpidV;
	pcp = pcpV;
	dei = deiV;
	vlanID = vlanIDV;
	dot1q = true;

	// move over the L2 payload by 4 bytes
	if (dot1q && frameSize <= (int)sizeof(struct ether_header)) { frameSize += 4; }
	headerSize = sizeof(struct ether_header)+4;
	qDebug() << "setDot1qHeader(), frameSize: "<< frameSize
			 << "\theaderSize: " << headerSize
			 << "\tpayloadSize: " << payloadSize;

	// avoid using realloc()
	sendbuf = (uint8_t *)realloc(sendbuf, frameSize * sizeof(uint8_t));	// increase frame buffer by 4 Bytes
	uint8_t *tmpBuf = new uint8_t [frameSize * sizeof(uint8_t)];
	memcpy(tmpBuf, sendbuf, frameSize * sizeof(uint8_t));
	delete[] sendbuf;

	sendbuf = new uint8_t [frameSize * sizeof(uint8_t)];
	eh = (struct ether_header *) sendbuf;
	memcpy(sendbuf, tmpBuf, frameSize * sizeof(uint8_t));
	memcpy(&sendbuf[headerSize], l2Payload, payloadSize);
	delete[] tmpBuf;


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
	return etherTypeVar;
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
