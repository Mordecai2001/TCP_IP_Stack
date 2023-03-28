#include "SerializedData.h"
#include <iostream>

std::vector<uint8_t> SerializedData::serialize(const MACFrame& macFrame) {
    std::vector<uint8_t> data;

    // Serialize MACHeader
    uint64_t srcMAC = macFrame.getMACHeader().getSourceMAC();
    uint64_t destMAC = macFrame.getMACHeader().getDestinationMAC();
    for (int i = 7; i >= 0; --i) {
        data.push_back((srcMAC >> (8 * i)) & 0xFF);
        data.push_back((destMAC >> (8 * i)) & 0xFF);
    }

    // Serialize IPPacket and its components
    const IPPacket& ipPacket = macFrame.getIPPacket();
    const IPHeader& ipHeader = ipPacket.getIPHeader();
    const TCPSegment& tcpSegment = ipPacket.getTCPSegment();
    const TCPHeader& tcpHeader = tcpSegment.getTCPHeader();

    // Serialize IPHeader
    data.push_back((ipHeader.getVersion() << 4) | ipHeader.getHeaderLength());
    data.push_back(ipHeader.getTypeOfService());
    uint16_t totalLength = ipHeader.getTotalLength();
    data.push_back(totalLength >> 8);
    data.push_back(totalLength & 0xFF);
    uint16_t identification = ipHeader.getIdentification();
    data.push_back(identification >> 8);
    data.push_back(identification & 0xFF);
    data.push_back((ipHeader.getFlags() << 5) | (ipHeader.getFragmentOffset() >> 8));
    data.push_back(ipHeader.getFragmentOffset() & 0xFF);
    data.push_back(ipHeader.getTimeToLive());
    data.push_back(ipHeader.getProtocol());
    uint16_t checksum = ipHeader.getChecksum();
    data.push_back(checksum >> 8);
    data.push_back(checksum & 0xFF);

    // Serialize IP addresses as 4-byte values
    const std::string& sourceIP = ipHeader.getSourceIP();
    const std::string& destinationIP = ipHeader.getDestinationIP();
    std::stringstream srcIPStream(sourceIP);
    std::stringstream destIPStream(destinationIP);
    uint32_t octet;
    char dot;

    for (int i = 0; i < 4; ++i) {
        srcIPStream >> octet;
        data.push_back(static_cast<uint8_t>(octet));
        if (i < 3) srcIPStream >> dot;
    }
    for (int i = 0; i < 4; ++i) {
        destIPStream >> octet;
        data.push_back(static_cast<uint8_t>(octet));
        if (i < 3) destIPStream >> dot;
    }


    // Serialize TCPHeader
    uint16_t sourcePort = tcpHeader.getSourcePort();
    uint16_t destinationPort = tcpHeader.getDestinationPort();
    data.push_back(sourcePort >> 8);
    data.push_back(sourcePort & 0xFF);
    data.push_back(destinationPort >> 8);
    data.push_back(destinationPort & 0xFF);

    uint32_t sequenceNumber = tcpHeader.getSequenceNumber();
    uint32_t acknowledgmentNumber = tcpHeader.getAcknowledgmentNumber();
    // Serialize sequence number and acknowledgment number
    for (int i = 3; i >= 0; --i) {
        data.push_back((sequenceNumber >> (8 * i)) & 0xFF);
        data.push_back((acknowledgmentNumber >> (8 * i)) & 0xFF);
    }

    // Serialize data offset, flags, window size, checksum, and urgent pointer
    data.push_back((tcpHeader.getDataOffset() << 4) | (tcpHeader.getFlags() >> 4));
    data.push_back(tcpHeader.getFlags() & 0x0F);
    uint16_t windowSize = tcpHeader.getWindowSize();
    data.push_back(windowSize >> 8);
    data.push_back(windowSize & 0xFF);
    uint16_t tcpChecksum = tcpHeader.getChecksum();
    data.push_back(tcpChecksum >> 8);
    data.push_back(tcpChecksum & 0xFF);
    uint16_t urgentPointer = tcpHeader.getUrgentPointer();
    data.push_back(urgentPointer >> 8);
    data.push_back(urgentPointer & 0xFF);

    // Serialize HTTPRequestMSG (as a string)
    const HTTPRequestMSG& httpRequest = tcpSegment.getHTTPRequestMSG();
    const std::map<std::string, std::string>& headers = httpRequest.getHeaders();
    std::stringstream httpRequestStream;
    httpRequestStream << httpRequest.getRequestMethod() << " "
        << httpRequest.getUri() << " "
        << httpRequest.getHttpVersion() << "\r\n";
    for (const auto& header : headers) {
        httpRequestStream << header.first << ": " << header.second << "\r\n";
    }
    httpRequestStream << "\r\n";

    const std::string& httpRequestString = httpRequestStream.str();
    for (const char& c : httpRequestString) {
        data.push_back(static_cast<uint8_t>(c));
    }

    // Serialize HTTP body
    const std::string& httpBody = httpRequest.getBody();
    for (const char& c : httpBody) {
        data.push_back(static_cast<uint8_t>(c));
    }

    return data;
}

