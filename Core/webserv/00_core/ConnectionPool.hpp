#ifndef WEBSERV_00_CORE_CONNECTIONPOOL_HPP
#define WEBSERV_00_CORE_CONNECTIONPOOL_HPP

#include <map>
#include <vector>
#include "Connection.hpp"

// -----------------------------------------------------------------------------
// ConnectionPool
// -----------------------------------------------------------------------------
/*
* Manages all active client connections.
*
* Responsibilities:
*  - Add / remove connections
*  - Lookup connections by file descriptor
*  - Cleanup closed connections
*  - Close all connections on shutdown
*  - Enforce a maximum number of connections
*/
class ConnectionPool {
public:
	ConnectionPool(size_t max = 1024);
	~ConnectionPool();

	// Add a new connection to the pool
	// Returns false if max connections reached
	bool addConnection(Connection* conn);

	// Remove a connection by file descriptor
	// Automatically deletes the connection
	bool removeConnection(int fd);

	// Retrieve a connection by file descriptor
	Connection* getConnection(int fd);

	// Get all connections as a vector
	std::vector<Connection*> getAllConnections() const;

	// Remove all connections in CLOSED state
	void cleanupClosed();

	// Close all connections and free memory
	void closeAll();

	// Current number of active connections
	size_t size() const;

	// Maximum allowed connections
	size_t getMaxConnections() const;

	// Available connection slots
	size_t getAvailableSlots() const;

private:
	std::map<int, Connection*> pool_; // map fd -> Connection*
	size_t max_;                       // maximum allowed connections
};

#endif // WEBSERV_00_CORE_CONNECTIONPOOL_HPP
