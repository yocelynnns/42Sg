#ifndef WEBSERV_03_HANDLERS_HANDLER_HPP 
#define WEBSERV_03_HANDLERS_HANDLER_HPP 

#include <string>
#include <vector>
#include "01_config/Config.hpp"
#include "02_http/HttpUtils.hpp"
#include "02_http/Request.hpp"
#include "02_http/Response.hpp"
#include "06_utils/Utils.hpp"
#include "05_session/SessionManager.hpp"
#include "05_session/Cookie.hpp"
#include "00_core/Connection.hpp"

class CGI;

// Classes required to be wrapped in the HandlerContext for the handle() member
struct HandlerContext {
	Request& req;		// CHANGED: non-const reference so we can set resolved path
	const ServerConfig& config;
	const Location* loc;
	Connection* conn;	// NEW: Pointer to the connection
	CGI* cgi; 			// NEW: Pointer to the CGI manager
};

// createHandler creates the derived handler based on the ServerConfig and HttpRequest
// handle() will create a response depending on the type of handler created
class Handler {
public:
	virtual ~Handler();
	virtual Response handle(HandlerContext& ctx) = 0;
	static Handler* createHandler(HandlerContext& ctx);
	static bool isMethodAllowed(HttpMethod method, const std::vector<std::string>& allowed);
	static std::string resolvePath(const std::string& request_path, HandlerContext& ctx);
	static bool isPathSafe(const std::string& path, const std::string& root);
	static std::string normalizePath(const std::string& path);

    // Session management
    static Session* getSessionFromRequest(const Request& req);
    static Cookie createSessionCookie(const Session& session);
    static void destroySession(const Request& req);
	static Session* getOrCreateSession(Request& req, Response& res);

protected:
	void setCommonHeaders(Response& response);
};

#endif