MACFrame SerializedData::deserialize(const std::vector<uint8_t>& data) {
    size_t index = 0;

    // Deserialize MACHeader
    uint64_t srcMAC = 0;
    uint64_t destMAC = 0;
    for (int i = 7; i >= 0; --i) {
        srcMAC |= static_cast<uint64_t>(data[index++]) << (8 * i);
        destMAC |= static_cast<uint64_t>(data[index++]) << (8 * i);
    }
    MACHeader macHeader(srcMAC, destMAC);

    // Deserialize IPPacket and its components
    IPHeader ipHeader;
    ipHeader.setVersion(data[index] >> 4);
    ipHeader.setHeaderLength(data[index++] & 0x0F);
    ipHeader.setTypeOfService(data[index++]);
    ipHeader.setTotalLength((data[index] << 8) | data[index + 1]);
    index += 2;
    ipHeader.setIdentification((data[index] << 8) | data[index + 1]);
    index += 2;
    ipHeader.setFlags(data[index] >> 5);
    ipHeader.setFragmentOffset(((data[index] & 0x1F) << 8) | data[index + 1]);
    index += 2;
    ipHeader.setTimeToLive(data[index++]);
    ipHeader.setProtocol(data[index++]);
    ipHeader.setChecksum((data[index] << 8) | data[index + 1]);
    index += 2;

    // Deserialize IP addresses
    std::stringstream srcIPStream;
    std::stringstream destIPStream;
    for (int i = 0; i < 4; ++i) {
        srcIPStream << static_cast<uint32_t>(data[index]);
        if (i < 3) srcIPStream << '.';
        index++;
    }
    for (int i = 0; i < 4; ++i) {
        destIPStream << static_cast<uint32_t>(data[index]);
        if (i < 3) destIPStream << '.';
        index++;
    }
    ipHeader.setSourceIP(srcIPStream.str());
    ipHeader.setDestinationIP(destIPStream.str());


    // Deserialize TCPHeader
    TCPHeader tcpHeader;
    tcpHeader.setSourcePort((data[index] << 8) | data[index + 1]);
    index += 2;
    tcpHeader.setDestinationPort((data[index] << 8) | data[index + 1]);
    index += 2;

    uint32_t seqNum = 0;
    uint32_t ackNum = 0;
    for (int i = 3; i >= 0; --i) {
        seqNum |= (static_cast<uint32_t>(data[index++]) << (8 * i));
        ackNum |= (static_cast<uint32_t>(data[index++]) << (8 * i));
    }
    tcpHeader.setSequenceNumber(seqNum);
    tcpHeader.setAcknowledgmentNumber(ackNum);

    tcpHeader.setDataOffset(data[index] >> 4);
    tcpHeader.setFlags((data[index++] & 0x0F) << 4 | data[index++]);
    tcpHeader.setWindowSize((data[index] << 8) | data[index + 1]);
    index += 2;
    tcpHeader.setChecksum((data[index] << 8) | data[index + 1]);
    index += 2;
    tcpHeader.setUrgentPointer((data[index] << 8) | data[index + 1]);
    index += 2;

    // Deserialize HTTPRequestMSG
    std::string httpRequestString(data.begin() + index, data.end());
    HTTPRequestMSG httpRequest;
    httpRequest.parseSerializedHTTPRequest(httpRequestString);

    // Find the end of the HTTP headers
    size_t endOfHeaders = httpRequestString.find("\r\n\r\n");
    if (endOfHeaders != std::string::npos) {
        endOfHeaders += 4; // Move past the "\r\n\r\n" separator
    }
    else {
        endOfHeaders = httpRequestString.size();
    }

    // Deserialize HTTP body
    std::string httpBody(data.begin() + index + endOfHeaders, data.end());
    httpRequest.setBody(httpBody);

    index += endOfHeaders;


    // Reconstruct TCPSegment, IPPacket, and MACFrame
    TCPSegment tcpSegment;
    tcpSegment.setTCPHeader(tcpHeader);
    tcpSegment.setHTTPRequestMSG(httpRequest);

    IPPacket ipPacket;
    ipPacket.setIPHeader(ipHeader);
    ipPacket.setTCPSegment(tcpSegment);

    MACFrame macFrame;
    macFrame.setMACHeader(macHeader);
    macFrame.setIPPacket(ipPacket);

    return macFrame;
}


