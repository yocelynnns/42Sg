#ifndef WEBSERV_03_HANDLERS_STATICFILEHANDLER_HPP
#define WEBSERV_03_HANDLERS_STATICFILEHANDLER_HPP

#include "Handler.hpp"

class StaticFileHandler : public Handler {
public:
	StaticFileHandler();
	~StaticFileHandler();
	Response handle(HandlerContext& ctx);

private:
	bool serveFile(const std::string& filePath, Response& res, std::string method);
};

#endif
