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
    std::string getHttpVersion() const;
    std::string getUri() const;
    const std::map<std::string, std::string>& getHeaders() const;
    const std::string& getBody() const;
    void setBody(const std::string& newBody);
    void toString() const;
    void parseRequestLine(const std::string& line);
    void parseHeaderField(const std::string& line);
    void parseSerializedHTTPRequest(const std::string& serializedHTTPRequest);

private:

    std::string method;
    std::string uri;
    std::string httpVersion;
    HTTPHeader httpHeader;
    std::string body;
};
