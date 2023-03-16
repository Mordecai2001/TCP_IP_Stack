#pragma once
#include <string>
#include <map>

class HTTPHeader {
public:
    void setHeaderField(const std::string& key, const std::string& value);
    std::string getHeaderField(const std::string& key) const;
    const std::map<std::string, std::string>& getHeaderFields() const;

private:
    std::map<std::string, std::string> headerFields;
};
