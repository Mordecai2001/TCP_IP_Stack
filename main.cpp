#include "HTTPRequestMSG.h"
#include "TCPSegment.h"
#include "IPPacket.h"
#include "MACFrame.h"
#include <iostream>

int main() {
    // Test the implementation
    HTTPRequestMSG httpRequest;
    httpRequest.readFile("http_get_request.txt");

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

    return 0;
}
