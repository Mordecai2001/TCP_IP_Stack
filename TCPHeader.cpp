#include "TCPHeader.h"

TCPHeader::TCPHeader()
    : sourcePort(0),
    destinationPort(0),
    sequenceNumber(0),
    acknowledgmentNumber(0),
    dataOffset(5),
    flags(0),
    windowSize(0),
    checksum(0),
    urgentPointer(0) {}

TCPHeader::TCPHeader(uint16_t srcPort, uint16_t destPort, uint32_t seqNum, uint32_t ackNum,
    uint8_t offset, uint8_t flgs, uint16_t wndSize, uint16_t chksum,
    uint16_t urgPtr)
    : sourcePort(srcPort),
    destinationPort(destPort),
    sequenceNumber(seqNum),
    acknowledgmentNumber(ackNum),
    dataOffset(offset),
    flags(flgs),
    windowSize(wndSize),
    checksum(chksum),
    urgentPointer(urgPtr) {}

uint16_t TCPHeader::getSourcePort() const { return sourcePort; }
uint16_t TCPHeader::getDestinationPort() const { return destinationPort; }
uint32_t TCPHeader::getSequenceNumber() const { return sequenceNumber; }
uint32_t TCPHeader::getAcknowledgmentNumber() const { return acknowledgmentNumber; }
uint8_t TCPHeader::getDataOffset() const { return dataOffset; }
uint8_t TCPHeader::getFlags() const { return flags; }
uint16_t TCPHeader::getWindowSize() const { return windowSize; }
uint16_t TCPHeader::getChecksum() const { return checksum; }
uint16_t TCPHeader::getUrgentPointer() const { return urgentPointer; }
void TCPHeader::setSourcePort(uint16_t srcPort) { sourcePort = srcPort; }
void TCPHeader::setDestinationPort(uint16_t destPort) { destinationPort = destPort; }
void TCPHeader::setSequenceNumber(uint32_t seqNum) { sequenceNumber = seqNum; }
void TCPHeader::setAcknowledgmentNumber(uint32_t ackNum) { acknowledgmentNumber = ackNum; }
void TCPHeader::setDataOffset(uint8_t offset) { dataOffset = offset; }
void TCPHeader::setFlags(uint8_t flgs) { flags = flgs; }
void TCPHeader::setWindowSize(uint16_t wndSize) { windowSize = wndSize; }
void TCPHeader::setChecksum(uint16_t chksum) { checksum = chksum; }
void TCPHeader::setUrgentPointer(uint16_t urgPtr) { urgentPointer = urgPtr; }
