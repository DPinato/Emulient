#ifndef UTILITIES_H
#define UTILITIES_H

#include "mainwindow.h"

class Utilities
{
public:
    Utilities();

    static bool checkMacAddress(std::string mac);

    static bool intToMacAddress(uint64_t mac, uint8_t *ptr);
    static std::string intToMacAddress(uint64_t mac);

    static uint64_t stringToInt(std::string mac);

};

#endif // UTILITIES_H
