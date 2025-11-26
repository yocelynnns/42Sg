#ifndef WEBSERV_02_HTTP_REQUEST_HPP
#define WEBSERV_02_HTTP_REQUEST_HPP

#include "HttpUtils.hpp"
#include "06_utils/Logger.hpp"
#include <string>
#include <map>
#include <sstream>

/*
* Low-level representation of an HTTP request.
* Filled directly by RequestParser.
*/
struct HttpRequest {
	HttpMethod method;                          // GET, POST, etc.
	std::string uri;                            // Full request URI (including query string)
	HttpVersion version;                        // HTTP/1.0 or HTTP/1.1
	std::map<std::string,std::string> headers;  // All headers from the request
	std::string body;                           // Request body (for POST/PUT)

	// Parsed helper fields
	std::string path;                           // URI path without query string
	bool keep_alive;                            // Connection persistence
	size_t content_length;                      // Length of the request body
	bool is_chunked;                            // Transfer-Encoding: chunked

	// Parsed cookies
	std::map<std::string,std::string> cookies;

	std::string host;      // Hostname from "Host:" header
	int port;              // Port number from Host header or connection
	std::string client_ip; // IP address of the client  
	int client_port;       // Port of the client

	// NEW: Server-resolved filesystem path
	std::string resolved_path;  // Absolute filesystem path for the request
	std::string request_path;   // Original request path with / in front
	HttpRequest(); // default constructor
};

/*
* High-level wrapper around HttpRequest for use in handlers.
* Provides helper functions for easier access to headers, cookies, and query parameters.
*/
class Request {
private:
	HttpRequest raw; // reference to the low-level parsed request

public:
	explicit Request(const HttpRequest& req);

	HttpMethod getMethod() const;
	const std::string& getPath() const;
	const std::string& getBody() const;
	std::string getCookie(const std::string& name) const;

	// Header accessors normalize on lookup
	std::string getHeader(const std::string& name) const;
	bool hasHeader(const std::string& name) const;
	const std::map<std::string,std::string>& getAllHeaders() const;

	std::string getUri() const;
	std::string getHost() const;
	int getPort() const;
	const std::string& getRemoteAddr() const;
	int getRemotePort() const;
	
	void setReqPath(const std::string& path);
	const std::string& getReqPath() const;
	// NEW: Resolved path accessors
	void setResolvedPath(const std::string& path);
	const std::string& getResolvedPath() const;
	bool hasResolvedPath() const;
	
	std::map<std::string, std::string> parseQueryString() const;
};

#endif // REQUEST_HPP
