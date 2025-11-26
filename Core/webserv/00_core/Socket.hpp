#ifndef WEBSERV_00_CORE_SOCKET_HPP
#define WEBSERV_00_CORE_SOCKET_HPP

#include <string>       // for std::string
#include <vector>       // for std::vector
#include <ctime>        // for time_t

// -----------------------------------------------------------------------------
// SocketInfo: metadata for a listening socket
// -----------------------------------------------------------------------------
struct SocketInfo {
	int fd;                    // Listening FD
	std::string host;          // Bound host
	int port;                  // Bound port
	int backlog;               // Listen backlog
	time_t created_at;         // Creation time

	// Declaration only - no implementation
	SocketInfo();
};

// -----------------------------------------------------------------------------
// Socket: low-level socket abstraction
// -----------------------------------------------------------------------------
class Socket {
public:
	static int create();
	static bool setNonBlocking(int fd);
	static bool setReuseAddr(int fd, bool reuse = true);

	static bool bind(int fd, const std::string& host, int port);
	static bool listen(int fd, int backlog);
	static int accept(int fd, std::string& ip, int& port);

	static void close(int fd);
};

#endif // WEBSERV_00_CORE_SOCKET_HPP
