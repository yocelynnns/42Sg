#ifndef WEBSERV_03_HANDLERS_ErrorHandler_HPP
#define WEBSERV_03_HANDLERS_ErrorHandler_HPP

#include "Handler.hpp"
#include <errno.h> // For errno constants
#include <cstring> 


class ErrorHandler : public Handler {
public:
	ErrorHandler();
	ErrorHandler(int status);
	ErrorHandler(int status, const std::string& url);		// Redirect OR return

	~ErrorHandler();
	Response handle(HandlerContext& ctx);

	// NEW: Static helper to build error response without HandlerContext
	static Response buildErrorResponse(int status, const ServerConfig& config);
	static Response buildResponseWithLocation(int code, const std::string& url);

private:
	int _status;
	std::string _location_url;  // Empty = error page, Non-empty = redirect/return
};

#endif
