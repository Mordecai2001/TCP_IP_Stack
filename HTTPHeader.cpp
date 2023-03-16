#include "HTTPHeader.h"

void HTTPHeader::setHeaderField(const std::string& key, const std::string& value) {
    headerFields[key] = value;
}

std::string HTTPHeader::getHeaderField(const std::string& key) const {
    auto it = headerFields.find(key);
    if (it != headerFields.end()) {
        return it->second;
    }
    return "";
}

const std::map<std::string, std::string>& HTTPHeader::getHeaderFields() const {
    return headerFields;
}
