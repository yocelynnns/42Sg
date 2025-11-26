#ifndef WEBSERV_05_SESSION_SESSIONDEMOHANDLER_HPP
#define WEBSERV_05_SESSION_SESSIONDEMOHANDLER_HPP

#include "03_handlers/Handler.hpp"
#include "05_session/SessionManager.hpp"
#include "05_session/Cookie.hpp"

/*
 * SessionDemoHandler
 * -------------------
 * Handles the bonus demo for session and cookie management.
 *
 * Supported endpoints:
 *   /session/info   -> returns JSON { logged_in, visits }
 *   /session/login  -> marks user as logged in
 *   /session/logout -> logs out user
 *   /session/clear  -> clears session and cookie
 *
 * Used by Handler::createHandler() when URI starts with "/session".
 * Demonstrates cookie persistence, session storage, and cleanup.
 */
class SessionDemoHandler : public Handler {
public:
	SessionDemoHandler() {}
	virtual ~SessionDemoHandler() {}

	virtual Response handle(HandlerContext& ctx);
};

#endif // WEBSERV_05_SESSION_SESSIONDEMOHANDLER_HPP
