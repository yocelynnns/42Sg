#include "Response.hpp"

Response::Response() :
	version(HTTP_1_1),
	status_code(200),
	headers_sent(false) {}

void Response::setStatus(int code) {
	static const int codesArray[] = { 200, 201, 204, 301, 302, 304, 400, 403, 404, 405, 413, 500, 501, 502, 503, 504 };
	static const std::vector<int> validCodes(codesArray, codesArray + sizeof(codesArray)/sizeof(codesArray[0]));

	if (std::find(validCodes.begin(), validCodes.end(), code) != validCodes.end())
		status_code = code;
	else
		status_code = 500;

	reason_phrase = HttpUtils::getStatusMessage(code);
}

void Response::setHeader(const std::string& name, const std::string& value) {
	headers[name] = value;
}

void Response::setBody(const std::string& content) {
	body = content;
}

void Response::setContentType(const std::string& type) {
	headers["Content-Type"] = type;
}

void Response::setContentLength(size_t length) {
	std::ostringstream ss;
	ss << length;
	headers["Content-Length"] = ss.str();
}

void Response::setKeepAlive(bool status) {
	if (status == true) 
		headers["Connection"] = "keep-alive";
	else
		headers["Connection"] = "closed";
}

void Response::addDateHeader() {
	headers["Date"] = HttpUtils::getCurrentDate();
}

int Response::getStatus() const {
	return status_code;
}

const std::string& Response::getReasonPhrase() const {
	return reason_phrase;
}

const std::string& Response::getHeader(const std::string& name) const {
	std::string normalized = HttpUtils::normalizeHeaderName(name);
	for (std::map<std::string,std::string>::const_iterator it = headers.begin(); it != headers.end(); ++it) {
		if (HttpUtils::normalizeHeaderName(it->first) == normalized)
			return it->second;
	}
	static const std::string empty = "";
	return empty;
}

const std::map<std::string,std::string>& Response::getAllHeaders() const {
	return headers;
}

const std::string& Response::getBody() const {
	return body;
}

HttpVersion Response::getVersion() const {
	return version;
}

bool Response::isHeadersSent() const {
	return headers_sent;
}

std::map<std::string, std::string>::const_iterator Response::findHeader(const std::string& name) const {
	std::string normalized = HttpUtils::normalizeHeaderName(name);

	for (std::map<std::string, std::string>::const_iterator it = headers.begin(); it != headers.end(); ++it) {
		if (HttpUtils::normalizeHeaderName(it->first) == normalized)
			return (it);
	}
	return (headers.end());
}

bool Response::hasHeader(const std::string& header) const {
	return findHeader(header) != headers.end();    
}

void Response::addCookie(const Cookie& cookie) {
	cookies_.push_back(cookie);
}

const std::vector<Cookie>& Response::getCookies() const {
	return cookies_;
}

void Response::clearCookies() {
	cookies_.clear();
}

// Serialize entire response to a string (ready to send over TCP)
std::string Response::toString() const {
	std::ostringstream oss;
	oss << "HTTP/1.1 " << status_code << " "
		<< (reason_phrase.empty() ? HttpUtils::getStatusMessage(status_code) : reason_phrase)
		<< "\r\n";

	// Add automatic headers if not already set
	if (headers.find("Date") == headers.end()) 
		oss << "Date: " << HttpUtils::getCurrentDate() << "\r\n";
	
	if (headers.find("Content-Length") == headers.end() && !body.empty())
		oss << "Content-Length: " << body.size() << "\r\n";

	// Add regular headers
	for (std::map<std::string,std::string>::const_iterator it = headers.begin();
		it != headers.end(); ++it) {
		oss << it->first << ": " << it->second << "\r\n";
	}

	// Add cookies as Set-Cookie headers
	for (std::vector<Cookie>::const_iterator it = cookies_.begin();
		it != cookies_.end(); ++it) {
		oss << "Set-Cookie: " << it->toString() << "\r\n";
	}

	oss << "\r\n" << body;
	return oss.str();
}
