#pragma once
#include <iostream>
#include <string>
#include "HTTPRequestMSG.h"
#include "TCPHeader.h"

class TCPSegment : public Protocol {
public:
    void encapsulateHTTPRequestMSG(const HTTPRequestMSG& httpRequest);

    const TCPHeader& getTCPHeader() const;
    void setTCPHeader(const TCPHeader& newTCPHeader);

    const HTTPRequestMSG& getHTTPRequestMSG() const;
    void setHTTPRequestMSG(const HTTPRequestMSG& newHTTPRequestMSG);

    void print() const;


private:
    void initializeTCPHeaderDefaults();

    TCPHeader tcpHeader;
    HTTPRequestMSG httpRequestMSG;
};

