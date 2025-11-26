#include "ErrorHandler.hpp"
#include "../02_http/HttpUtils.hpp"
#include <fstream>
#include <sstream>

static std::string loadErrorPage(const ServerConfig& config, int status) {
	// NEW: Use server-configured error pages from config
	std::map<int, std::string>::const_iterator it = config.error_pages.find(status);
	std::string filePath;
	
	if (it != config.error_pages.end()) {
		// Use the error page path configured in the server block
		filePath = it->second;
		Logger::debug("ErrorHandler - Using configured error page: " + filePath);
	} else {
		// Fallback to default error pages location
		filePath = "assets/error_pages/" + Utils::toString(status) + ".html";
		Logger::debug("ErrorHandler - Using default error page: " + filePath);
	}

	// Check if the path is to a valid file
	std::stringstream buffer;
	std::ifstream file(filePath.c_str());
	if (file.is_open()) {
		buffer << file.rdbuf();
		file.close();
		Logger::debug("ErrorHandler - Loaded error page: " + filePath);
	} else {
		// Final fallback: generate default error page
		Logger::debug("ErrorHandler - Error page not found, generating default: " + filePath);
		buffer << "<!DOCTYPE html>\n"
			<< "<html>\n"
			<< "<head>\n"
			<< "    <title>" << status << " " << HttpUtils::getStatusMessage(status) << "</title>\n"
			<< "    <style>\n"
			<< "        body { font-family: Arial, sans-serif; margin: 40px; text-align: center; }\n"
			<< "        h1 { color: #333; }\n"
			<< "        a { color: #0066cc; text-decoration: none; }\n"
			<< "        a:hover { text-decoration: underline; }\n"
			<< "    </style>\n"
			<< "</head>\n"
			<< "<body>\n"
			<< "    <h1>" << status << " - " << HttpUtils::getStatusMessage(status) << "</h1>\n"
			<< "    <p><a href=\"/\">Return to Home Page</a></p>\n"
			<< "</body>\n"
			<< "</html>";
	}

	return buffer.str();
}

// NEW: Static helper method
// Static method - takes reference like original
Response ErrorHandler::buildErrorResponse(int status, const ServerConfig& config) {
	Logger::info("ErrorHandler - Handling status code: " + Utils::toString(status));
	Response res;
	res.setStatus(status);
	
	std::string errorBody = loadErrorPage(config, status);  // Same as before
	res.setBody(errorBody);
	
	res.setHeader("Content-Type", "text/html");
	res.setHeader("Content-Length", Utils::toString(errorBody.size()));
	res.setHeader("Connection", "close");
	
	return res;
}

ErrorHandler::ErrorHandler() : _status(500) {
	Logger::info("ErrorHandler - Handling status code: 500");
}

ErrorHandler::ErrorHandler(int status) : _status(status) {
    // Logger::info("ErrorHandler - Handling status code: " + Utils::toString(status));
}

ErrorHandler::ErrorHandler(int status, const std::string& url) 
    : _status(status), _location_url(url) {
    Logger::info("ErrorHandler - Handling status code: " + Utils::toString(status) + " -> " + url);
}

ErrorHandler::~ErrorHandler() {
	// Destructor implementation
}

Response ErrorHandler::handle(HandlerContext& ctx) {
if (!_location_url.empty()) {
	// Location header set = redirect or return (identical behavior)
	return buildResponseWithLocation(_status, _location_url);
}

// No location = error page
return buildErrorResponse(_status, ctx.config);
}

Response ErrorHandler::buildResponseWithLocation(int code, const std::string& url) {
	Response res;
	res.setStatus(code);
	res.setHeader("Location", url);
	res.setHeader("Content-Length", "0");  // ← ADD THIS!
	res.setBody("");
	return res;
}
