#include "TCPSegment.h"

void TCPSegment::encapsulateHTTPRequestMSG(const HTTPRequestMSG& httpRequest) {
    initializeTCPHeaderDefaults();
    httpRequestMSG = httpRequest;
    setIn(&httpRequestMSG);
    setOut(this);
}

const TCPHeader& TCPSegment::getTCPHeader() const {
    return tcpHeader;
}

void TCPSegment::setTCPHeader(const TCPHeader& newTCPHeader) {
    tcpHeader = newTCPHeader;
}

const HTTPRequestMSG& TCPSegment::getHTTPRequestMSG() const {
    return httpRequestMSG;
}

void TCPSegment::setHTTPRequestMSG(const HTTPRequestMSG& newHTTPRequestMSG) {
    httpRequestMSG = newHTTPRequestMSG;
}

void TCPSegment::toString() const {
    const TCPHeader& tcpHeader = getTCPHeader();
    std::cout << "\nTCP Header:" << std::endl;
    std::cout << "Source port: " << unsigned(tcpHeader.getSourcePort()) << std::endl;
    std::cout << "Destination port: " << unsigned(tcpHeader.getDestinationPort()) << std::endl;
    std::cout << "Sequence number: " << unsigned(tcpHeader.getSequenceNumber()) << std::endl;
    std::cout << "Acknowledgment number: " << unsigned(tcpHeader.getAcknowledgmentNumber()) << std::endl;
    std::cout << "Data offset: " << unsigned(tcpHeader.getDataOffset()) << std::endl;
    std::cout << "Flags: " << unsigned(tcpHeader.getFlags()) << std::endl;
    std::cout << "Window size: " << unsigned(tcpHeader.getWindowSize()) << std::endl;
    std::cout << "Checksum: " << unsigned(tcpHeader.getChecksum()) << std::endl;
    std::cout << "Urgent pointer: " << unsigned(tcpHeader.getUrgentPointer()) << std::endl;
}

void TCPSegment::initializeTCPHeaderDefaults() {
    tcpHeader.setSourcePort(12345);
    tcpHeader.setDestinationPort(80);
    tcpHeader.setSequenceNumber(0);
    tcpHeader.setAcknowledgmentNumber(0);
    tcpHeader.setDataOffset(5);
    tcpHeader.setFlags(0x02); // SYN flag
    tcpHeader.setWindowSize(65535);
    tcpHeader.setChecksum(0);
    tcpHeader.setUrgentPointer(0);
}