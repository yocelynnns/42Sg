#include "Handler.hpp"
#include "ErrorHandler.hpp"
#include "StaticFileHandler.hpp"
#include "AutoIndexHandler.hpp"
#include "UploadHandler.hpp"
#include "DeleteHandler.hpp"
#include "04_cgi/CGIHandler.hpp"
#include "05_session/SessionDemoHandler.hpp"
#include "01_config/Config.hpp"
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <sstream>
#include <string>
#include <sys/stat.h>

static bool fileExists(const std::string& path) {
	struct stat buffer;
	return (stat(path.c_str(), &buffer) == 0);
}

static bool isFile(const std::string& path) {
	struct stat buffer;
	return (stat(path.c_str(), &buffer) == 0 && S_ISREG(buffer.st_mode));
}

static bool isDirectory(const std::string& path) {
	struct stat buffer;
	return (stat(path.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode));
}

Handler::~Handler() {
	// Destructor implementation
}

Handler* Handler::createHandler(HandlerContext& ctx) {
	Logger::debug("Handler::createHandler - Starting handler selection");
	Logger::debug("Handler::createHandler - Request: " + 
			HttpUtils::methodToString(ctx.req.getMethod()) + " " + 
			ctx.req.getUri());
	Logger::debug("Handler::createHandler - Host: " + ctx.req.getHost() + " Port: " + Utils::toString(ctx.req.getPort()));

	// 1. SESSION DEMO ROUTE (existing - keep as is)
	if (ctx.req.getUri().find("/session") == 0) {
		Logger::debug("Handler::createHandler - SessionDemoHandler selected");
		return new SessionDemoHandler();
	}

	// 2. FALLBACK if location is not resolved
	const Location* loc = ctx.loc;
	if (loc == NULL) {
		Logger::debug("Handler::createHandler - No location found, returning 404");
		return new ErrorHandler(404);
	}

	// ========== NEW: ACCESS CONTROL BLOCK ==========
	// 3. CHECK deny_all FIRST
	if (loc->deny_all) {
		Logger::debug("Handler::createHandler - deny_all is set, returning 403");
		return new ErrorHandler(403);
	}

	// 4. CHECK denied_ips
	std::string client_ip = ctx.req.getRemoteAddr(); 
	for (size_t i = 0; i < loc->denied_ips.size(); i++) {
		if (client_ip == loc->denied_ips[i]) {
		Logger::debug("Handler::createHandler - Access denied for IP: " + client_ip);
		return new ErrorHandler(403);
		}
	}

	// 5. CHECK redirect_url
	if (!loc->redirect_url.empty()) {
		Logger::debug("Handler::createHandler - Redirect to: " + loc->redirect_url);
		return new ErrorHandler(301, loc->redirect_url);  // ← Uses new 2-param constructor
	}

	// 6. CHECK return directive
	if (loc->return_code != 0) {
		// Logger::info("Handler::createHandler - Return code: " + Utils::toString(loc->return_code));
		return new ErrorHandler(loc->return_code, loc->return_url);  // ← Uses new 2-param constructor
	}
	// ========== END NEW BLOCK ==========

	Logger::debug("Handler::createHandler - Location root: " + loc->root);
	Logger::debug("Handler::createHandler - Location autoindex: " + Utils::toString(loc->autoindex));
	Logger::debug("Handler::createHandler - Location upload_enable: " + Utils::toString(loc->upload_enable));
	
	// 7. METHOD CHECK (existing - keep unchanged)
	HttpMethod method = ctx.req.getMethod();
	std::string sMethod = HttpUtils::methodToString(method);
	Logger::debug("Handler::createHandler - Method: " + sMethod);

	if (method == UNKNOWN) {
		Logger::debug("Handler::createHandler - Method not implemented, returning 501");
		return new ErrorHandler(501);
	}

	// Now check if the method is allowed for this location
	if (!isMethodAllowed(method, loc->allowed_methods)) {
		Logger::debug("Handler::createHandler - Method not allowed, returning 405");
		return new ErrorHandler(405);
	}

	if (method == POST || method == PUT) {
		if (ctx.req.hasHeader("Content-Length")) {
			std::string clStr = ctx.req.getHeader("Content-Length");
			std::stringstream ss(clStr);
			size_t contentLength;
			ss >> contentLength;
			
			// Get client_max_body_size from location config
			size_t maxBodySize = ctx.loc->client_max_body_size;
			
			Logger::debug("Handler::createHandler - Content-Length: " + 
						Utils::toString(contentLength) + 
						", Max allowed: " + Utils::toString(maxBodySize));
			
			if (contentLength > maxBodySize) {
				Logger::debug("Handler::createHandler - Payload too large, returning 413");
				return new ErrorHandler(413);
			}
		}
	}

	if (sMethod == "POST" && loc->upload_enable) {
		Logger::debug("Handler::createHandler - Creating UploadHandler (early check)");
		Logger::debug("Handler::createHandler - Upload dir: " + loc->upload_dir);
		return new UploadHandler(loc->upload_dir);
	}

	// ========== RESOLVE PATH ONCE AND STORE IN REQUEST ==========
	std::string fsPath;
	try {
		fsPath = Handler::resolvePath(ctx.req.getPath(), ctx);
		ctx.req.setResolvedPath(fsPath);
		Logger::debug("Handler::createHandler - Resolved and stored path: " + fsPath);
	} catch (const std::exception& e) {
		std::string msg = e.what();
		Logger::debug("Handler::createHandler - Path resolution failed: " + msg);
		if (msg == "Forbidden")
			return new ErrorHandler(403);
		else if (msg == "No index file") {
			if (ctx.loc->autoindex)
				return new AutoIndexHandler();
			else
				return new ErrorHandler(403);
		} else
			return new ErrorHandler(404);
	}

	// ========== CHECK FOR CGI USING RESOLVED PATH ==========
	size_t dot_pos = fsPath.find_last_of('.');
	if (dot_pos != std::string::npos) {
		std::string ext = fsPath.substr(dot_pos);
		for (size_t i = 0; i < loc->cgi_extensions.size(); ++i) {
			if (loc->cgi_extensions[i] == ext) {
				Logger::debug("Handler::createHandler - CGI extension detected: " + ext);
				if (fileExists(fsPath) && isFile(fsPath))
					return new CGIHandler(*ctx.cgi);
				else
					return new ErrorHandler(404);
			}
		}
	}

	if (sMethod == "POST") {
		if (loc->upload_enable) {
			Logger::debug("Handler::createHandler - Creating UploadHandler");
			Logger::debug("Handler::createHandler - Upload dir: " + loc->upload_dir);
			return new UploadHandler(loc->upload_dir);
		}
		Logger::debug("Handler::createHandler - Upload not enabled, returning 403");
		return new ErrorHandler(403);
	}

	// Check if it's a directory
	if (isDirectory(fsPath)) {
		Logger::debug("Handler::createHandler - Path is a directory");
		if (loc->autoindex)
			return new AutoIndexHandler();
		else if (fileExists(fsPath + "/index.html"))
			return new StaticFileHandler();
		else
			return new ErrorHandler(403);
	}

	// Check if it's a file
	if (isFile(fsPath)) {
		Logger::debug("Handler::createHandler - Path is a file: " + fsPath);
		if (sMethod == "GET" || sMethod == "HEAD")
			return new StaticFileHandler();
		if (sMethod == "DELETE")
			return new DeleteHandler();
	}

	Logger::debug("Handler::createHandler - No matching handler, returning 404");
	return new ErrorHandler(404);
}

