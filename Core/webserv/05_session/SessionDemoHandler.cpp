#include "SessionDemoHandler.hpp"
#include <sstream>

/*
* SessionDemoHandler
* -------------------
* Endpoints:
*   /session/info   -> returns session status + visit count
*   /session/login  -> marks session as logged in
*   /session/logout -> marks session as logged out
*   /session/clear  -> destroys session and clears cookie
*/
Response SessionDemoHandler::handle(HandlerContext& ctx) {
	Request& req = ctx.req;
	Response res;

	Handler::setCommonHeaders(res);
	res.setContentType("application/json");

	// ✅ Automatically get or create a session + cookie
	Session* session = Handler::getOrCreateSession(req, res);

	std::string uri = req.getUri();
	std::ostringstream body;

	// ----- /session/clear -----
	if (uri.find("/session/clear") == 0) {
		Handler::destroySession(req);

		Cookie cookie("session_id", "");
		cookie.setPath("/");
		cookie.setMaxAge(0); // delete cookie
		res.addCookie(cookie);

		body << "{\"status\":\"cleared\"}";
	}

	// ----- /session/login -----
	else if (uri.find("/session/login") == 0) {
		session->setData("logged_in", "true");
		session->setData("visits", "0");
		body << "{\"status\":\"logged_in\"}";
	}

	// ----- /session/logout -----
	else if (uri.find("/session/logout") == 0) {
		session->removeData("logged_in");
		body << "{\"status\":\"logged_out\"}";
	}

	// ----- /session/info -----
	else if (uri.find("/session/info") == 0) {
		bool logged = session->hasData("logged_in");
		int visits = 0;

		if (logged) {
			if (session->hasData("visits"))
				visits = std::atoi(session->getData("visits").c_str());
			visits++;
			std::ostringstream oss;
			oss << visits;
			session->setData("visits", oss.str());
		}

		body << "{\"logged_in\":" << (logged ? "true" : "false")
			<< ",\"visits\":" << visits << "}";
	}

	// ----- invalid endpoint -----
	else {
		res.setStatus(404);
		body << "{\"error\":\"invalid endpoint\"}";
	}

	res.setBody(body.str());
	res.setStatus(200);
	return res;
}
