#pragma once
#include <string>
#include <cstdint>

class IPHeader {
public:
    // Getters
    uint8_t getVersion() const;
    uint8_t getHeaderLength() const;
    uint8_t getTypeOfService() const;
    uint16_t getTotalLength() const;
    uint16_t getIdentification() const;
    uint8_t getFlags() const;
    uint16_t getFragmentOffset() const;
    uint8_t getTimeToLive() const;
    uint8_t getProtocol() const;
    uint16_t getChecksum() const;
    std::string getSourceIP() const;
    std::string getDestinationIP() const;

    // Setters
    void setVersion(uint8_t ver);
    void setHeaderLength(uint8_t length);
    void setTypeOfService(uint8_t service);
    void setTotalLength(uint16_t length);
    void setIdentification(uint16_t id);
    void setFlags(uint8_t flgs);
    void setFragmentOffset(uint16_t offset);
    void setTimeToLive(uint8_t ttl);
    void setProtocol(uint8_t proto);
    void setChecksum(uint16_t chksum);
    void setSourceIP(const std::string& srcIP);
    void setDestinationIP(const std::string& destIP);

private:
    uint8_t version;
    uint8_t headerLength;
    uint8_t typeOfService;
    uint16_t totalLength;
    uint16_t identification;
    uint8_t flags;
    uint16_t fragmentOffset;
    uint8_t timeToLive;
    uint8_t protocol;
    uint16_t checksum;
    std::string sourceIP;
    std::string destinationIP;
};
