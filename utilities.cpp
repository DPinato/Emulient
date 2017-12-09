#include "utilities.h"

Utilities::Utilities()
{

}

bool Utilities::checkMacAddress(std::string mac) {
	// check if the string given is a valid MAC address
	// format expected is xx:xx:xx:xx:xx:xx
	// I am going to do something really quick here

	// check :
	if (mac.at(2) == ':' || mac.at(5) == ':' || mac.at(8) == ':'
			|| mac.at(11) == ':' || mac.at(14) == ':') {
	} else {
		return false;
	}

	// get 2 digit hex numbers 1 by 1
	for (int i = 0; i < (int)mac.length(); i++) {
		std::string tmp = mac.substr(i, 2);
		qDebug() << QString::fromLocal8Bit(tmp.c_str());

		// check if tmp is a valid number in hex
		uint8_t tmpHex;
		if (sscanf(tmp.c_str(), "%X", &tmpHex) == EOF) {
			// I am not sure this actually works
			return false;
		}

		i+=2;
	}


	return true;

}

uint8_t* Utilities::intToMacAddress(uint64_t mac, uint8_t *ptr) {
	// convert the 64-bit integer mac to an array of 8-bit elements
	for (int i = 0; i < 6; i++) {
		uint8_t tmp;
		tmp = mac >> (40-(8*i));
//        qDebug() << "tmp: " << tmp;

		ptr[i] = tmp;
	}

	return ptr;

}

std::string Utilities::intToMacAddress(uint64_t mac) {
	std::string t = "";
	std::stringstream stream;
	stream << std::hex << mac;
	t = stream.str();

	// add leading zeroes
	while (t.length() < 12) {
		t.insert(0, "0");
	}

//    qDebug() << "t: " << t.c_str();

	for (int i = 2; i < (int)t.length(); i+=3) {
		t.insert(i, ":");
	}
//    qDebug() << "t: " << t.c_str();

	return t;

}

std::string Utilities::arrayToMacAddressStr(uint8_t *ptr) {
    // take a 6-element array that forms a MAC address and transform it into a string
    std::string tmp = "";

    for(int i = 0; i < 6; i++) {
        tmp.append(QString::number(ptr[i], 16).rightJustified(2, '0').toStdString());
        if (i < 5) { tmp.append(":"); }
    }

    return tmp;

}

uint64_t Utilities::stringToInt(std::string mac) {
	// convert 48-bit MAC address to 64-bit uint svalue
	uint64_t t = 0;

	for (int i = 0; i < (int)mac.length(); i++) {
		std::string tmpS = mac.substr(i, 2);
		uint64_t tmpU = (uint8_t)strtoul(tmpS.c_str(), NULL, 16);
		int shift = (48-8)-((i/3)*8);   // amount of left shift to apply
//        qDebug() << "tmpS: " << tmpS.c_str() << "\ttmpU: " << tmpU
//                 << "\ti: " << i << "\t" << shift;

		t += (tmpU<<shift);
//        qDebug() << "t: " << t;

		i+=2;

	}

	return t;

}

std::string Utilities::intToIPAddressStr(uint32_t ip) {
	// convert 32-bit integer to an IPv4 address string
	std::string tmp = "";
	uint32_t tmpIP = ip;

	for (int i = 0; i < 4; i++) {
		// IPv4 has 4 octets, i.e. it is 4-Bytes wide
		qDebug() << tmpIP << "\t" << (tmpIP>>(8*(3-i)));
		tmp.insert(0, std::to_string((tmpIP>>(8*(3-i)))));	// put the value in the string
		tmpIP &= (0x00FFFFFF>>(i*8));		// zero-out the left most 8 bits, so we can keep right shifting

		if (i < 3) { tmp.insert(0, "."); }

	}

	qDebug() << QString(tmp.c_str());
	return tmp;

}

uint32_t Utilities::ipAddressStrToInt(std::string ip) {
	// convert IPv4 address string to 32-bit integer
	std::string tmpIP = ip;
	uint32_t tmp = 0;
	int start = 0;
	int end = 0;

	for (int i = 0; i < 4; i++) {
		std::string tmpStr;
		end = ip.find_first_of(".", start+1);

		if (i == 0) {
			tmpStr = ip.substr(start, end-start);
		} else {
			tmpStr = ip.substr(start+1, end-start-1);
		}

//		qDebug() << QString(tmpStr.c_str());
		tmp += ((int)atoi(tmpStr.c_str()))<<(8*(3-i));

		start = end;

	}

	return tmp;

}

