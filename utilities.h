#ifndef UTILITIES_H
#define UTILITIES_H

#include "mainwindow.h"

class Utilities
{
public:
    Utilities();

    static bool checkMacAddress(std::string mac);

    // conversion for MAC addresses
    static uint8_t *intToMacAddress(uint64_t mac, uint8_t *ptr);
    static std::string intToMacAddress(uint64_t mac);
    static std::string arrayToMacAddressStr(uint8_t *ptr);
    static uint64_t stringToInt(std::string mac);   // TODO: This function's name is terrible

    // conversion for IPv4 addresses
    static std::string intToIPAddressStr(uint32_t ip);
    static uint32_t ipAddressStrToInt(std::string ip);

};

#endif // UTILITIES_H
