#include "EventLoop.hpp"
#include "Connection.hpp"
#include <cstring>
#include <cerrno>

// -----------------------------------------------------------------------------
// Constructor / Destructor
// -----------------------------------------------------------------------------
EventLoop::EventLoop(size_t max_connections)
	: epoll_fd_(-1),
	running_(false),
	timeout_ms_(SERVER_POLL_TIME),
	max_events_(static_cast<int>(max_connections)),
	stop_flag_(NULL)
{
	// Create epoll instance
	epoll_fd_ = epoll_create1(0);
	if (epoll_fd_ < 0) {
		Logger::error("EventLoop: epoll_create1() failed");
		throw std::runtime_error("Failed to create epoll instance");
	}
	
	Logger::debug("EventLoop created with epoll, max_connections=" + 
				Utils::toString(max_connections));
}

EventLoop::~EventLoop() {
	stop();
	cleanupClosedConnections();
	
	if (epoll_fd_ >= 0) {
		::close(epoll_fd_);
		epoll_fd_ = -1;
	}
	
	Logger::info("EventLoop destroyed");
}

// -----------------------------------------------------------------------------
// Convert our EventMask to epoll flags
// -----------------------------------------------------------------------------
int EventLoop::eventMaskToEpoll(int mask) {
	int epoll_events = 0;
	
	if (mask & EVENTMASK_READ) {
		epoll_events |= EPOLLIN;
	}
	if (mask & EVENTMASK_WRITE) {
		epoll_events |= EPOLLOUT;
	}
	
	// Always monitor for errors and hangup
	epoll_events |= EPOLLERR | EPOLLHUP;
	
	return epoll_events;
}

// -----------------------------------------------------------------------------
// Socket management
// -----------------------------------------------------------------------------
bool EventLoop::addSocket(int fd, Connection* conn, int events) {
	if (fd < 0) {
		Logger::error("addSocket: invalid fd");
		return false;
	}
	
	if (epoll_fd_ < 0) {
		Logger::error("addSocket: epoll instance not initialized");
		return false;
	}
	
	// Store connection info
	SocketEntry& entry = sockets_[fd];
	entry.conn = conn;
	entry.events = events;
	
	// Register with epoll
	struct epoll_event ev;
	std::memset(&ev, 0, sizeof(ev));
	ev.events = eventMaskToEpoll(events);
	ev.data.fd = fd;
	
	if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &ev) < 0) {
		Logger::error("addSocket: epoll_ctl(ADD) failed for fd=" + Utils::toString(fd));
		sockets_.erase(fd);
		return false;
	}
	
	Logger::debug("Added socket fd=" + Utils::toString(fd) + 
				" events=" + Utils::toString(events));
	return true;
}

bool EventLoop::modifySocket(int fd, Connection* conn, int events) {
	std::map<int, SocketEntry>::iterator it = sockets_.find(fd);
	if (it == sockets_.end()) {
		Logger::warn("modifySocket: fd " + Utils::toString(fd) + " not found");
		return false;
	}
	
	if (epoll_fd_ < 0) {
		Logger::error("modifySocket: epoll instance not initialized");
		return false;
	}
	
	// Update our tracking
	it->second.conn = conn;
	it->second.events = events;
	
	// Modify epoll registration
	struct epoll_event ev;
	std::memset(&ev, 0, sizeof(ev));
	ev.events = eventMaskToEpoll(events);
	ev.data.fd = fd;
	
	if (epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd, &ev) < 0) {
		Logger::error("modifySocket: epoll_ctl(MOD) failed for fd=" + Utils::toString(fd));
		return false;
	}
	
	Logger::debug("Modified socket fd=" + Utils::toString(fd) + " events=" + Utils::toString(events));
	return true;
}

bool EventLoop::removeSocket(int fd) {
	std::map<int, SocketEntry>::iterator it = sockets_.find(fd);
	if (it == sockets_.end()) {
		Logger::debug("removeSocket: fd " + Utils::toString(fd) + " not found");
		return false;
	}
	
	// Remove from epoll (can safely ignore errors here)
	if (epoll_fd_ >= 0) {
		epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, NULL);
	}
	
	// Remove from our tracking
	sockets_.erase(it);
	
	Logger::debug("Removed socket fd=" + Utils::toString(fd));
	return true;
}

// -----------------------------------------------------------------------------
// Poll events (returns vector)
// -----------------------------------------------------------------------------
std::vector<Event> EventLoop::pollEvents() {
	return runOnce();
}