bool Handler::isMethodAllowed(HttpMethod method, const std::vector<std::string>& allowed) {
	std::string s = HttpUtils::methodToString(method);
	
	std::vector<std::string>::const_iterator it = std::find(allowed.begin(), allowed.end(), s); 
	if (it == allowed.end())
		return (false);
	return (true);
}

std::string Handler::resolvePath(const std::string& requestPath, HandlerContext& ctx) {
	const std::string& root = ctx.loc->root.empty() ? ctx.config.default_root : ctx.loc->root;
	const std::string& location_path = ctx.loc->path;
	
	// Remove query string
	std::string path = requestPath;
	std::string::size_type qPos = path.find('?');
	if (qPos != std::string::npos)
		path = path.substr(0, qPos);

	// Decode percent-encoding
	std::string decoded = HttpUtils::urlDecode(path);

	Logger::debug("Handler::resolvePath - Request path: " + requestPath);
	Logger::debug("Handler::resolvePath - Decoded path: " + decoded);
	Logger::debug("Handler::resolvePath - Location path: " + location_path);
	Logger::debug("Handler::resolvePath - Root: " + root);
	Logger::debug("Handler::resolvePath - CGI enabled: " + Utils::toString(ctx.loc->cgi_enable));

	// Remove location prefix from the path
	std::string path_without_location = decoded;
	
	// Only remove location prefix for CGI-enabled locations
	if (ctx.loc->cgi_enable && !location_path.empty() && location_path != "/") {
		Logger::debug("Handler::resolvePath - Before stripping: " + path_without_location);
		
		// Check if the path starts with the location path
		if (path_without_location.find(location_path) == 0) {
			path_without_location = path_without_location.substr(location_path.length());
			
			// Remove any leading slash that might remain
			if (!path_without_location.empty() && path_without_location[0] == '/') {
				path_without_location = path_without_location.substr(1);
			}
			
			Logger::debug("Handler::resolvePath - After stripping: " + path_without_location);
		}
	}

	// Combine with root to get full filesystem path
	std::string fullPath = root;
	if (!fullPath.empty() && fullPath[fullPath.size() - 1] != '/') {
		fullPath += "/";
	}
	
	// Add the remaining path (remove leading slash if it exists to avoid double slashes)
	if (!path_without_location.empty()) {
		// Skip leading slash if present to avoid double slashes
		if (path_without_location[0] == '/') {
			fullPath += path_without_location.substr(1);
		} else {
			fullPath += path_without_location;
		}
	}

	// Convert to absolute path if relative
	if (fullPath[0] != '/') {
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) != NULL) {
			fullPath = std::string(cwd) + "/" + fullPath;
		}
	}

	Logger::debug("Handler::resolvePath - Full path: " + fullPath);

	ctx.req.setReqPath(requestPath);
	
	struct stat st;
	if (stat(fullPath.c_str(), &st) != 0) {
		Logger::debug("Handler::resolvePath - Path not found: " + fullPath);
		throw std::runtime_error("Not Found");
	}

	// Safety check - ensure path is within root
	if (!Handler::isPathSafe(fullPath, root)) {
		Logger::debug("Handler::resolvePath - Path safety check failed: " + fullPath);
		throw std::runtime_error("Forbidden");
	}

	// If it's a directory, handle index files
	if (S_ISDIR(st.st_mode)) {
		Logger::debug("Handler::resolvePath - Path is directory");
		
		// Store the directory path FIRST, before trying index files
		std::string directoryPath = fullPath;
		if (directoryPath[directoryPath.size() - 1] != '/') {
			directoryPath += "/";
		}
		ctx.req.setResolvedPath(directoryPath);
		
		// Add trailing slash if missing
		if (fullPath[fullPath.size() - 1] != '/') {
			fullPath += "/";
		}
		
		// Try index files from location config
		const std::vector<std::string>& indexFiles = ctx.loc->index_files;
		bool foundIndex = false;
		
		for (std::vector<std::string>::const_iterator it = indexFiles.begin(); 
			it != indexFiles.end(); ++it) {
			std::string indexPath = fullPath + *it;
			Logger::debug("Handler::resolvePath - Trying index: " + indexPath);
			
			if (fileExists(indexPath) && isFile(indexPath)) {
				fullPath = indexPath;
				foundIndex = true;
				Logger::debug("Handler::resolvePath - Found index: " + indexPath);
				break;
			}
		}
		
		if (!foundIndex) {
			Logger::debug("Handler::resolvePath - No index file found");
			throw std::runtime_error("No index file");
		}
	}
	// If it's a regular file, just return it
	else if (S_ISREG(st.st_mode)) {
		Logger::debug("Handler::resolvePath - Path is file: " + fullPath);
		return fullPath;
	}
	// Neither file nor directory
	else {
		Logger::debug("Handler::resolvePath - Not file or directory: " + fullPath);
		throw std::runtime_error("Not Found");
	}

	return fullPath;
}

