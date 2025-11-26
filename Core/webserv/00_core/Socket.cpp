#include "Socket.hpp"
#include "06_utils/Logger.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

// -----------------------------------------------------------------------------
// Constructor for SocketInfo
// -----------------------------------------------------------------------------
SocketInfo::SocketInfo() : fd(-1), port(0), backlog(512), created_at(0) {}

// -----------------------------------------------------------------------------
// Create a new TCP socket (IPv4)
// -----------------------------------------------------------------------------
int Socket::create() {
	int fd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
		Logger::error("Socket::create failed");
	else
		Logger::debug("Socket created, fd=" + Utils::toString(fd));
	return fd;
}

// -----------------------------------------------------------------------------
// Set a socket to non-blocking mode
// -----------------------------------------------------------------------------
bool Socket::setNonBlocking(int fd) {
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1) {
		Logger::error("setNonBlocking F_GETFL failed");
		return false;
	}
	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
		Logger::error("setNonBlocking F_SETFL failed");
		return false;
	}
	Logger::debug("Socket fd=" + Utils::toString(fd) + " set to non-blocking");
	return true;
}

// -----------------------------------------------------------------------------
// Enable or disable SO_REUSEADDR
// -----------------------------------------------------------------------------
bool Socket::setReuseAddr(int fd, bool reuse) {
	int opt = reuse ? 1 : 0;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
		Logger::warn("setReuseAddr failed");
		return false;
	}
	Logger::debug("Socket fd=" + Utils::toString(fd) + " reuseaddr=" + (reuse ? "true" : "false"));
	return true;
}

// -----------------------------------------------------------------------------
// Bind socket to a host:port
// -----------------------------------------------------------------------------
bool Socket::bind(int fd, const std::string& host, int port) {
	struct sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	if (host.empty()) {
		addr.sin_addr.s_addr = INADDR_ANY;
	} else {
		if (inet_pton(AF_INET, host.c_str(), &addr.sin_addr) <= 0) {
			Logger::error("Socket::bind invalid IP address: " + host);
			return false;
		}
	}

	if (::bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		Logger::error("Socket::bind failed on " + host + ":" + Utils::toString(port));
		return false;
	}

	Logger::debug("Socket bound to " + host + ":" + Utils::toString(port));
	return true;
}

// -----------------------------------------------------------------------------
// Start listening on a socket
// -----------------------------------------------------------------------------
bool Socket::listen(int fd, int backlog) {
	if (::listen(fd, backlog) == -1) {
		Logger::error("Socket::listen failed");
		return false;
	}
	Logger::debug("Socket fd=" + Utils::toString(fd) + " listening with backlog=" + Utils::toString(backlog));
	return true;
}

// -----------------------------------------------------------------------------
// Accept a new connection and retrieve remote IP/port
// FIXED: No errno usage - compliant with webserv subject
// -----------------------------------------------------------------------------
int Socket::accept(int fd, std::string& ip, int& port) {
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);
	int client_fd = ::accept(fd, (struct sockaddr*)&addr, &addrlen);
	
	if (client_fd >= 0) {
		// Success - extract client information
		char buf[INET_ADDRSTRLEN];
		if (inet_ntop(AF_INET, &addr.sin_addr, buf, sizeof(buf))) {
			ip = buf;
			port = ntohs(addr.sin_port);
			Logger::debug("Accepted connection fd=" + Utils::toString(client_fd) + 
						" from " + ip + ":" + Utils::toString(port));
		} else {
			// inet_ntop failed - use fallback
			ip = "unknown";
			port = 0;
			Logger::warn("Could not determine client address for fd=" + Utils::toString(client_fd));
		}
	} else {
		// Accept failed - could be EAGAIN/EWOULDBLOCK (no pending connections)
		// or a real error. We don't check errno per subject requirements.
		// Just return the error code and let caller handle it.
		Logger::debug("Socket::accept returned " + Utils::toString(client_fd));
	}
	
	return client_fd;
}

// -----------------------------------------------------------------------------
// Close a socket safely
// -----------------------------------------------------------------------------
void Socket::close(int fd) {
	if (fd >= 0) {
		::close(fd);
		Logger::debug("Socket fd=" + Utils::toString(fd) + " closed");
	}
}
