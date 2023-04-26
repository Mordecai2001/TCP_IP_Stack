#include "HTTPRequestMSG.h"

void HTTPRequestMSG::readFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Error opening file");
    }

    std::string line;
    bool isRequestLine = true;
    bool isHeader = true;

    while (std::getline(inputFile, line)) {
        if (isRequestLine) {
            parseRequestLine(line);
            isRequestLine = false;
        }
        else if (isHeader) {
            if (line.empty()) {
                isHeader = false;
            }
            else {
                parseHeaderField(line);
            }
        }
        else {
            // Read the body content
            body += line;
            if (!inputFile.eof()) {
                body += "\n";
            }
        }
    }

    inputFile.close();
}


std::string HTTPRequestMSG::getRequestMethod() const {
    return method;
}

std::string HTTPRequestMSG::getHttpVersion() const {
    return httpVersion;
}

std::string HTTPRequestMSG::getUri() const {
    return uri;
}

const std::map<std::string, std::string>& HTTPRequestMSG::getHeaders() const {
    return httpHeader.getHeaderFields();
}

const std::string& HTTPRequestMSG::getBody() const {
    return body;
}

void HTTPRequestMSG::setBody(const std::string& newBody) {
    body = newBody;
}

void HTTPRequestMSG::toString() const {
    std::cout<<"\n" << getRequestMethod() << getUri() << getHttpVersion() << std::endl;
    for (const auto& header : getHeaders()) {
        std::cout << header.first << ": " << header.second << std::endl;
    }
    if (!getBody().empty()) {
        std::cout << "\nBody:\n" << getBody() << std::endl;
    }
}

void HTTPRequestMSG::parseRequestLine(const std::string& line) {
    std::istringstream iss(line);
    iss >> method >> uri >> httpVersion;
}

void HTTPRequestMSG::parseHeaderField(const std::string& line) {
    std::istringstream iss(line);
    std::string key, value;

    std::getline(iss, key, ':');
    std::getline(iss, value);

    // Remove leading and trailing whitespaces
    value.erase(0, value.find_first_not_of(" "));
    value.erase(value.find_last_not_of(" \r") + 1);

    httpHeader.setHeaderField(key, value);
}

void HTTPRequestMSG::parseSerializedHTTPRequest(const std::string& serializedHTTPRequest) {
    std::istringstream inputStream(serializedHTTPRequest);
    std::string line;

    // Parse the request line
    std::getline(inputStream, line);
    parseRequestLine(line);

    // Parse the header fields
    while (std::getline(inputStream, line) && line != "\r") {
        parseHeaderField(line);
    }

    // If there is a body, read it (for POST requests)
    if (method == "POST") {
        std::string postData;
        std::getline(inputStream, postData);
        // Here, you can handle the POST data as required
    }
}