bool Handler::isPathSafe(const std::string& path, const std::string& root) {
	Logger::debug("Handler::isPathSafe - Path: " + path);
	Logger::debug("Handler::isPathSafe - Root: " + root);

	// Convert relative root to absolute path for comparison
	std::string abs_root = root;
	if (root[0] != '/') {
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) != NULL) {
			abs_root = std::string(cwd) + "/" + root;
			Logger::debug("Handler::isPathSafe - Absolute root: " + abs_root);
		}
	}

	// Normalize both paths (remove trailing slashes)
	std::string normalized_path = path;
	std::string normalized_root = abs_root;
	
	// Remove trailing slashes for consistent comparison
	if (!normalized_path.empty() && normalized_path[normalized_path.size() - 1] == '/') {
		normalized_path = normalized_path.substr(0, normalized_path.size() - 1);
	}
	if (!normalized_root.empty() && normalized_root[normalized_root.size() - 1] == '/') {
		normalized_root = normalized_root.substr(0, normalized_root.size() - 1);
	}

	Logger::debug("Handler::isPathSafe - Normalized path: " + normalized_path);
	Logger::debug("Handler::isPathSafe - Normalized root: " + normalized_root);

	// Check if path starts with root
	if (normalized_path.size() < normalized_root.size()) {
		Logger::debug("Handler::isPathSafe - Path shorter than root");
		return false;
	}

	if (normalized_path.compare(0, normalized_root.size(), normalized_root) != 0) {
		Logger::debug("Handler::isPathSafe - Path does not start with root");
		return false;
	}

	// Additional safety: ensure the next character is a slash (or we're at the end)
	if (normalized_path.size() > normalized_root.size() && normalized_path[normalized_root.size()] != '/') {
		Logger::debug("Handler::isPathSafe - Path traversal detected");
		return false;
	}

	Logger::debug("Handler::isPathSafe - Path is safe");
	return true;
}

