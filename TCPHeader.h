#pragma once
#include <cstdint>

class TCPHeader {
public:
    // Constructors
    TCPHeader();
    TCPHeader(uint16_t srcPort, uint16_t destPort, uint32_t seqNum, uint32_t ackNum, uint8_t offset,
        uint8_t flgs, uint16_t wndSize, uint16_t chksum, uint16_t urgPtr);

    // Getters
    uint16_t getSourcePort() const;
    uint16_t getDestinationPort() const;
    uint32_t getSequenceNumber() const;
    uint32_t getAcknowledgmentNumber() const;
    uint8_t getDataOffset() const;
    uint8_t getFlags() const;
    uint16_t getWindowSize() const;
    uint16_t getChecksum() const;
    uint16_t getUrgentPointer() const;

    // Setters
    void setSourcePort(uint16_t srcPort);
    void setDestinationPort(uint16_t destPort);
    void setSequenceNumber(uint32_t seqNum);
    void setAcknowledgmentNumber(uint32_t ackNum);
    void setDataOffset(uint8_t offset);
    void setFlags(uint8_t flgs);
    void setWindowSize(uint16_t wndSize);
    void setChecksum(uint16_t chksum);
    void setUrgentPointer(uint16_t urgPtr);

private:
    uint16_t sourcePort;
    uint16_t destinationPort;
    uint32_t sequenceNumber;
    uint32_t acknowledgmentNumber;
    uint8_t dataOffset;
    uint8_t flags;
    uint16_t windowSize;
    uint16_t checksum;
    uint16_t urgentPointer;
};


