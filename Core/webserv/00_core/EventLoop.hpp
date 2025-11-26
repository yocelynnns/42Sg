#ifndef WEBSERV_00_CORE_EVENTLOOP_HPP
#define WEBSERV_00_CORE_EVENTLOOP_HPP

#include <map>
#include <vector>
#include <ctime>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/epoll.h>  // CHANGED: Use epoll instead of select
#include <csignal>

#include "Connection.hpp"
#include "06_utils/Logger.hpp"
#include "06_utils/Utils.hpp"

#define SERVER_POLL_TIME 20

// -----------------------------------------------------------------------------
// Event types
// -----------------------------------------------------------------------------
enum EventType {
	EVENT_READ,
	EVENT_WRITE,
	EVENT_ERROR,
	EVENT_TIMEOUT,
	EVENT_HUP
};

// -----------------------------------------------------------------------------
// EventMask: bitmask for monitoring
// -----------------------------------------------------------------------------
enum EventMask {
	EVENTMASK_READ  = 1 << 0,
	EVENTMASK_WRITE = 1 << 1
};

// -----------------------------------------------------------------------------
// Event structure
// -----------------------------------------------------------------------------
struct Event {
	int fd;
	EventType type;
	Connection* conn;
	time_t timestamp;
};

// -----------------------------------------------------------------------------
// EventLoop class
// -----------------------------------------------------------------------------
class EventLoop {
public:
	explicit EventLoop(size_t max_connections = 1024);
	~EventLoop();

	// Socket management
	bool addSocket(int fd, Connection* conn, int events);      // REGISTER
	bool modifySocket(int fd, Connection* conn, int events);   // MODIFY
	bool removeSocket(int fd);                                 // UNREGISTER

	// Poll events (returns vector of events)
	std::vector<Event> pollEvents();

	// Stop / Status
	void stop();
	bool isRunning() const;
	size_t getConnectionCount() const;

	// Configuration
	void setTimeout(int ms);                          // epoll_wait() timeout in ms
	void setMaxEvents(int n);                         // Limit number of events returned
	void setStopFlag(volatile sig_atomic_t* flag);

private:
	struct SocketEntry {
		Connection* conn;
		int events;  // Our internal event mask (EVENTMASK_READ | EVENTMASK_WRITE)
		SocketEntry() : conn(NULL), events(0) {}
	};

	std::map<int, SocketEntry> sockets_;
	
	int epoll_fd_;                           // NEW: epoll file descriptor
	bool running_;
	int timeout_ms_;
	int max_events_;
	volatile sig_atomic_t* stop_flag_;

	// Internal helpers
	std::vector<Event> runOnce();
	void checkTimeouts(std::vector<Event>& events);
	void cleanupClosedConnections();
	int eventMaskToEpoll(int mask);          // NEW: Convert our mask to epoll flags
	
	// Disable copy
	EventLoop(const EventLoop&);
	EventLoop& operator=(const EventLoop&);
};

#endif // WEBSERV_00_CORE_EVENTLOOP_HPP
