#pragma once
#include "Protocol.h"
#include "IPHeader.h"
#include "TCPSegment.h"

class IPPacket : public Protocol {
public:
    void encapsulateTCPSegment(const TCPSegment& tcpSegment);
    const IPHeader& getIPHeader() const;
    void setIPHeader(const IPHeader& newIPHeader);
    const TCPSegment& getTCPSegment() const;
    void setTCPSegment(const TCPSegment& newTCPSegment);
    void toString() const;

private:
    void initializeIPHeaderDefaults();

    IPHeader ipHeader;
    TCPSegment tcpSegment;
};


