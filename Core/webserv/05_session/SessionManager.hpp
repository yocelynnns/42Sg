#ifndef WEBSERV_05_SESSION_SessionManager_HPP
#define WEBSERV_05_SESSION_SessionManager_HPP

#include "Session.hpp"
#include <map>
#include <string>
#include <ctime>

class SessionManager {
public:
	static SessionManager& getInstance();
	
	Session& createSession();
	Session* getSession(const std::string& sessionId);
	bool destroySession(const std::string& sessionId);
	void cleanupExpiredSessions();
	
	void setSessionTimeout(std::time_t timeout);
	std::time_t getSessionTimeout() const;
	
	size_t getActiveSessionsCount() const;
	
private:
	SessionManager();
	SessionManager(const SessionManager&);
	SessionManager& operator=(const SessionManager&);
	
	std::string generateSessionId();
	
	std::map<std::string, Session> sessions_;
	std::time_t sessionTimeout_;
};

#endif // WEBSERV_05_SESSION_SessionManager_HPP
