#pragma once
#include <vector>
#include <string>
#include "MACHeader.h"
#include "IPPacket.h"
#include "Protocol.h"

class MACFrame : public Protocol {
public:
    void encapsulateIPPacket(const IPPacket& ipPacket);

    const MACHeader& getMACHeader() const;
    void setMACHeader(const MACHeader& newMACHeader);

    const IPPacket& getIPPacket() const;
    void setIPPacket(const IPPacket& newIPPacket);

    void toString() const;
    void printMACAddress(uint64_t macAddress) const;
    const std::string& getSerializedHTTPRequest() const;
    void setSerializedHTTPRequest(const std::string& serializedHTTPRequest);

private:
    void initializeMACHeaderDefaults();

    MACHeader macHeader;
    IPPacket ipPacket;
    std::string serializedHTTPRequest;
};


