#include "RequestParser.hpp"
#include <cstdlib>
#include <sstream>

// The 8192 bytes (8 KB) is a conventional 
// limit used in many HTTP servers for request 
// lines and headers
#define MAX_HEADER_SIZE 8192
#define MAX_LINE_SIZE 8192

// Constructor
RequestParser::RequestParser() 
	: state(PARSING_REQUEST_LINE), content_length(0), bytes_read(0), bytes_consumed_(0) {}  // new: Initialize bytes_consumed_

// Incremental parse function
ParseState RequestParser::parse(const std::string& data, HttpRequest& request) {
	buffer += data;
	
	while (true) {
		if (state == PARSING_REQUEST_LINE) {
			size_t pos = buffer.find("\r\n");
			if (pos == std::string::npos) return state;
			std::string line = buffer.substr(0, pos);
			
			bytes_consumed_ += (pos + 2);  // new: Track consumption
			buffer.erase(0, pos + 2);

			if (line.size() > MAX_LINE_SIZE) { state = ERROR; error_message = "Request line too long"; return state; }
			if (!parseRequestLine(line, request)) { state = ERROR; return state; }
			if (request.version == HTTP_UNKNOWN_VERSION) { state = UNKNOWN_VERSION; return state; }
			state = PARSING_HEADERS;
		}
		else if (state == PARSING_HEADERS) {
			size_t pos = buffer.find("\r\n");
			if (pos == std::string::npos) return state;
			std::string line = buffer.substr(0, pos);
			
			bytes_consumed_ += (pos + 2);  // new: Track consumption
			buffer.erase(0, pos + 2);

			if (line.empty()) {
				// End of headers
				std::map<std::string,std::string>::iterator host_it = request.headers.find("Host");
				if (host_it != request.headers.end()) {
					std::string host_header = host_it->second;
					size_t colon = host_header.find(':');
					if (colon != std::string::npos) {
						request.host = host_header.substr(0, colon);
						request.port = std::atoi(host_header.substr(colon + 1).c_str());
					} else {
						request.host = host_header;
						request.port = 80; // default HTTP port
					}
				}
				std::map<std::string,std::string>::iterator it = request.headers.find("Transfer-Encoding");
				if (it != request.headers.end() && it->second.find("chunked") != std::string::npos) {
					request.is_chunked = true;
					state = PARSING_CHUNKED_BODY;
					continue;
				}
				it = request.headers.find("Content-Length");
				if (it != request.headers.end()) {
					content_length = std::atoi(it->second.c_str());
					request.content_length = content_length;
					state = PARSING_BODY;
				} else {
					content_length = 0;
					state = COMPLETE;
					parseCookies(request);
				}
				request.keep_alive = shouldKeepAlive(request);
				bytes_read = 0;
				continue;
			}
			if (!parseHeader(line, request)) { state = ERROR; return state; }
		}
		else if (state == PARSING_BODY) {
			size_t to_read = content_length - bytes_read;
			
			Logger::debug("PARSING_BODY: buffer=" + Utils::toString(buffer.size()) + 
						" to_read=" + Utils::toString(to_read) + 
						" bytes_read=" + Utils::toString(bytes_read) + 
						"/" + Utils::toString(content_length));
			
			if (buffer.size() < to_read) {
				// Partial body
				bytes_consumed_ += buffer.size();
				request.body += buffer;
				bytes_read += buffer.size();
				buffer.clear();
				return state;
			} else {
				// Complete body
				bytes_consumed_ += to_read;
				request.body += buffer.substr(0, to_read);
				buffer.erase(0, to_read);
				
				Logger::debug("Body complete! Total size: " + Utils::toString(request.body.size()));
				
				parseCookies(request);
				state = COMPLETE;
				return state;
			}
		}
		else if (state == PARSING_CHUNKED_BODY) {
			if (!parseChunkedBody(request)) return state;
			parseCookies(request);
			state = COMPLETE;
			return state;
		}
		else {
			return state;
		}
	}
}

// Get current parser state
ParseState RequestParser::getState() const {
	return state;
}

