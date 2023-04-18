#include "pch.h"
#include "../HTTPRequestMSG.h"

TEST(HTTPRequestMSGTest, ParseRequestLine) {
    HTTPRequestMSG httpRequest;

    httpRequest.parseRequestLine("GET /index.html HTTP/1.1");

    ASSERT_EQ("GET", httpRequest.getRequestMethod());
    ASSERT_EQ("/index.html", httpRequest.getUri());
    ASSERT_EQ("HTTP/1.1", httpRequest.getHttpVersion());
}

TEST(HTTPRequestMSGTest, ParseHeaderField) {
    HTTPRequestMSG httpRequest;

    httpRequest.parseHeaderField("Content-Type: application/json");

    const std::map<std::string, std::string>& headers = httpRequest.getHeaders();
    ASSERT_EQ(1, headers.size());
    ASSERT_EQ("application/json", headers.at("Content-Type"));
}

TEST(HTTPRequestMSGTest, ReadFileAndPrint) {
    HTTPRequestMSG httpRequest;

    // Create a temporary file with an HTTP request
    std::ofstream outputFile("temp_request.txt");
    outputFile << "GET /index.html HTTP/1.1\r\n";
    outputFile << "Content-Type: text/html\r\n";
    outputFile << "Content-Length: 10\r\n";
    outputFile << "\r\n";
    outputFile << "Test body\n";
    outputFile.close();

    httpRequest.readFile("temp_request.txt");

    ASSERT_EQ("GET", httpRequest.getRequestMethod());
    ASSERT_EQ("/index.html", httpRequest.getUri());
    ASSERT_EQ("HTTP/1.1", httpRequest.getHttpVersion());

    const std::map<std::string, std::string>& headers = httpRequest.getHeaders();
    ASSERT_EQ(2, headers.size());
    ASSERT_EQ("text/html", headers.at("Content-Type"));
    ASSERT_EQ("10", headers.at("Content-Length"));

    ASSERT_EQ("Test body\n", httpRequest.getBody());

    httpRequest.print(); // This will print the request on the console

    // Clean up the temporary file
    std::remove("temp_request.txt");
}

TEST(HTTPRequestMSGTest, ParseSerializedHTTPRequest) {
    HTTPRequestMSG httpRequest;

    std::string serializedRequest = "POST /api/v1/data HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 29\r\n"
        "\r\n"
        "{\"id\": 1, \"value\": \"Hello\"}";

    httpRequest.parseSerializedHTTPRequest(serializedRequest);

    ASSERT_EQ("POST", httpRequest.getRequestMethod());
    ASSERT_EQ("/api/v1/data", httpRequest.getUri());
    ASSERT_EQ("HTTP/1.1", httpRequest.getHttpVersion());

    const std::map<std::string, std::string>& headers = httpRequest.getHeaders();
    ASSERT_EQ(2, headers.size());
    ASSERT_EQ("application/json", headers.at("Content-Type"));
    ASSERT_EQ("29", headers.at("Content-Length"));
}

TEST(HTTPRequestMSGTest, SetBody) {
    HTTPRequestMSG httpRequest;
    std::string newBody = "This is a new body";

    httpRequest.setBody(newBody);

    ASSERT_EQ(newBody, httpRequest.getBody());
}