#include "IPHeader.h"

// Getters
uint8_t IPHeader::getVersion() const {
    return version;
}

uint8_t IPHeader::getHeaderLength() const {
    return headerLength;
}

uint8_t IPHeader::getTypeOfService() const {
    return typeOfService;
}

uint16_t IPHeader::getTotalLength() const {
    return totalLength;
}

uint16_t IPHeader::getIdentification() const {
    return identification;
}

uint8_t IPHeader::getFlags() const {
    return flags;
}

uint16_t IPHeader::getFragmentOffset() const {
    return fragmentOffset;
}

uint8_t IPHeader::getTimeToLive() const {
    return timeToLive;
}

uint8_t IPHeader::getProtocol() const {
    return protocol;
}

uint16_t IPHeader::getChecksum() const {
    return checksum;
}

std::string IPHeader::getSourceIP() const {
    return sourceIP;
}

std::string IPHeader::getDestinationIP() const {
    return destinationIP;
}

// Setters
void IPHeader::setVersion(uint8_t ver) {
    version = ver;
}

void IPHeader::setHeaderLength(uint8_t length) {
    headerLength = length;
}

void IPHeader::setTypeOfService(uint8_t service) {
    typeOfService = service;
}

void IPHeader::setTotalLength(uint16_t length) {
    totalLength = length;
}

void IPHeader::setIdentification(uint16_t id) {
    identification = id;
}

void IPHeader::setFlags(uint8_t flgs) {
    flags = flgs;
}
void IPHeader::setFragmentOffset(uint16_t offset) {
    fragmentOffset = offset;
}

void IPHeader::setTimeToLive(uint8_t ttl) {
    timeToLive = ttl;
}

void IPHeader::setProtocol(uint8_t proto) {
    protocol = proto;
}

void IPHeader::setChecksum(uint16_t chksum) {
    checksum = chksum;
}

void IPHeader::setSourceIP(const std::string& srcIP) {
    sourceIP = srcIP;
}

void IPHeader::setDestinationIP(const std::string& destIP) {
    destinationIP = destIP;
}
