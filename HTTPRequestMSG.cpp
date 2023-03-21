#include "HTTPRequestMSG.h"

void HTTPRequestMSG::readFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Read and parse the request line
    std::string requestLine;
    std::getline(file, requestLine);
    parseRequestLine(requestLine);

    // Read and parse the header fields
    std::string line;
    while (std::getline(file, line)) {
        if (line == "\r" || line.empty()) {
            break; // End of headers
        }
        parseHeaderField(line);
    }

    file.close();
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

void HTTPRequestMSG::print() const {
    std::cout << "\nRequest method: " << getRequestMethod() << std::endl;
    std::cout << "Request headers:\n";
    for (const auto& header : getHeaders()) {
        std::cout << header.first << ": " << header.second << std::endl;
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

