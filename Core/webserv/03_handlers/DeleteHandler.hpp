#ifndef WEBSERV_03_HANDLERS_DELETEHANDLER_HPP
#define WEBSERV_03_HANDLERS_DELETEHANDLER_HPP

#include "Handler.hpp"

class DeleteHandler : public Handler {
public:
	DeleteHandler();
	~DeleteHandler();
	Response handle(HandlerContext& ctx);

private:
	bool isDeletionSafe(const std::string& path, HandlerContext& ctx);
};

#endif
