#include "HTTPRequestMSG.h"
#include "TCPSegment.h"
#include "IPPacket.h"
#include "MACFrame.h"
#include "SerializedData.h"
#include <iostream>
#include <bitset>

int main() {
    // Test the implementation
    HTTPRequestMSG httpRequest;
    httpRequest.readFile("http_post_request.txt");

    // Print the HTTPRequestMSG
    std::cout << "HTTPRequestMSG:\n";
    httpRequest.print();

    // Create a TCPSegment
    TCPSegment tcpSegment;
    tcpSegment.encapsulateHTTPRequestMSG(httpRequest);

    // Print the TCPSegment
    std::cout << "\nTCPSegment:\n";
    tcpSegment.print();

    // Create an IPPacket
    IPPacket ipPacket;
    ipPacket.encapsulateTCPSegment(tcpSegment);

    // Print the IPPacket
    std::cout << "\nIPPacket:\n";
    ipPacket.print();

    //create a MACFrame
    MACFrame macFrame;
    macFrame.encapsulateIPPacket(ipPacket);

    //print the MACFrame
    std::cout << "\nMACFrame:\n";
    macFrame.print();

    
    // Create an instance of SerializedData
    SerializedData serializedData;

    // Call the serialize function on the MACFrame
    std::vector<uint8_t> binaryData = serializedData.serialize(macFrame);

    // Print the binary data
    std::cout << "Serialized binary data:" << std::endl;
    for (const auto& byte : binaryData) {
        std::cout << std::bitset<8>(byte) << " ";
    }
    std::cout << std::endl;
    
    // Deserialize the MACFrame
    MACFrame deserializedMACFrame = serializedData.deserialize(binaryData);
    std::cout << "\nDeserialized MACFrame:\n";
    deserializedMACFrame.print();

    // Retrieve the deserialized IPPacket from the deserialized MACFrame
    IPPacket deserializedIPPacket = deserializedMACFrame.getIPPacket();

    // Print the deserialized IPPacket
    std::cout << "\nDeserialized IPPacket:\n";
    deserializedIPPacket.print();

    // Retrieve the deserialized TCPSegment from the deserialized IPPacket
    TCPSegment deserializedTCPSegment = deserializedIPPacket.getTCPSegment();

    // Print the deserialized TCPSegment
    std::cout << "\nDeserialized TCPSegment:\n";
    deserializedTCPSegment.print();

    // Retrieve the deserialized HTTPRequestMSG from the deserialized TCPSegment
    HTTPRequestMSG deserializedHTTPRequest = deserializedTCPSegment.getHTTPRequestMSG();

    // Print the deserialized HTTPRequestMSG
    std::cout << "\nDeserialized HTTPRequestMSG:\n";
    deserializedHTTPRequest.print();
    
}

