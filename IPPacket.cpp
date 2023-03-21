#include "IPPacket.h"
#include <iostream>
#include <cstdint>

void IPPacket::encapsulateTCPSegment(const TCPSegment& newTcpSegment) {
    initializeIPHeaderDefaults();

    setIn(new TCPSegment(tcpSegment));

    setOut(this);
    tcpSegment = newTcpSegment;
}

const IPHeader& IPPacket::getIPHeader() const {
    return ipHeader;
}

void IPPacket::setIPHeader(const IPHeader& newIPHeader) {
    ipHeader = newIPHeader;
}

const TCPSegment& IPPacket::getTCPSegment() const {
    return tcpSegment;
}

void IPPacket::setTCPSegment(const TCPSegment& newTCPSegment) {
    tcpSegment = newTCPSegment;
}

void IPPacket::print() const {
    const IPHeader& ipHeader = getIPHeader();
    std::cout << "\nIP Header:" << std::endl;
    std::cout << "Version: " << static_cast<unsigned>(ipHeader.getVersion()) << std::endl;
    std::cout << "Header Length: " << static_cast<unsigned>(ipHeader.getHeaderLength()) << std::endl;
    std::cout << "Type of Service: " << static_cast<unsigned>(ipHeader.getTypeOfService()) << std::endl;
    std::cout << "Total Length: " << static_cast<unsigned>(ipHeader.getTotalLength()) << std::endl;
    std::cout << "Identification: " << static_cast<unsigned>(ipHeader.getIdentification()) << std::endl;
    std::cout << "Flags: " << static_cast<unsigned>(ipHeader.getFlags()) << std::endl;
    std::cout << "Fragment Offset: " << static_cast<unsigned>(ipHeader.getFragmentOffset()) << std::endl;
    uint8_t ttl = ipHeader.getTimeToLive();
    std::cout << "Time to Live: "<< std::dec << static_cast<int>(ttl)<< std::endl;
    std::cout << "Protocol: " << static_cast<unsigned>(ipHeader.getProtocol()) << std::endl;
    std::cout << "Checksum: " << static_cast<unsigned>(ipHeader.getChecksum()) << std::endl;
    std::cout << "Source IP: " << ipHeader.getSourceIP() << std::endl;
    std::cout << "Destination IP: " << ipHeader.getDestinationIP() << std::endl;
}

void IPPacket::initializeIPHeaderDefaults() {
    ipHeader.setVersion(4);
    ipHeader.setHeaderLength(5);
    ipHeader.setTypeOfService(0);
    ipHeader.setTotalLength(0);
    ipHeader.setIdentification(0);
    ipHeader.setFlags(0);
    ipHeader.setFragmentOffset(0);
    ipHeader.setTimeToLive(64);
    ipHeader.setProtocol(6);
    ipHeader.setChecksum(0);
    ipHeader.setSourceIP("192.168.1.1");
    ipHeader.setDestinationIP("8.8.8.8");
}
