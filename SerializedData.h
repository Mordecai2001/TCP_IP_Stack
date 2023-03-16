#pragma once
#include <vector>
#include "MACFrame.h"

class SerializedData {
public:
    SerializedData() = default;
    SerializedData(const MACFrame& macFrame) : macFrame(macFrame){}
    std::vector<uint8_t> serialize(const MACFrame& macFrame);
    MACFrame deserialize(const std::vector<uint8_t>& data);

private:
    MACFrame macFrame;
};
