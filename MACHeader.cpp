#include "MACHeader.h"

MACHeader::MACHeader() : sourceMAC(0), destinationMAC(0) {}

MACHeader::MACHeader(uint64_t srcMAC, uint64_t destMAC)
    : sourceMAC(srcMAC), destinationMAC(destMAC) {}

uint64_t MACHeader::getSourceMAC() const {
    return sourceMAC;
}

uint64_t MACHeader::getDestinationMAC() const {
    return destinationMAC;
}

void MACHeader::setSourceMAC(uint64_t srcMAC) {
    sourceMAC = srcMAC;
}

void MACHeader::setDestinationMAC(uint64_t destMAC) {
    destinationMAC = destMAC;
}
