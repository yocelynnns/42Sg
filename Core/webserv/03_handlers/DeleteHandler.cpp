#include "DeleteHandler.hpp"
#include "ErrorHandler.hpp"
#include <sys/stat.h>
#include <cstdio>  // For remove() function

DeleteHandler::DeleteHandler() {
	// Constructor implementation
}

DeleteHandler::~DeleteHandler() {
	// Destructor implementation
}

Response DeleteHandler::handle(HandlerContext& ctx) {
	Response res;

	// Use the pre-resolved path from the request
	if (!ctx.req.hasResolvedPath()) {
		Logger::error("DeleteHandler - No resolved path available");
		return ErrorHandler(500).handle(ctx);
	}

	std::string fsPath = ctx.req.getResolvedPath();
	Logger::debug("DeleteHandler - Attempting to delete file: " + fsPath);

	// First check: does the file exist?
	struct stat st;
	if (stat(fsPath.c_str(), &st) != 0) {
		Logger::debug("DeleteHandler - File not found: " + fsPath);
		return ErrorHandler(404).handle(ctx);
	}

	// Second check: is it a regular file?
	if (!S_ISREG(st.st_mode)) {
		Logger::debug("DeleteHandler - Path is not a regular file: " + fsPath);
		return ErrorHandler(404).handle(ctx);
	}

	// Third check: safety validation
	if (!isDeletionSafe(fsPath, ctx)) {
		Logger::warn("DeleteHandler - Deletion blocked for safety: " + fsPath);
		return ErrorHandler(403).handle(ctx);  // Blocked = 403
	}

	// NEW: Check if file is writable (subject-compliant, no errno checking)
	if (access(fsPath.c_str(), W_OK) != 0) {
		Logger::debug("DeleteHandler - Permission denied: " + fsPath);
		return ErrorHandler(403).handle(ctx);
	}

	// Final operation: If this fails, it's truly unexpected (system error)
	if (remove(fsPath.c_str()) != 0) {
		Logger::error("DeleteHandler - Deletion failed: " + fsPath);
		return ErrorHandler(500).handle(ctx);  // ✅ System error = 500
	}

	Logger::info("DeleteHandler - Successfully deleted file: " + fsPath);
	res.setStatus(204); // No Content
	setCommonHeaders(res);
	return res;
}

// NEW: Safety check to prevent accidental deletion of important files
bool DeleteHandler::isDeletionSafe(const std::string& path, HandlerContext& ctx) {
	// Prevent deletion of files outside the server root
	std::string root = ctx.loc && !ctx.loc->root.empty() ? ctx.loc->root : ctx.config.default_root;
	if (!Handler::isPathSafe(path, root)) {
		return false;
	}

	// Prevent deletion of important system files (optional safety measure)
	if (path.find("/etc/") != std::string::npos ||
		path.find("/bin/") != std::string::npos ||
		path.find("/usr/") != std::string::npos) {
		return false;
	}

	// Prevent deletion of critical web server files
	if (path.find("index.") != std::string::npos || // index.html, index.php, etc.
		path.find("error_pages/") != std::string::npos) {
		return false;
	}

	return true;
}
