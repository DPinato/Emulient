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
    for (int i = 0; i < mac.length(); i++) {
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

bool Utilities::intToMacAddress(uint64_t mac, uint8_t *ptr) {
    // convert the 64-bit integer mac to an array of 8-bit elements
    uint64_t tmpMac;
    for (int i = 0; i < 6; i++) {
        uint8_t tmp;
        tmp = mac >> 40-(8*i);
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


    qDebug() << "t: " << t.c_str();

    for (int i = 2; i < (int)t.length(); i+=3) {
        t.insert(i, ":");
    }
    qDebug() << "t: " << t.c_str();

    return t;

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
