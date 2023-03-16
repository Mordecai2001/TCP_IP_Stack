#pragma once
#include <cstdint>

class MACHeader {
public:
    // Constructors
    MACHeader();
    MACHeader(uint64_t srcMAC, uint64_t destMAC);

    // Getters
    uint64_t getSourceMAC() const;
    uint64_t getDestinationMAC() const;

    // Setters
    void setSourceMAC(uint64_t srcMAC);
    void setDestinationMAC(uint64_t destMAC);

private:
    uint64_t sourceMAC;
    uint64_t destinationMAC;
};
