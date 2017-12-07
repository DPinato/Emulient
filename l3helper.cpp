#include "l3helper.h"

L3Helper::L3Helper(int headerLength) {
	// tos, tot_len, id, frag_off, ttl, protocol, check, saddr, daddr
	headerSize = headerLength;
	sendbuf = new uint8_t [headerSize*sizeof(uint8_t)];	// this holds the whole L3 header + L3 payload

	// initialise sendbuf to 0
	for (int i = 0; i < headerSize; i++) { sendbuf[i] = 0; }
	iph = (struct iphdr *) sendbuf;

	version = 4;	// by default, do IPv4
	ihl = headerSize/4;		// default value is 5, when no IP options are in the header
	sendbuf[0] = (version<<4) + ihl;
//	qDebug() << "sendbuf[0]: " << (uint8_t)sendbuf[0];

	// initialise
	payloadSize = 0;
	packetSize = ihl*4;

}

L3Helper::L3Helper(const L3Helper &obj) {
	// do a deep copy of the object

	// copy single variables
	headerSize = obj.headerSize;
	payloadSize = obj.payloadSize;
	packetSize = obj.packetSize;
	version = obj.version;
	ihl = obj.ihl;

	// copy pointers/buffers
	sendbuf = new uint8_t [packetSize * sizeof(uint8_t)];
	l3Payload = new uint8_t [payloadSize * sizeof(uint8_t)];
	iph = (struct iphdr *) sendbuf;	// no need to do memcpy() for this, it already points to sendbuf

	memcpy(sendbuf, obj.sendbuf, packetSize * sizeof(uint8_t));
	memcpy(l3Payload, obj.l3Payload, payloadSize * sizeof(uint8_t));

}

L3Helper::~L3Helper() {
	delete[] sendbuf;
	delete[] l3Payload;
}

void L3Helper::setVersion(uint8_t v) {
	version = v;
	sendbuf[0] = (version<<4) + ihl;
}

void L3Helper::setIHL(uint8_t l) {
	ihl = l;
	sendbuf[0] = (version<<4) + ihl;
}

void L3Helper::setDSCP(uint8_t d) {
	// 6 left-most bits of TOS
	if (d < 0x40) {
		iph->tos = iph->tos & 0x02;	// zero out the 6 left-most bits
		iph->tos += (d<<2);
	}
}

void L3Helper::setECN(uint8_t e) {
	// 2 right-most bits of TOS
	if (e < 4) {
		iph->tos = iph->tos & 0xFC;	// zero out the 6 left-most bits
		iph->tos += (e);
	}
}

//void L3Helper::setTOS(uint8_t t) {
//	iph->tos = t;
//}

void L3Helper::setTotLength(uint16_t l) {
	iph->tot_len = htons(l);
}

void L3Helper::setIdentification(uint16_t i) {
	iph->id = htons(i);
}

void L3Helper::setFlags(uint16_t f) {
	// 3 left-most bit of fragment offset
	// since the whole field is 16-bits, it is probably easier to treat this as
	// 16 bits too, and use htons()
	// REMEMBER frag_off has been htons()ed
	iph->frag_off = iph->frag_off & 0xFF1F;	// zero out the 3 left-most bits
	if (f < 8) {
		// flag is 3-bit wide
		iph->frag_off += htons(f<<13);
//		qDebug() << "htons(): " << QString::number(htons(f<<13), 16);

	}
}

void L3Helper::setFragOffset(uint16_t f) {
	// 15 right-most bits of fragment offset
	iph->frag_off = iph->frag_off & 0x00E0; // set fragment offset to zero
//	qDebug() << "setFragOffset, iph->frag_off: " << QString::number(iph->frag_off, 16);

	if (f < 0x2000) {
		iph->frag_off += htons(f);
//		qDebug() << "htons(): " << QString::number(htons(f), 16);

	}
}

void L3Helper::setTTL(uint8_t t) {
	iph->ttl = t;
}

void L3Helper::setProtocol(uint8_t p) {
	iph->protocol = p;
}

void L3Helper::setChecksum(uint16_t c) {
	iph->check = htons(c);
}

void L3Helper::setSrcIP(uint32_t ip) {
	iph->saddr = htonl(ip);
}

void L3Helper::setDstIP(uint32_t ip) {
	iph->daddr = htonl(ip);
}

void L3Helper::setL3Payload(uint8_t *data, int size) {
	// reallocate sendbuf to include header + payload
	// at this point in time, sendbuf only has the header, and it is as large as the header
	payloadSize = size;
	l3Payload = new uint8_t [payloadSize * sizeof(uint8_t)];
	memcpy(l3Payload, data, (payloadSize * sizeof(uint8_t)));


	// change the size of sendbuf, since it needs to include the L3 payload
	packetSize = (headerSize + payloadSize) * sizeof(uint8_t);
/*	qDebug() << "setL3PayloadSize(), packetSize: "<< packetSize
			 << "\theaderSize: " << headerSize
			 << "\tpayloadSize: " << payloadSize;
*/

	// avoid using realloc()
//	sendbuf = (uint8_t *)realloc(sendbuf, tmpSize*sizeof(uint8_t));
	uint8_t *tmpBuf = new uint8_t [headerSize];	// temporary buffer while we enlarge sendbuf
	memcpy(tmpBuf, sendbuf, headerSize * sizeof(uint8_t));		// copy header in temporary buffer
	delete[] sendbuf;

	sendbuf = new uint8_t [packetSize];
	iph = (struct iphdr *) sendbuf;
	memcpy(sendbuf, tmpBuf, headerSize);
	memcpy(&sendbuf[headerSize * sizeof(uint8_t)], l3Payload, payloadSize);	// copy l3Payload in sendbuf

	delete[] tmpBuf;

}

