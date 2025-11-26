#ifndef WEBSERV_02_HTTP_REQUESTPARSER_HPP
#define WEBSERV_02_HTTP_REQUESTPARSER_HPP

#include "Request.hpp"
#include <string>

// Parsing states for incremental request parsing
enum ParseState {
	PARSING_REQUEST_LINE,
	PARSING_HEADERS,
	PARSING_BODY,
	PARSING_CHUNKED_BODY,
	COMPLETE,
	ERROR,
	UNKNOWN_VERSION
};

/*
* Incremental HTTP request parser
* Handles partial reads, stores buffer internally, and tracks state.
*/
class RequestParser {
	ParseState state;           // Current parser state
	size_t content_length;      // Expected body size
	size_t bytes_read;          // Bytes read for body
	std::string error_message;  // Error details if parse fails
	std::string buffer;         // Internal buffer for incoming data
	size_t bytes_consumed_;     // New: Total bytes consumed from buffer

public:
	RequestParser();

	// Feed new data to parser. Returns current ParseState.
	ParseState parse(const std::string& data, HttpRequest& request);

	ParseState getState() const;
	std::string getError() const;
	void reset(); // Reset parser to start parsing new request
	size_t getBytesConsumed() const;
	void resetBytesConsumed();

private:
	bool parseRequestLine(const std::string& line, HttpRequest& request); // Parse "GET / HTTP/1.1"
	bool parseHeader(const std::string& line, HttpRequest& request);      // Parse "Host: localhost"
	void parseCookies(HttpRequest& request);                              // Parse "Cookie" header into key-value
	bool parseChunkedBody(HttpRequest& request);
	static bool shouldKeepAlive(const HttpRequest& req);                         // Helper for keep-alive detection
};

#endif
