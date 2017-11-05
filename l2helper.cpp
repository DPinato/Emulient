#include "l2helper.h"

L2Helper::L2Helper() {

    eh = (struct ether_header *) sendbuf;
    srcMac = new uint8_t [6];
    dstMac = new uint8_t [6];

}

L2Helper::~L2Helper() {
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

ether_header *L2Helper::getEtherHeader() {
    return eh;
}

uint8_t *L2Helper::getSrcMac() {

}

uint8_t *L2Helper::getDstMac() {

}

uint16_t L2Helper::getEtherType() {

}
