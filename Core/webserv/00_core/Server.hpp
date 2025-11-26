#ifndef WEBSERV_00_CORE_SERVER_HPP
#define WEBSERV_00_CORE_SERVER_HPP

#include <csignal>
#include <vector>
#include <string>
#include "01_config/Config.hpp"
#include "00_core/Connection.hpp"
#include "00_core/ConnectionPool.hpp"
#include "00_core/EventLoop.hpp"
#include "00_core/Socket.hpp"
#include "06_utils/Logger.hpp"
#include "06_utils/Utils.hpp"
#include "04_cgi/CGI.hpp"

const int DEFAULT_MAX_ACCEPTS_PER_LOOP = 50;

// -----------------------------------------------------------------------------
// Server
// -----------------------------------------------------------------------------
// Central orchestrator for the webserv project. Manages listening sockets,
// event loop, connection pool, configuration reloads, and graceful shutdown.
// -----------------------------------------------------------------------------
class Server {
public:
	explicit Server(const std::string& config_file);
	~Server();

	// Lifecycle
	bool start();
	void stop();

	// Listening sockets
	bool createListeningSockets();
	void closeListeningSockets();

	// Signals
	void setShutdownFlag(volatile sig_atomic_t* flag);
	void setReloadFlag(volatile sig_atomic_t* flag);

	// Reload configuration
	bool reloadConfig();

	void processCGICompletions();

private:
	// Event handlers
	void updateListeningSocketsFromConfig();
	void processReadEvent(int fd, Connection* conn);
	void processWriteEvent(int fd, Connection* conn);
	void processErrorEvent(int fd, Connection* conn);
	void acceptNewConnection(SocketInfo& sock);
	void checkConnectionTimeouts();

	// Internal helpers
	void cleanupResources();
	void gracefulShutdownConnections();
	void updateConnectionSettings();
	bool rollbackConfig(const Config& old_config);
	void cleanupConnections(); 
	void processHangupEvent(int fd, Connection* conn);

	// Members
	EventLoop* loop_;
	ConnectionPool* conn_pool_;
	std::vector<SocketInfo> listen_sockets_;
	volatile sig_atomic_t* shutdown_flag_;
	volatile sig_atomic_t* reload_flag_;
	std::string config_file_;
	CGI cgi_;
	Config config_;

	// Prevent copying
	Server(const Server&);
	Server& operator=(const Server&);
};

#endif // WEBSERV_00_CORE_SERVER_HPP
