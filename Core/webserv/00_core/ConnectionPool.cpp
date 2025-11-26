#include "ConnectionPool.hpp"
#include "06_utils/Logger.hpp"
#include "06_utils/Utils.hpp"

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------
ConnectionPool::ConnectionPool(size_t max) : max_(max) {
	Logger::debug("ConnectionPool created with max size " + Utils::toString(max_));
}

// -----------------------------------------------------------------------------
// Destructor: clean up all connections
// -----------------------------------------------------------------------------
ConnectionPool::~ConnectionPool() {
	Logger::info("ConnectionPool destroyed, closing all connections");
	closeAll();
}

// -----------------------------------------------------------------------------
// Add a new connection (with validation)
// -----------------------------------------------------------------------------
bool ConnectionPool::addConnection(Connection* conn) {
	if (!conn) {
		Logger::error("Attempted to add null connection");
		return false;
	}
	
	if (pool_.size() >= max_) {
		Logger::warn("ConnectionPool full, cannot add fd " + Utils::toString(conn->getFd()));
		return false;
	}
	
	if (pool_.find(conn->getFd()) != pool_.end()) {
		Logger::warn("Connection fd " + Utils::toString(conn->getFd()) + " already exists");
		return false;
	}
	
	pool_[conn->getFd()] = conn;
	Logger::debug("Added connection fd " + Utils::toString(conn->getFd()) + 
				" (" + Utils::toString(getAvailableSlots()) + " slots remaining)");
	return true;
}

// -----------------------------------------------------------------------------
// FIXED: Remove a connection by file descriptor - Memory Safe
// -----------------------------------------------------------------------------
bool ConnectionPool::removeConnection(int fd) {
	std::map<int, Connection*>::iterator it = pool_.find(fd);
	if (it != pool_.end()) {
		Connection* conn = it->second;
		
		// FIXED: Proper cleanup order to prevent double-close
		if (conn) {
			// Connection destructor will handle closing the fd safely
			Logger::debug("Removing connection fd " + Utils::toString(fd));
			delete conn;  // This calls ~Connection() which calls close()
		}
		
		pool_.erase(it);
		return true;
	}
	
	Logger::warn("Attempted to remove non-existent connection fd " + Utils::toString(fd));
	return false;
}

// -----------------------------------------------------------------------------
// Retrieve a connection by file descriptor
// -----------------------------------------------------------------------------
Connection* ConnectionPool::getConnection(int fd) {
	std::map<int, Connection*>::iterator it = pool_.find(fd);
	if (it != pool_.end())
		return it->second;
	Logger::debug("getConnection: fd " + Utils::toString(fd) + " not found");
	return NULL;
}

// -----------------------------------------------------------------------------
// Get all connections as a vector
// -----------------------------------------------------------------------------
std::vector<Connection*> ConnectionPool::getAllConnections() const {
	std::vector<Connection*> connections;
	for (std::map<int, Connection*>::const_iterator it = pool_.begin();
		it != pool_.end(); ++it) {
		connections.push_back(it->second);
	}
	return connections;
}

// -----------------------------------------------------------------------------
// FIXED: Remove all closed connections - Memory Safe
// -----------------------------------------------------------------------------
void ConnectionPool::cleanupClosed() {
	std::vector<int> to_remove;
	
	for (std::map<int, Connection*>::iterator it = pool_.begin(); it != pool_.end(); ++it) {
		Connection* conn = it->second;
		// Add CLOSING state to cleanup condition
		if (conn && (conn->getState() == CLOSED || 
					conn->getState() == CLOSING ||  // ← ADD THIS
					!conn->isValid())) {
			to_remove.push_back(it->first);
		}
	}
	
	for (size_t i = 0; i < to_remove.size(); ++i) {
		int fd = to_remove[i];
		Logger::debug("Cleaning up closed connection fd " + Utils::toString(fd));
		removeConnection(fd);
	}
	
	if (!to_remove.empty()) {
		Logger::debug("Cleaned up " + Utils::toString(to_remove.size()) + " closed connections");
	}
}

// -----------------------------------------------------------------------------
// FIXED: Close all connections - Memory Safe
// -----------------------------------------------------------------------------
void ConnectionPool::closeAll() {
	// Use two-phase cleanup to avoid iterator invalidation issues
	std::vector<Connection*> connections_to_delete;
	
	// Phase 1: Collect all connections
	for (std::map<int, Connection*>::iterator it = pool_.begin(); it != pool_.end(); ++it) {
		connections_to_delete.push_back(it->second);
	}
	
	// Phase 2: Clear the map first to prevent double-deletion
	pool_.clear();
	
	// Phase 3: Delete all connections
	for (size_t i = 0; i < connections_to_delete.size(); ++i) {
		Connection* conn = connections_to_delete[i];
		if (conn) {
			Logger::debug("Deleting connection fd " + Utils::toString(conn->getFd()));
			delete conn;  // This calls ~Connection() which calls close()
		}
	}
	
	Logger::info("All connections closed");
}

// -----------------------------------------------------------------------------
// Get current number of active connections
// -----------------------------------------------------------------------------
size_t ConnectionPool::size() const {
	return pool_.size();
}

// -----------------------------------------------------------------------------
// Get maximum allowed connections
// -----------------------------------------------------------------------------
size_t ConnectionPool::getMaxConnections() const {
	return max_;
}

// -----------------------------------------------------------------------------
// Get available connection slots
// -----------------------------------------------------------------------------
size_t ConnectionPool::getAvailableSlots() const {
	return max_ - pool_.size();
}