struct iphdr *L3Helper::getIPHeader() {
	return iph;
}

uint8_t *L3Helper::getSendbuf() {
	return sendbuf;
}

uint8_t L3Helper::getVersion() {
	return version;
}

uint8_t L3Helper::getIHL() {
	return ihl;
}

uint8_t *L3Helper::getL3Payload() {
	return l3Payload;
}

int L3Helper::getL3PayloadSize() {
	return payloadSize;
}

int L3Helper::getPacketSize() {
	return packetSize;
}

uint32_t L3Helper::ip4To32bitUint(std::string ip) {
	// convert a string containing an IPv4 to a 32-bit unsigned integer
//	qDebug() << "L3Helper::ipTo32bitUint,\t" << QString::fromLocal8Bit(ip.c_str());
	uint32_t r = 0;
	int tmp1 = 0;
	int tmp2 = 0;
	int count = 0;	// helpful for the left shifting
	std::string tmpS = "";

	// IPv4 has 4 parts divided by a dot
	while (tmp2 != -1) {
		tmp2 = ip.find_first_of('.', tmp1+1);
		tmpS = ip.substr(tmp1, tmp2-tmp1);
		r += (uint32_t) (atoi(tmpS.c_str()) << (24-8*count));

		tmp1 = tmp2+1;
		count++;

	}

	return r;

}

std::string L3Helper::uintToIp4Str(uint32_t ip) {
	// convert an unsigned 32-bit integer to an IPv4 string
//	qDebug() << "L3Helper::uintToIp4Str,\t" << ip;

	std::string r = "";

	for (int i = 0; i < 4; i++) {
		uint8_t tmp = (ip>>(24-8*i));
		r.append(std::to_string(tmp));
		if (i < 3) { r.append("."); }

	}

	return r;

}

uint16_t L3Helper::computeIPv4Checksum() {
	// compute IPv4 checksum according to header
	// note that this will likely fail if some of the values are simply not present
	// (different from values not being set properly, maybe header buffer is not allocated properly?)
	qDebug() << "computeIPv4Checksum()";
	uint32_t tmp = 0;	// this cannot be only 16-bits, since it needs to carry over left-most bits
	uint16_t header[ihl*2];	// collect header valued in 16-bit uint format

	for (int i = 0; i < ihl*4; i+=2) {
		// the IPv4 header size should always be divisible by 4 Bytes
		// do not sum the checksum field itself
		if (i != 10 && i!=11) {
			header[i/2] = ((uint8_t)sendbuf[i]<<8) + (uint8_t)sendbuf[i+1];
			tmp += header[i/2];	// sum all the 16-bit values
		}
//		qDebug() << i << "\theader[i]: " << QString::number(header[i/2], 16);
	}
//	qDebug() << "sum: " << QString::number(tmp, 16);

	// carry over any left-most bits above bit 15 (right-most bit is bit zero)
	tmp = (tmp&0xFFFF) + (tmp>>16);
	while (tmp >0xFFFF) {
		// there is a double carry, do the above again
		tmp = (tmp&0xFFFF) + (tmp>>16);
	}

	qDebug() << QString::number(~(uint16_t)tmp, 16);
	return ~(uint16_t)tmp;	// final operation is a NOT

}

uint16_t L3Helper::verifyIPv4Checksum() {
	// check whether IPv4 headerchecksum of this header is correct
	// returns 0 if correct, any other number otherwise
	// TODO: this looks awfully close to computeIPv4Checksum(), can you do anything about that?
	qDebug() << "verifyIPv4Checksum()";
	uint32_t tmp = 0;	// this cannot be only 16-bits, since it needs to carry over left-most bits
	uint16_t header[ihl*2];	// collect header valued in 16-bit uint format

	for (int i = 0; i < ihl*4; i+=2) {
		// the IPv4 header size should always be divisible by 4 Bytes
		// DO sum the checksum field itself
		header[i/2] = ((uint8_t)sendbuf[i]<<8) + (uint8_t)sendbuf[i+1];
		tmp += header[i/2];	// sum all the 16-bit values
	}

	// carry over any left-most bits above bit 15 (right-most bit is bit zero)
	tmp = (tmp&0xFFFF) + (tmp>>16);
	while (tmp >0xFFFF) {
		// there is a double carry, do the above again
		tmp = (tmp&0xFFFF) + (tmp>>16);
	}

	return ~(uint16_t)tmp;	// final operation is a NOT

}

void L3Helper::showSendBuf(int l) {
	// show l bytes of sendbuf
	for (int i = 0; i < l; i++) {
//		qDebug() << sendbuf[i];
		qDebug() << QString::number(sendbuf[i], 16);
	}
}
