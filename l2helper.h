/* Class used to help with the creation and management of variables and fields
 * for the L2 header.
 *
 *
 */
#ifndef L2HELPER_H
#define L2HELPER_H

#include "mainwindow.h"

class L2Helper
{
public:
    L2Helper();
    ~L2Helper();

    // SET
    void setEtherHeader(ether_header *h);
    void setSrcMac(uint8_t *src);
    void setDstMac(uint8_t *dst);
    void setEtherType(uint16_t eType);

    // GET
    ether_header *getEtherHeader();
    uint8_t *getSrcMac();
    uint8_t *getDstMac();
    uint16_t getEtherType();

private:
    char sendbuf[20];
    struct ether_header *eh;

    uint8_t *srcMac;    // store MAC address as a 6-element array
    uint8_t *dstMac;

    uint64_t srcMacInt; // store MAC address as a 48-bit uint
    uint64_t dstMacInt;
};

#endif // L2HELPER_H
