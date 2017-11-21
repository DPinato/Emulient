#include "l3helper.h"

L3Helper::L3Helper(int headerLength, int totalLength) {
	// tos, tot_len, id, frag_off, ttl, protocol, check, saddr, daddr
	sendbuf = new char [totalLength];	// this holds the whole L3 header + L3 payload

	// initialise sendbuf to 0
	for (int i = 0; i < totalLength; i++) { sendbuf[i] = 0; }
	iph = (struct iphdr *) sendbuf;

	version = 4;	// by default, do IPv4
//	ihl = 5;		// default value is 5, when no IP options are in the header
	ihl = totalLength/4;		// default value is 5, when no IP options are in the header
	sendbuf[0] = (version<<4) + ihl;

	qDebug() << "sendbuf[0]: " << (uint8_t)sendbuf[0];

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
	if (f < 8) {
		iph->frag_off = iph->frag_off & 0x1FFF;	// zero out the 3 left-most bits
		iph->frag_off += htons((f<<13));
	}
}

void L3Helper::setFragOffset(uint16_t f) {
	// 15 right-most bits of fragment offset
	if (f < 0x2000) {
		iph->frag_off = iph->frag_off & 0x00E0;	// think about how it would be from setFlags()
		iph->frag_off += htons(f);
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

struct iphdr *L3Helper::getIPHeader() {
	return iph;
}

char *L3Helper::getRawHeader() {
	return sendbuf;
}

uint8_t L3Helper::getVersion() {
	return version;
}

uint8_t L3Helper::getIHL() {
	return ihl;
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

void L3Helper::computeChecksum() {

}

void L3Helper::showSendBuf(int l) {
	// show l bytes of sendbuf
	for (int i = 0; i < l; i++) {
		qDebug() << (uint8_t)sendbuf[i];
	}
}