std::string RequestParser::getError() const {
	return error_message;
}

void RequestParser::resetBytesConsumed() { 
	bytes_consumed_ = 0;
}


// Reset parser
void RequestParser::reset() {
	state = PARSING_REQUEST_LINE;
	buffer.clear();
	content_length = 0;
	bytes_read = 0;
	bytes_consumed_ = 0;  // new: Reset consumption counter
	error_message.clear();
}

size_t RequestParser::getBytesConsumed() const { 
	return bytes_consumed_; 
}

// Parse "METHOD /path HTTP/1.1"
bool RequestParser::parseRequestLine(const std::string& line, HttpRequest& request) {
	std::istringstream ss(line);
	std::string method_str, uri, version_str;
	
	if (!(ss >> method_str >> uri >> version_str)) {
		error_message = "Invalid request line";
		return false;
	}
	request.method = HttpUtils::stringToMethod(method_str);
	request.uri = uri;

	size_t qpos = uri.find('?');
	if (qpos != std::string::npos)
		request.path = uri.substr(0, qpos);
	else
		request.path = uri;

	if (version_str == "HTTP/1.1")
		request.version = HTTP_1_1;
	else if (version_str == "HTTP/1.0")
		request.version = HTTP_1_0;
	else
		request.version = HTTP_UNKNOWN_VERSION;
	return true;
}

// Parse single header line
bool RequestParser::parseHeader(const std::string& line, HttpRequest& request) {
	size_t pos = line.find(":");
	if (pos == std::string::npos) {
		error_message = "Invalid header";
		return false;
	}
	std::string key = line.substr(0,pos);
	std::string value = line.substr(pos+1);
	// remove leading space
	if (!value.empty() && value[0] == ' ')
		value.erase(0,1);
	if (key.size() > 1024 || value.size() > 8192) {
		error_message = "Header too large";
		return false;
	}
	request.headers[key] = value;
	return true;
}

// Parses Cookie header into key-value map
void RequestParser::parseCookies(HttpRequest& request) {
	std::map<std::string,std::string>::iterator it = request.headers.find("Cookie");
	if (it != request.headers.end()) {
		std::istringstream ss(it->second);
		std::string pair;
		while (std::getline(ss, pair, ';')) {
			size_t eq = pair.find('=');
			if (eq != std::string::npos) {
				std::string key = pair.substr(0,eq);
				std::string val = pair.substr(eq+1);
				// remove leading space
				if (!key.empty() && key[0] == ' ')
					key.erase(0,1);
				request.cookies[key] = val;
			}
		}
	}
}

bool RequestParser::parseChunkedBody(HttpRequest& request) {
	while (true) {
		size_t pos = buffer.find("\r\n");
		if (pos == std::string::npos)
			return false;
		
		std::string line = buffer.substr(0, pos);
		
		bytes_consumed_ += (pos + 2);  // new: Track chunk size line consumption
		buffer.erase(0, pos + 2);

		std::istringstream ss(line);
		size_t chunk_size = 0;
		ss >> std::hex >> chunk_size;
		if (chunk_size == 0) {
			if (buffer.size() >= 2) {
				bytes_consumed_ += 2;  // new: Track final \r\n consumption
				buffer.erase(0, 2); // remove trailing \r\n
			}
			return true;
		}
		if (buffer.size() < chunk_size + 2)
			return false; // wait for more data
		
		bytes_consumed_ += (chunk_size + 2);  // new: Track chunk data consumption
		request.body += buffer.substr(0, chunk_size);
		buffer.erase(0, chunk_size + 2); // remove chunk + \r\n
	}
}

bool RequestParser::shouldKeepAlive(const HttpRequest& req) {
	std::map<std::string,std::string>::const_iterator it = req.headers.find("Connection");
	std::string conn;

	if (it != req.headers.end()) {
		conn = it->second;
	} else {
		conn = "";
	}
	if (req.version == HTTP_1_0)
		return conn.find("keep-alive") != std::string::npos;
	else
		return conn.find("close") == std::string::npos;
}
