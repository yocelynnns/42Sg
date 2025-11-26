 #include <sys/stat.h>
 #include "StaticFileHandler.hpp"
#include "ErrorHandler.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

StaticFileHandler::StaticFileHandler() {
	// Constructor implementation
}

StaticFileHandler::~StaticFileHandler() {
	// Destructor implementation
}

Response StaticFileHandler::handle(HandlerContext& ctx) {
	Response res;

	// NEW: Use the pre-resolved path from the request
	if (!ctx.req.hasResolvedPath()) {
		Logger::error("StaticFileHandler - No resolved path available");
		return ErrorHandler(500).handle(ctx);
	}

	std::string filePath = ctx.req.getResolvedPath();
	Logger::debug("StaticFileHandler - Using resolved path: " + filePath);

	std::string sMethod = HttpUtils::methodToString(ctx.req.getMethod());
	if (!serveFile(filePath, res, sMethod)) {
		Logger::debug("StaticFileHandler - File not served successfully: " + filePath);
		return ErrorHandler(res.getStatus()).handle(ctx);
	}
	
	Logger::debug("StaticFileHandler - Successfully served file: " + filePath);
	return res;
}

bool StaticFileHandler::serveFile(const std::string& filePath, Response& res, std::string method) {
	// Debug: log the file path we're trying to serve
	Logger::debug("StaticFileHandler - Attempting to serve file: " + filePath);
	
	// std::ifstream file(filePath.c_str(), std::ios::binary);
	// if (!file.is_open()) {
    //     int err = errno;
	// 	Logger::debug("StaticFileHandler - Failed to open file: " + filePath + " (" + std::string(std::strerror(err)) + ")");
    //     if (err == ENOENT)
    //         res.setStatus(404);
    //     else if (err == EACCES || EISDIR)
    //         res.setStatus(403);
    //     else
    //         res.setStatus(500);
	// 	return false;
	// }

	// NEW: Use pre-checks instead of errno
	struct stat st;

	// First check: does the file exist and is it a regular file?
	if (stat(filePath.c_str(), &st) != 0 || !S_ISREG(st.st_mode)) {
		Logger::debug("StaticFileHandler - File not found or not a file: " + filePath);
		res.setStatus(404);
		return false;
	}

	// Second check: can we read it? (optional, but adds safety)
	std::ifstream file(filePath.c_str(), std::ios::binary);
	if (!file.is_open()) {
		Logger::error("StaticFileHandler - Cannot open file (system error): " + filePath);
		res.setStatus(500);
		return false;
	}

	// If we reach here, file is valid and openable
	Logger::debug("StaticFileHandler - Successfully opened file: " + filePath);

	// Determine file size
	file.seekg(0, std::ios::end);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	// Debug: log the file size
	Logger::debug("StaticFileHandler - File size from tellg(): " + Utils::toString(size));
	
	// Check if file is empty
	if (size == 0) {
		Logger::warn("StaticFileHandler - File is empty: " + filePath);
	}

	// Set status code and message 
	res.setStatus(200);

	// Set common headers
	setCommonHeaders(res);

	// Set Content-Length header
	res.setHeader("Content-Length", Utils::toString(size));

	// Set Content-Type header
	std::string::size_type pos = filePath.find_last_of('.');
	std::string ext = (pos != std::string::npos) ? filePath.substr(pos + 1) : "";
	std::string mimeType = HttpUtils::getMimeType(ext);
	Logger::debug("StaticFileHandler - File extension: '" + ext + "', MIME type: " + mimeType);
	res.setHeader("Content-Type", mimeType);

	// Read body if method is GET
	if (method == "GET") {
		Logger::debug("StaticFileHandler - Reading file content for GET");
		
		// Reset to beginning after getting size
		file.clear();  // Clear any error flags
		file.seekg(0, std::ios::beg);
		
		// Read the file content properly for binary data
		std::vector<char> buffer(size);
		if (!file.read(&buffer[0], size)) {
			Logger::warn("StaticFileHandler - Failed to read entire file: " + filePath);
			Logger::warn("StaticFileHandler - Bytes read: " + Utils::toString(file.gcount()) + 
						", expected: " + Utils::toString(size));
			return false;
		}
		
		std::string body(buffer.begin(), buffer.end());
		
		// Verify we read the expected amount
		if (body.size() != static_cast<size_t>(size)) {
			Logger::warn("StaticFileHandler - File size mismatch: expected " + Utils::toString(size) + 
						", got " + Utils::toString(body.size()));
		} else {
			Logger::debug("StaticFileHandler - Successfully read file, body size: " + Utils::toString(body.size()));
		}
		
		res.setBody(body);
	} else {
		Logger::debug("StaticFileHandler - Skipping body read for method: " + method);
	}

	return true;
}
