#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "Protocol.h"
#include "HTTPHeader.h"

class HTTPRequestMSG : public Protocol {
public:
    void readFile(const std::string& filename);
    std::string getRequestMethod() const;
    const std::map<std::string, std::string>& getHeaders() const;
    void print() const;

private:
    void parseRequestLine(const std::string& line);
    void parseHeaderField(const std::string& line);

    std::string method;
    std::string uri;
    std::string httpVersion;
    HTTPHeader httpHeader;
};

