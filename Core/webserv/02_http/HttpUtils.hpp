#ifndef WEBSERV_02_HTTP_HTTPUTILS_HPP
#define WEBSERV_02_HTTP_HTTPUTILS_HPP

#include <string>
#include <map>

enum HttpMethod { GET, POST, DELETE, HEAD, PUT, OPTIONS, UNKNOWN };
enum HttpVersion { HTTP_1_0, HTTP_1_1, HTTP_UNKNOWN_VERSION };

class HttpUtils {
public:
	// Convert string to HttpMethod
	static HttpMethod stringToMethod(const std::string& str);
	static std::string getCurrentDate();

	static std::string normalizeHeaderName(const std::string& name);

	// Convert HttpMethod to string
	static std::string methodToString(HttpMethod method);

	// USED FOR HANDLER 
	// Return reason phrase for a status code
	static std::string getStatusMessage(int status_code);

	// Return MIME type for file extension
	static std::string getMimeType(const std::string& extension);
	static std::string urlDecode(const std::string& str);

	// Status codes and messages constant
	static const std::map<int, std::string> kStatusMessages;

	// Retrieve reason/message based on status code
	static std::string getReasonPhrase(int status);
};

#endif
