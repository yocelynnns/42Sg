#include "Request.hpp"

// Default constructor for HttpRequest
HttpRequest::HttpRequest()
	: method(UNKNOWN),
	version(HTTP_1_1),
	keep_alive(true),
	content_length(0),
	is_chunked(false),
	host(""),
	port(80), // default HTTP port
	client_ip(""),
	client_port(0),
	resolved_path("")  // NEW: Initialize resolved_path
{}

// Construct a Request from an HttpRequest
Request::Request(const HttpRequest& req)
	: raw(req) {}

// Accessors
HttpMethod Request::getMethod() const {
	return raw.method;
}

const std::string& Request::getPath() const {
	return raw.path;
}

const std::string& Request::getBody() const {
	return raw.body;
}

// Header helpers
//Note: getHeader("Host"): returns the full Host header value "localhost:8080"
std::string Request::getHeader(const std::string& name) const {
	std::string normalized = HttpUtils::normalizeHeaderName(name);
	for (std::map<std::string,std::string>::const_iterator it = raw.headers.begin();
		it != raw.headers.end(); ++it) {
		if (HttpUtils::normalizeHeaderName(it->first) == normalized)
			return it->second;
	}
	return "";
}

bool Request::hasHeader(const std::string& name) const {
	std::string normalized = HttpUtils::normalizeHeaderName(name);
	for (std::map<std::string,std::string>::const_iterator it = raw.headers.begin();
		it != raw.headers.end(); ++it) {
		if (HttpUtils::normalizeHeaderName(it->first) == normalized)
			return true;
	}
	return false;
}

const std::map<std::string,std::string>& Request::getAllHeaders() const {
	return raw.headers;
}

std::string Request::getCookie(const std::string& name) const {
	std::map<std::string,std::string>::const_iterator it = raw.cookies.find(name);
	return it != raw.cookies.end() ? it->second : "";
}

std::string Request::getUri() const {
	return raw.uri;
}

//getHost(): returns the hostname only (without port) "localhost"
std::string Request::getHost() const {
	return raw.host;
}

int Request::getPort() const {
	return raw.port;
}

const std::string& Request::getRemoteAddr() const {
	return raw.client_ip;
}

int Request::getRemotePort() const {
	return raw.client_port;
}

// NEW: Requested path accessors
void Request::setReqPath(const std::string& path) {
	raw.request_path = path;
}

const std::string& Request::getReqPath() const {
	return raw.request_path;
}

// NEW: Resolved path accessors
void Request::setResolvedPath(const std::string& path) {
	raw.resolved_path = path;
}

const std::string& Request::getResolvedPath() const {
	return raw.resolved_path;
}

bool Request::hasResolvedPath() const {
	return !raw.resolved_path.empty();
}

// Note:
// example if: Client machine (192.168.1.5:53422) → Server (127.0.0.1:8080)
// req.client_ip   == "192.168.1.5";
// req.client_port == 53422;
// req.host		   == 127.0.0.1;
// req.port        == 8080;   // server-side port (from Host or listen socket)

// Query string parser
std::map<std::string, std::string> Request::parseQueryString() const {
	std::map<std::string, std::string> params;
	size_t pos = raw.uri.find('?');
	if (pos == std::string::npos) return params;

	std::string query = raw.uri.substr(pos + 1);
	std::istringstream ss(query);
	std::string pair;
	while (std::getline(ss, pair, '&')) {
		size_t eq = pair.find('=');
		if (eq != std::string::npos)
			params[pair.substr(0, eq)] = pair.substr(eq + 1);
	}
	return params;
}
