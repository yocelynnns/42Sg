#ifndef WEBSERV_04_CGI_HANDLER_HPP
#define WEBSERV_04_CGI_HANDLER_HPP

#include "04_cgi/CGI.hpp"
#include "02_http/Response.hpp"
#include "02_http/Request.hpp"
#include "01_config/Config.hpp"
#include "03_handlers/Handler.hpp"
#include <string>
#include <vector>
#include <map>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*
* CGIHandler
*
* Handles execution of CGI scripts based on server configuration and request.
* Responsible for:
*   1. Checking if a request should be handled as CGI.
*   2. Building CGI environment and arguments.
*   3. Executing the script via the CGI module.
*   4. Converting CGI response into an HTTP response.
*/
class CGIHandler : public Handler {
private:
	CGI &cgi_; // Core CGI executor

public:
	CGIHandler(CGI& cgi);
	~CGIHandler();

	// Returns true if this handler can process the request
	bool canHandle(const Request& req, const Location& loc) const;

	// Execute CGI and return HTTP Response
	Response handle(HandlerContext& ctx);

private:
	// Convert CGIResponse into HTTP Response
	Response convertToHttpResponse(const CGIResponse& cgi_resp) const;
};

#endif // WEBSERV_04_CGI_HANDLER_HPP
