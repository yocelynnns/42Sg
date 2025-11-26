#include "SessionManager.hpp"
#include "06_utils/Utils.hpp"
#include <cstdlib>
#include <ctime>

SessionManager::SessionManager() : sessionTimeout_(SESSION_TIMEOUT_24HOURS) { // 24 hours default
    std::srand(std::time(NULL));
}

SessionManager& SessionManager::getInstance() {
	static SessionManager instance;
	return instance;
}

// Generate random 32-char session ID
std::string SessionManager::generateSessionId() {
	static const std::string chars =
	    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	std::string result;
	for (int i = 0; i < 32; ++i)
		result += chars[std::rand() % chars.size()];
	return result;
}

Session& SessionManager::createSession() {
	cleanupExpiredSessions(); // 🧹 occasionally prune old sessions

	std::string sessionId;
	do {
		sessionId = generateSessionId();
	} while (sessions_.find(sessionId) != sessions_.end()); // avoid collision

	Session newSession(sessionId);
	newSession.setExpiration(std::time(NULL) + sessionTimeout_);

	sessions_[sessionId] = newSession;
	return sessions_[sessionId];
}

Session* SessionManager::getSession(const std::string& sessionId) {
	std::map<std::string, Session>::iterator it = sessions_.find(sessionId);
	if (it != sessions_.end()) {
		if (!it->second.isExpired()) {
			it->second.updateAccessTime();
			return &(it->second);
		}
		sessions_.erase(it);
	}
	return NULL;
}

bool SessionManager::destroySession(const std::string& sessionId) {
	return sessions_.erase(sessionId) > 0;
}

// 🧹 Periodic cleanup — can be called every N requests or in createSession()
void SessionManager::cleanupExpiredSessions() {
	for (std::map<std::string, Session>::iterator it = sessions_.begin();
		it != sessions_.end();) {
			if (it->second.isExpired())
				sessions_.erase(it++);
			else
				++it;
		}
}

void SessionManager::setSessionTimeout(std::time_t timeout) {
	sessionTimeout_ = timeout;
}

std::time_t SessionManager::getSessionTimeout() const {
	return sessionTimeout_;
}

size_t SessionManager::getActiveSessionsCount() const {
	return sessions_.size();
}