void Handler::setCommonHeaders(Response& response) {
	response.addDateHeader();
	if (!response.hasHeader("Server"))
			response.setHeader("Server", "WebServ/1.0");
	response.setHeader("Connection", "keep-alive");
}

std::string Handler::normalizePath(const std::string& path) {
	std::vector<std::string> stack;
	std::istringstream iss(path);
	std::string token;

	while (std::getline(iss, token, '/')) {
		if (token.empty() || token == ".")
			continue;
		else if (token == "..") {
			if (!stack.empty())
				stack.pop_back();
			else
				throw std::runtime_error("Forbidden");
		}
		else
			stack.push_back(token);
	}

	std::string canonical;
	for (size_t i = 0; i < stack.size(); ++i) {
		canonical += stack[i];
		if (i + 1 < stack.size())
			canonical += "/";
	}
	return (canonical);
}

Session* Handler::getSessionFromRequest(const Request& req) {
	// Extract session ID from cookies
	std::string sessionCookie = req.getCookie("session_id");
	if (!sessionCookie.empty()) {
		Session* session = SessionManager::getInstance().getSession(sessionCookie);
		if (session && !session->isExpired()) {
			session->updateAccessTime();
			return session;
		}
	}
	return NULL;
}

Cookie Handler::createSessionCookie(const Session& session) {
	Cookie cookie("session_id", session.getId());
	cookie.setPath("/");
	cookie.setHttpOnly(true);
	cookie.setMaxAge(session.getExpiration() - std::time(NULL));
	return cookie;
}

void Handler::destroySession(const Request& req) {
	std::string sessionId = req.getCookie("session_id");
	if (!sessionId.empty()) {
		SessionManager::getInstance().destroySession(sessionId);
	}
}

Session* Handler::getOrCreateSession(Request& req, Response& res) {
	Session* session = getSessionFromRequest(req);
	if (session)
		return session;

	Session& newSession = SessionManager::getInstance().createSession();
	Cookie cookie("session_id", newSession.getId());
	cookie.setPath("/");
	cookie.setHttpOnly(true);
	cookie.setMaxAge(SessionManager::getInstance().getSessionTimeout());
	res.addCookie(cookie);
	return &newSession;
}
