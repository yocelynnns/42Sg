#ifndef WEBSERV_02_HTTP_RESPONSE_HPP
#define WEBSERV_02_HTTP_RESPONSE_HPP

#include "HttpUtils.hpp"
#include "05_session/Cookie.hpp"
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

/*
* Represents an HTTP response.
* Stores status code, reason phrase, headers, and body.
*/
class Response {
public:
	Response();

	// Setters
	void setStatus(int code);     // Set status code and reason
	void setHeader(const std::string& name, const std::string& value); // Add header
	void setBody(const std::string& content);               // Set response body
	void setContentType(const std::string& type);           // Convenience for Content-Type
	void setContentLength(size_t length);                   // Convenience for Content-Length
	void setKeepAlive(bool status);                                 // Add Connection: keep-alive
	
	// Getters
	int getStatus() const;
	const std::string& getReasonPhrase() const;
	const std::string& getHeader(const std::string& name) const;
	const std::map<std::string,std::string>& getAllHeaders() const;
	const std::string& getBody() const;
	HttpVersion getVersion() const;
	bool isHeadersSent() const;
	std::map<std::string, std::string>::const_iterator findHeader(const std::string& name) const;
	bool hasHeader(const std::string& header) const;

	void addDateHeader();

	std::string toString() const;							// Serialize to HTTP string

	void addCookie(const Cookie& cookie);
    const std::vector<Cookie>& getCookies() const;
    void clearCookies();
    


private:
	HttpVersion version;
	int status_code;
	std::string reason_phrase;
	std::map<std::string,std::string> headers;
	std::string body;
	bool headers_sent;
	std::vector<Cookie> cookies_;
};

#endif
