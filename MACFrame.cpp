#include "MACFrame.h"
#include <iostream>
#include <iomanip>

void MACFrame::encapsulateIPPacket(const IPPacket& newIpPacket) {
    initializeMACHeaderDefaults();
    setIn(new IPPacket(ipPacket));
    setOut(this);
    ipPacket = newIpPacket;
}

const MACHeader& MACFrame::getMACHeader() const {
    return macHeader;
}

void MACFrame::setMACHeader(const MACHeader& newMACHeader) {
    macHeader = newMACHeader;
}

const IPPacket& MACFrame::getIPPacket() const {
    return ipPacket;
}

void MACFrame::setIPPacket(const IPPacket& newIPPacket) {
    ipPacket = newIPPacket;
}

void MACFrame::print() const {
    std::cout << "\nMAC Header:\n";

    std::cout << "Source MAC: ";
    printMACAddress(macHeader.getSourceMAC());

    std::cout << "Destination MAC: ";
    printMACAddress(macHeader.getDestinationMAC());
}

void MACFrame::printMACAddress(uint64_t macAddress) const {
    for (int i = 5; i >= 0; --i) {
        std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
            << (unsigned((macAddress >> (i * 8)) & 0xFF));
        if (i > 0) {
            std::cout << ":";
        }
    }
    std::cout << std::endl;
}

void MACFrame::initializeMACHeaderDefaults() {
    macHeader.setSourceMAC(0x112233445566);
    macHeader.setDestinationMAC(0xAABBCCDDEEFF);
}

const std::string& MACFrame::getSerializedHTTPRequest() const {
    return serializedHTTPRequest;
}

void MACFrame::setSerializedHTTPRequest(const std::string& newSerializedHTTPRequest) {
    serializedHTTPRequest = newSerializedHTTPRequest;
}
