#include "04_cgi/CGIHandler.hpp"
#include "04_cgi/CGI.hpp"
#include "03_handlers/ErrorHandler.hpp"
#include "06_utils/Logger.hpp"
#include <sstream>
#include <stdexcept>
#include <map>

CGIHandler::CGIHandler(CGI& cgi) : cgi_(cgi) {
}

CGIHandler::~CGIHandler() {}

bool CGIHandler::canHandle(const Request& req, const Location& loc) const {
	// Location must have CGI enabled
	if (!loc.cgi_enable && loc.cgi_extensions.empty())
		return false;

	// Check if request path matches a supported CGI extension
	std::string path = req.getPath();
	size_t dot_pos = path.find_last_of('.');
	if (dot_pos == std::string::npos)
		return false;

	std::string ext = path.substr(dot_pos);
	for (size_t i = 0; i < loc.cgi_extensions.size(); ++i) {
		if (loc.cgi_extensions[i] == ext)
			return true;
	}

	return false;
}

Response CGIHandler::handle(HandlerContext& ctx) {
	Response resp;

	// Check if CGI is enabled for this location
	if (!ctx.loc || !ctx.loc->cgi_enable) {
		return ErrorHandler(404).handle(ctx);
	}

	// Check if we have a resolved path
	if (!ctx.req.hasResolvedPath()) {
		return ErrorHandler(500).handle(ctx);
	}

	if (!cgi_.canExecute(ctx)) {
		return ErrorHandler(503).handle(ctx);
	}

	try {
		// Register interpreters
		for (std::map<std::string, std::string>::const_iterator it = ctx.loc->cgi_interpreters.begin();
			it != ctx.loc->cgi_interpreters.end(); ++it) {
			std::vector<std::string> args;
			cgi_.addInterpreter(it->first, it->second, args);
		}

		if (!ctx.loc->default_cgi_interpreter.empty()) {
			std::vector<std::string> args;
			for (size_t i = 0; i < ctx.loc->cgi_extensions.size(); ++i) {
				const std::string& ext = ctx.loc->cgi_extensions[i];
				if (ctx.loc->cgi_interpreters.find(ext) == ctx.loc->cgi_interpreters.end()) {
					cgi_.addInterpreter(ext, ctx.loc->default_cgi_interpreter, args);
				}
			}
		}

		// Validate script
		struct stat sb;
		const std::string& script_path = ctx.req.getResolvedPath();
		if (stat(script_path.c_str(), &sb) != 0 || !(sb.st_mode & S_IXUSR)) {
			return ErrorHandler(404).handle(ctx);
		}

		Logger::debug("CGIHandler::handle Executing CGI script: " + script_path);

		// ========== USE ASYNC EXECUTION INSTEAD OF BLOCKING ==========
		// ========== FIX: Don't return a response, just set state ==========
		if (cgi_.executeAsync(ctx, ctx.conn->getFd())) {
			// Set connection state to waiting for CGI
			ctx.conn->setState(WAITING_FOR_CGI);

			// // CRITICAL: Update timeout to CGI timeout value, 
			// int cgi_timeout_ms = cgi_.getTimeout(ctx) * 1000;
			// ctx.conn->setTimeout(cgi_timeout_ms);

			Logger::debug("CGIHandler::handle CGI execution started async for fd=" +
						Utils::toString(ctx.conn->getFd()));
			
			// Return empty response - Server will check the state and not send it
			Response empty_resp;
			return empty_resp;  // Doesn't matter what we return
		}

	} catch (const std::exception& e) {
		Logger::error("CGIHandler::handle execution failed: " + std::string(e.what()));
		return ErrorHandler(500).handle(ctx);	
	}

	return resp;
}

Response CGIHandler::convertToHttpResponse(const CGIResponse& cgi_resp) const {
	Response resp;

	// Set status
	resp.setStatus(cgi_resp.http_status);

	// Copy headers
	for (std::map<std::string,std::string>::const_iterator it = cgi_resp.headers.begin();
		it != cgi_resp.headers.end(); ++it) {
		resp.setHeader(it->first, it->second);
	}

	// Set body
	resp.setBody(cgi_resp.body);

	return resp;
}
