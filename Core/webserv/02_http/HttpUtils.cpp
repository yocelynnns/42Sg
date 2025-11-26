#include "HttpUtils.hpp"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cstdlib>

std::string HttpUtils::normalizeHeaderName(const std::string& name) {
		std::string result = name;
		for (size_t i = 0; i < result.size(); ++i)
			result[i] = std::tolower(result[i]);
		return result;
}

HttpMethod HttpUtils::stringToMethod(const std::string& str) {
	if (str == "GET") return GET;
	if (str == "POST") return POST;
	if (str == "DELETE") return DELETE;
	if (str == "HEAD") return HEAD;
	if (str == "PUT") return PUT;
	if (str == "OPTIONS") return OPTIONS;
	return UNKNOWN;
}

std::string HttpUtils::methodToString(HttpMethod method) {
	switch(method) {
		case GET: return "GET";
		case POST: return "POST";
		case DELETE: return "DELETE";
		case HEAD: return "HEAD";
		case PUT: return "PUT";
		case OPTIONS: return "OPTIONS";
		default: return "UNKNOWN";
	}
}

std::string HttpUtils::getStatusMessage(int status_code) {
	switch(status_code) {
		case 200: return "OK";
		case 201: return "Created";
		case 204: return "No Content";
		case 301: return "Moved Permanently";
		case 302: return "Found";
		case 304: return "Not Modified";
		case 400: return "Bad Request";
		case 403: return "Forbidden";
		case 404: return "Not Found";
		case 405: return "Method Not Allowed";
		case 413: return "Payload Too Large";
		case 500: return "Internal Server Error";
		case 501: return "Not Implemented";
		case 502: return "Bad Gateway";
		case 503: return "Service Unavailable";
		case 504: return "Gateway Timeout";
		default: return "Unknown";
	}
}

std::string HttpUtils::getMimeType(const std::string& ext) {
	if (ext == "html") return "text/html";
	if (ext == "css") return "text/css";
	if (ext == "js") return "application/javascript";
	if (ext == "json") return "application/json";
	if (ext == "png") return "image/png";
	if (ext == "jpg" || ext == "jpeg") return "image/jpeg";
	if (ext == "gif") return "image/gif";
	if (ext == "txt") return "text/plain";
	return "application/octet-stream";
}

std::string HttpUtils::urlDecode(const std::string& str) {
	std::string result;
	for (size_t i = 0; i < str.size(); ++i) {
		if (str[i] == '%' && i + 2 < str.size()) {
			int value = 0;
			std::istringstream is(str.substr(i+1,2));
			if (is >> std::hex >> value) {
				result += static_cast<char>(value);
				i += 2;
			} else {
				result += '%';
			}
		} else if (str[i] == '+') {
			result += ' ';
		} else {
			result += str[i];
		}
	}
	return result;
}

std::string HttpUtils::getCurrentDate() {
	char buf[128];
	std::time_t t = std::time(0);
	std::tm* gmt = std::gmtime(&t);
	std::strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S GMT", gmt);
	return std::string(buf);
}
