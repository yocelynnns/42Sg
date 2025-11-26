#ifndef WEBSERV_03_HANDLERS_AUTOINDEXHANDLER_HPP
#define WEBSERV_03_HANDLERS_AUTOINDEXHANDLER_HPP

#include "Handler.hpp"

class AutoIndexHandler : public Handler {
	public:
		AutoIndexHandler();
		~AutoIndexHandler();
		Response handle(HandlerContext& ctx);

	private:
		std::pair<int, std::string> generateDirectoryListing(const std::string& dirPath, const std::string& requestPath);
};

#endif