// -----------------------------------------------------------------------------
// Internal runOnce implementation - EPOLL VERSION
// -----------------------------------------------------------------------------
std::vector<Event> EventLoop::runOnce() {
	std::vector<Event> events;
	
	// Check if we should stop
	if (stop_flag_ && *stop_flag_) {
		return events;
	}
	
	if (epoll_fd_ < 0) {
		Logger::error("EventLoop::runOnce epoll_fd invalid");
		return events;
	}
	
	// Allocate array for epoll events
	std::vector<struct epoll_event> epoll_events(max_events_);
	
	// Wait for events
	int nready = epoll_wait(epoll_fd_, &epoll_events[0], max_events_, timeout_ms_);
	
	if (nready < 0) {
		// Subject forbids errno checking, so just log and continue
		Logger::error("EventLoop::runOnce epoll_wait() returned error, continuing");
		return events;
	}
	
	if (nready == 0) {
		// Timeout - normal, just check timeouts
		// Logger::debug("EventLoop::runOnce epoll_wait() timeout (" + Utils::toString(timeout_ms_) + "ms)");
		cleanupClosedConnections();
		return events;
	}
	
	// Process ready file descriptors
	for (int i = 0; i < nready; ++i) {
		int fd = epoll_events[i].data.fd;
		uint32_t epoll_ev = epoll_events[i].events;
		
		// Look up connection
		std::map<int, SocketEntry>::iterator it = sockets_.find(fd);
		if (it == sockets_.end()) {
			Logger::warn("EventLoop::runOnce Event for unknown fd=" + Utils::toString(fd));
			continue;
		}
		
		Connection* conn = it->second.conn;
		
		// Check for errors or hangup first (highest priority)
		if (epoll_ev & EPOLLHUP) {
			Event e = {fd, EVENT_HUP, conn, std::time(NULL)};  // Use EVENT_HUP
			events.push_back(e);
			Logger::debug("EventLoop::runOnce HUP event on fd=" + Utils::toString(fd));
			continue;
		}
		
		// Check for read events
		if (epoll_ev & EPOLLIN) {
			Event e = {fd, EVENT_READ, conn, std::time(NULL)};
			events.push_back(e);
			Logger::debug("EventLoop::runOnce Read event on fd=" + Utils::toString(fd));
		}
		
		// Check for write events
		if (epoll_ev & EPOLLOUT) {
			Event e = {fd, EVENT_WRITE, conn, std::time(NULL)};
			events.push_back(e);
			Logger::debug("EventLoop::runOnce Write event on fd=" + Utils::toString(fd));
		}
	}
	
	// Check for timeouts and add timeout events
	checkTimeouts(events);
	
	// Clean up any closed connections
	cleanupClosedConnections();
	
	Logger::debug("EventLoop::runOnce returning " + Utils::toString(events.size()) + " events");
	return events;
}

// -----------------------------------------------------------------------------
// Stop / Status
// -----------------------------------------------------------------------------
void EventLoop::stop() {
	running_ = false;
	Logger::info("EventLoop stop requested");
}

bool EventLoop::isRunning() const {
	return running_;
}

size_t EventLoop::getConnectionCount() const {
	return sockets_.size();
}

// -----------------------------------------------------------------------------
// Configuration
// -----------------------------------------------------------------------------
void EventLoop::setTimeout(int ms) {
	if (ms > 0) {
		timeout_ms_ = ms;
		Logger::debug("EventLoop timeout set to " + Utils::toString(ms) + "ms");
	}
}

void EventLoop::setMaxEvents(int n) {
	if (n > 0) {
		max_events_ = n;
		Logger::debug("EventLoop max_events set to " + Utils::toString(n));
	}
}

void EventLoop::setStopFlag(volatile sig_atomic_t* flag) {
	stop_flag_ = flag;
}

// -----------------------------------------------------------------------------
// Timeout checking
// -----------------------------------------------------------------------------
void EventLoop::checkTimeouts(std::vector<Event>& events) {
	time_t current_time = Connection::now_ms();
	
	std::map<int, SocketEntry>::iterator it;
	for (it = sockets_.begin(); it != sockets_.end(); ++it) {
		Connection* conn = it->second.conn;
		if (conn && conn->isValid() && conn->isTimedOut()) {
			Event e = {it->first, EVENT_TIMEOUT, conn, current_time / 1000};
			events.push_back(e);
			Logger::warn("Timeout event added for fd=" + Utils::toString(it->first));
		}
	}
}

// -----------------------------------------------------------------------------
// Cleanup closed connections
// -----------------------------------------------------------------------------
void EventLoop::cleanupClosedConnections() {
    std::vector<int> to_remove;
    
    for (std::map<int, SocketEntry>::iterator it = sockets_.begin(); it != sockets_.end(); ++it) {
        Connection* conn = it->second.conn;
        // Add CLOSING state check
        if (conn && (!conn->isValid() || conn->getState() == CLOSING)) {  // ← MODIFY THIS
            to_remove.push_back(it->first);
        }
    }
    
    for (size_t i = 0; i < to_remove.size(); ++i) {
        int fd = to_remove[i];
        Logger::debug("Cleaning up closed connection fd=" + Utils::toString(fd));
        removeSocket(fd);
    }
    
    if (!to_remove.empty()) {
        Logger::debug("Cleaned up " + Utils::toString(to_remove.size()) + " closed connections");
    }
}
