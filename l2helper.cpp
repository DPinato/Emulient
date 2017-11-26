#include "l2helper.h"

L2Helper::L2Helper(int length) {

	sendbuf = new uint8_t [length * sizeof(uint8_t)];	// this holds the whole L2 header + L2 payload
	eh = (struct ether_header *) sendbuf;
	srcMac = new uint8_t [6];
	dstMac = new uint8_t [6];
	frameSize = length;
	payloadSize = 0;
	headerSize = sizeof(struct ether_header);

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
	// set the payload of the L2 frame
	payloadSize = size;
	l2Payload = new uint8_t [payloadSize * sizeof(uint8_t)];
	memcpy(l2Payload, data, (payloadSize * sizeof(uint8_t)));

	// change the size of sendbuf, since it needs to include the L2 payload
	frameSize = headerSize + payloadSize;

	sendbuf = (uint8_t *)realloc(sendbuf, frameSize * sizeof(uint8_t));
	if (sendbuf == NULL) {
		std::cerr << "Unable to reallocate in L2Helper::setPayload, tmpSize: " << frameSize;
	}

//	memcpy(&sendbuf[sizeof(struct ether_header)], l2Payload, payloadSize);
	memcpy(&sendbuf[headerSize*sizeof(uint8_t)], l2Payload, payloadSize);


}

void L2Helper::setDot1qHeader(uint16_t tpid, uint8_t pcp, uint8_t dei, uint16_t vlanID) {
	// insert the 802.1Q header right after the source MAC address
	tpid = tpid;
	pcp = pcp;
	dei = dei;
	vlanID = vlanID;

	// move over the L2 payload by 4 bytes
	frameSize += 4;
	headerSize += 4;
	qDebug() << "frameSize: " << frameSize << "\theaderSize: " << headerSize;
	sendbuf = (uint8_t *)realloc(sendbuf, frameSize*sizeof(uint8_t));	// increase frame buffer by 4 Bytes
	memcpy(&sendbuf[sizeof(struct ether_header)+4], l2Payload, payloadSize);

	// put back the ethertype, note that it has already gone through htons()
	sendbuf[17] = (uint8_t)(eh->ether_type>>8);
	sendbuf[16] = (uint8_t)(eh->ether_type&0xFF);


	// insert 802.1Q fields
	// | TPID (16-bits) | PCP (3 bits) | DEI (1 bit) | VLAN tag (12 bits) |
	uint16_t tpidTmp = tpid;
	sendbuf[12] = (uint8_t)(tpidTmp>>8);		// left-most
	sendbuf[13] = (uint8_t)(tpidTmp&0xFF);	// right-most, the AND operation is probably unnecessary
	qDebug() << sendbuf[12] << "\t" << sendbuf[13];

	// do TCI, i.e. PCP, DEI and VLAN tag
	uint16_t tciTmp = (pcp<<13);
	tciTmp += (dei<<12);
	tciTmp += vlanID;
//	tciTmp = htons(tciTmp);
	sendbuf[14] = (uint8_t)(tciTmp>>8);		// left-most
	sendbuf[15] = (uint8_t)(tciTmp&0xFF);	// right-most, the AND operation is probably unnecessary
	qDebug() << sendbuf[14] << "\t" << sendbuf[15];

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
