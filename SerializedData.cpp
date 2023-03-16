#include "SerializedData.h"


std::vector<uint8_t> SerializedData::serialize(const MACFrame& macFrame) {
    std::vector<uint8_t> serializedData;

    // Serialize the MACHeader
    uint64_t srcMAC = macFrame.getMACHeader().getSourceMAC();
    uint64_t destMAC = macFrame.getMACHeader().getDestinationMAC();

    for (int i = 5; i >= 0; --i) {
        serializedData.push_back((srcMAC >> (i * 8)) & 0xFF);
    }

    for (int i = 5; i >= 0; --i) {
        serializedData.push_back((destMAC >> (i * 8)) & 0xFF);
    }

    // Serialize the IPPacket and its components
    // Serialize the IPHeader
    const IPHeader& ipHeader = macFrame.getIPPacket().getIPHeader();
    uint8_t versionAndHeaderLength = (ipHeader.getVersion() << 4) | ipHeader.getHeaderLength();
    serializedData.push_back(versionAndHeaderLength);
    serializedData.push_back(ipHeader.getTypeOfService());
    serializedData.push_back((ipHeader.getTotalLength() >> 8) & 0xFF);
    serializedData.push_back(ipHeader.getTotalLength() & 0xFF);
    serializedData.push_back((ipHeader.getIdentification() >> 8) & 0xFF);
    serializedData.push_back(ipHeader.getIdentification() & 0xFF);
    serializedData.push_back(ipHeader.getFlags());
    serializedData.push_back((ipHeader.getFragmentOffset() >> 8) & 0xFF);
    serializedData.push_back(ipHeader.getFragmentOffset() & 0xFF);
    serializedData.push_back(ipHeader.getTimeToLive());
    serializedData.push_back(ipHeader.getProtocol());
    serializedData.push_back((ipHeader.getChecksum() >> 8) & 0xFF);
    serializedData.push_back(ipHeader.getChecksum() & 0xFF);

    // Serialize the source and destination IP addresses
    std::istringstream srcIPStream(ipHeader.getSourceIP());
    std::istringstream destIPStream(ipHeader.getDestinationIP());
    uint8_t octet;
    while (srcIPStream >> octet) {
        serializedData.push_back(octet);
        if (srcIPStream.peek() == '.') {
            srcIPStream.ignore();
        }
    }
    while (destIPStream >> octet) {
        serializedData.push_back(octet);
        if (destIPStream.peek() == '.') {
            destIPStream.ignore();
        }
    }

    // Serialize the TCPSegment and its components
    // Serialize the TCPHeader
    const TCPHeader& tcpHeader = macFrame.getIPPacket().getTCPSegment().getTCPHeader();
    serializedData.push_back((tcpHeader.getSourcePort() >> 8) & 0xFF);
    serializedData.push_back(tcpHeader.getSourcePort() & 0xFF);
    serializedData.push_back((tcpHeader.getDestinationPort() >> 8) & 0xFF);
    serializedData.push_back(tcpHeader.getDestinationPort() & 0xFF);
    serializedData.push_back((tcpHeader.getSequenceNumber() >> 24) & 0xFF);
    serializedData.push_back((tcpHeader.getSequenceNumber() >> 16) & 0xFF);
    serializedData.push_back((tcpHeader.getSequenceNumber() >> 8) & 0xFF);
    serializedData.push_back(tcpHeader.getSequenceNumber() & 0xFF);
    serializedData.push_back((tcpHeader.getAcknowledgmentNumber() >> 24) & 0xFF);
    serializedData.push_back((tcpHeader.getAcknowledgmentNumber() >> 16) & 0xFF);
    serializedData.push_back((tcpHeader.getAcknowledgmentNumber() >> 8) & 0xFF);
    serializedData.push_back(tcpHeader.getAcknowledgmentNumber() & 0xFF);
    serializedData.push_back(tcpHeader.getDataOffset() << 4);
    serializedData.push_back(tcpHeader.getFlags());
    serializedData.push_back((tcpHeader.getWindowSize() >> 8) & 0xFF);
    serializedData.push_back(tcpHeader.getWindowSize() & 0xFF);
    serializedData.push_back((tcpHeader.getChecksum() >> 8) & 0xFF);
    serializedData.push_back(tcpHeader.getChecksum() & 0xFF);
    serializedData.push_back((tcpHeader.getUrgentPointer() >> 8) & 0xFF);
    serializedData.push_back(tcpHeader.getUrgentPointer() & 0xFF);

    // Serialize the HTTPRequestMSG
    const HTTPRequestMSG& httpRequestMsg = macFrame.getIPPacket().getTCPSegment().getHTTPRequestMSG();
    const std::map<std::string, std::string>& httpRequestHeaders = httpRequestMsg.getHeaders();

    for (const auto& header : httpRequestHeaders) {
        std::string headerLine = header.first + ": " + header.second + "\r\n";
        for (char c : headerLine) {
            serializedData.push_back(static_cast<uint8_t>(c));
        }
    }

    // Add a blank line to indicate the end of headers
    serializedData.push_back('\r');
    serializedData.push_back('\n');

    return serializedData;
}

MACFrame SerializedData::deserialize(const std::vector<uint8_t>& serializedData) {
    MACFrame macFrame;

    // Deserialize the MACHeader
    uint64_t srcMAC = 0;
    uint64_t destMAC = 0;

    for (int i = 5, j = 0; i >= 0; --i, j += 2) {
        srcMAC |= (static_cast<uint64_t>(serializedData[j]) << (i * 8));
        destMAC |= (static_cast<uint64_t>(serializedData[j + 1]) << (i * 8));
    }

    MACHeader macHeader;
    macHeader.setSourceMAC(srcMAC);
    macHeader.setDestinationMAC(destMAC);
    macFrame.setMACHeader(macHeader);

    // Deserialize the IPPacket and its components
    IPPacket ipPacket;

    // Deserialize the IPHeader
    IPHeader ipHeader;
    size_t index = 12;

    uint8_t versionAndHeaderLength = serializedData[index++];
    ipHeader.setVersion(versionAndHeaderLength >> 4);
    ipHeader.setHeaderLength(versionAndHeaderLength & 0xF);
    ipHeader.setTypeOfService(serializedData[index++]);
    ipHeader.setTotalLength((serializedData[index] << 8) | serializedData[index + 1]);
    index += 2;
    ipHeader.setIdentification((serializedData[index] << 8) | serializedData[index + 1]);
    index += 2;
    ipHeader.setFlags(serializedData[index++]);
    ipHeader.setFragmentOffset((serializedData[index] << 8) | serializedData[index + 1]);
    index += 2;
    ipHeader.setTimeToLive(serializedData[index++]);
    ipHeader.setProtocol(serializedData[index++]);
    ipHeader.setChecksum((serializedData[index] << 8) | serializedData[index + 1]);
    index += 2;

    // Deserialize the source and destination IP addresses
    std::ostringstream srcIPStream;
    std::ostringstream destIPStream;
    for (int i = 0; i < 4; ++i) {
        srcIPStream << static_cast<uint32_t>(serializedData[index++]);
        if (i < 3) {
            srcIPStream << '.';
        }
    }
    for (int i = 0; i < 4; ++i) {
        destIPStream << static_cast<uint32_t>(serializedData[index++]);
        if (i < 3) {
            destIPStream << '.';
        }
    }

    ipHeader.setSourceIP(srcIPStream.str());
    ipHeader.setDestinationIP(destIPStream.str());
    ipPacket.setIPHeader(ipHeader);
    // Deserialize the TCPSegment and its components
    TCPSegment tcpSegment;

    // Deserialize the TCPHeader
    TCPHeader tcpHeader;
    tcpHeader.setSourcePort((serializedData[index] << 8) | serializedData[index + 1]);
    index += 2;
    tcpHeader.setDestinationPort((serializedData[index] << 8) | serializedData[index + 1]);
    index += 2;
    tcpHeader.setSequenceNumber((serializedData[index] << 24) | (serializedData[index + 1] << 16) | (serializedData[index + 2] << 8) | serializedData[index + 3]);
    index += 4;
    tcpHeader.setAcknowledgmentNumber((serializedData[index] << 24) | (serializedData[index + 1] << 16) | (serializedData[index + 2] << 8) | serializedData[index + 3]);
    index += 4;
    uint8_t dataOffsetAndReserved = serializedData[index++];
    tcpHeader.setDataOffset(dataOffsetAndReserved >> 4);
    tcpHeader.setFlags(serializedData[index++]);
    tcpHeader.setWindowSize((serializedData[index] << 8) | serializedData[index + 1]);
    index += 2;
    tcpHeader.setChecksum((serializedData[index] << 8) | serializedData[index + 1]);
    index += 2;
    tcpHeader.setUrgentPointer((serializedData[index] << 8) | serializedData[index + 1]);
    index += 2;
    tcpSegment.setTCPHeader(tcpHeader);

    // Deserialize the HTTPRequestMsg
    HTTPRequestMSG httpRequestMsg;

    std::string serializedHTTPRequest;
    for (; index < serializedData.size(); ++index) {
        serializedHTTPRequest.push_back(static_cast<char>(serializedData[index]));
    }
    macFrame.setSerializedHTTPRequest(serializedHTTPRequest);

    // Set the HTTPRequestMsg in the TCPSegment
    tcpSegment.setHTTPRequestMSG(httpRequestMsg);

    // Set the deserialized TCPSegment into the IPPacket
    ipPacket.setTCPSegment(tcpSegment);

    // Set the deserialized IPPacket into the MACFrame
    macFrame.setIPPacket(ipPacket);

    return macFrame;
}

