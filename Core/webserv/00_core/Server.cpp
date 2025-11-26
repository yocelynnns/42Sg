#include "Server.hpp"
#include "01_config/Config.hpp"
#include "02_http/Response.hpp"
#include "03_handlers/Handler.hpp"
#include "03_handlers/ErrorHandler.hpp"
#include "06_utils/Logger.hpp"
#include "06_utils/Utils.hpp"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <ctime>

// -----------------------------------------------------------------------------
// updateListeningSocketsFromConfig - FIXED: deduplicate host:port
// -----------------------------------------------------------------------------
void Server::updateListeningSocketsFromConfig() {
	listen_sockets_.clear();

	for (size_t i = 0; i < config_.getGlobalConfig().http.servers.size(); ++i) {
		const ServerConfig& server_cfg = config_.getGlobalConfig().http.servers[i];
		bool exists = false;

		for (size_t j = 0; j < listen_sockets_.size(); ++j) {
			if (listen_sockets_[j].host == server_cfg.host &&
				listen_sockets_[j].port == server_cfg.port) {
				exists = true;
				break;
			}
		}

		if (!exists) {
			SocketInfo new_sock;
			new_sock.host = server_cfg.host;
			new_sock.port = server_cfg.port;
			new_sock.backlog = 128;
			new_sock.created_at = std::time(NULL);
			listen_sockets_.push_back(new_sock);
		}
	}
}

// -----------------------------------------------------------------------------
// Constructor / Destructor
// -----------------------------------------------------------------------------
Server::Server(const std::string& config_file)
	: loop_(NULL),
	conn_pool_(NULL),
	shutdown_flag_(NULL),
	reload_flag_(NULL),
	config_file_(config_file),
	cgi_(),
	config_()
	{
	// Load config in constructor
	if (!config_.load(config_file_)) {
		throw std::runtime_error("Failed to load configuration: " + config_file_);
	}
	
	loop_ = new EventLoop(1024);
	conn_pool_ = new ConnectionPool(1024);
	updateListeningSocketsFromConfig();
}

Server::~Server() {
	stop();
	closeListeningSockets();
	cleanupResources();
	delete loop_;
	delete conn_pool_;
}

// -----------------------------------------------------------------------------
// Signal flag setters
// -----------------------------------------------------------------------------
void Server::setShutdownFlag(volatile sig_atomic_t* flag) { shutdown_flag_ = flag; }
void Server::setReloadFlag(volatile sig_atomic_t* flag)   { reload_flag_ = flag; }

// -----------------------------------------------------------------------------
// processReadEvent - UPDATED: Handle CGI async execution
// -----------------------------------------------------------------------------
void Server::processReadEvent(int fd, Connection* conn) {
	if (!conn) {
		// Listening socket: accept new connections
		for (size_t i = 0; i < listen_sockets_.size(); ++i) {
			if (listen_sockets_[i].fd == fd) {
				acceptNewConnection(listen_sockets_[i]);
				break;
			}
		}
		return;
	}

	ssize_t n = conn->readData();
	if (n <= 0) {
		Logger::debug("Closing client fd=" + Utils::toString(fd));
		conn->setState(CLOSING);
		loop_->removeSocket(fd);
		// conn_pool_->removeConnection(fd);
		return;
	}

	RequestParser& parser = conn->getParser();
	HttpRequest& http_req = conn->getHttpRequest();

	ParseState state = parser.parse(conn->getReadBuffer(), http_req);
	size_t consumed = parser.getBytesConsumed();
	if (consumed > 0) {
		conn->consumeReadBuffer(consumed);
		parser.resetBytesConsumed();
	}

	// === CONTENT-LENGTH VALIDATION (FIXED) ===
	if (http_req.content_length > 0 && state == PARSING_BODY) {
		size_t content_length = http_req.content_length; // Already parsed!
		
		const ServerConfig* srv = config_.findServer(http_req.host, http_req.port);
		size_t max_body_size = srv ? srv->client_max_body_size : 1048576;
		
		if (content_length > max_body_size) {
			// Send 413 immediately
			Response too_large = ErrorHandler::buildErrorResponse(413, *srv);
			too_large.setHeader("Connection", "close");
			conn->setKeepAlive(false);
			conn->writeData(too_large.toString());
			conn->setState(WRITING_RESPONSE);
			loop_->modifySocket(fd, conn, EVENTMASK_READ | EVENTMASK_WRITE);
			
			// Clean up
			conn->clearReadBuffer();
			conn->resetForNewRequest();
			parser.reset();
			http_req = HttpRequest();
			return;
		}
	}

	if (state == PARSING_REQUEST_LINE || state == PARSING_HEADERS || state == PARSING_BODY) {
		Logger::debug("Waiting for more data fd=" + Utils::toString(fd) +
					" state=" + Utils::toString(state));
		return;
	}

	if (state == PARSING_BODY) {
		// Find server config
		const ServerConfig* srv = config_.findServer(http_req.host, http_req.port);
		if (!srv && !config_.getGlobalConfig().http.servers.empty()) {
			srv = &config_.getGlobalConfig().http.servers[0];
		}
		
		// Update timeout to client_body_timeout if reading body
		if (srv && srv->client_body_timeout > 0) {
				int body_timeout_ms = srv->client_body_timeout * 1000;
				conn->setTimeout(body_timeout_ms);
				Logger::debug("Switched to body timeout: " + Utils::toString(srv->client_body_timeout) + 
							" seconds for fd=" + Utils::toString(fd));
		}
		
		Logger::debug("Waiting for request body fd=" + Utils::toString(fd));
		return;
	}

	if (state == ERROR) {
		Logger::warn("Request parse error fd=" + Utils::toString(fd) + ": " + parser.getError());
		
		// Send 400 response before closing
		const ServerConfig* srv = config_.findServer(http_req.host, conn->getInfo().server_port);
		if (!srv && !config_.getGlobalConfig().http.servers.empty()) {
			srv = &config_.getGlobalConfig().http.servers[0];
		}
		
		if (srv) {
			Response badRequest = ErrorHandler::buildErrorResponse(400, *srv);
			conn->writeData(badRequest.toString());
			conn->setState(WRITING_RESPONSE);
			loop_->modifySocket(fd, conn, EVENTMASK_READ | EVENTMASK_WRITE);
		} else {
			conn->setState(CLOSING);
			loop_->removeSocket(fd);
		}
		
		conn->clearReadBuffer();
		conn->resetForNewRequest();
		parser.reset();
		http_req = HttpRequest();
		return;
	}

	// NEW: Handle HTTP Version Not Supported (505)
	if (state == UNKNOWN_VERSION) {
		Logger::warn("Unsupported HTTP version on fd=" + Utils::toString(fd));
		
		// Find server config to use error page
		const ServerConfig* srv = NULL;
		if (!http_req.host.empty()) {
			srv = config_.findServer(http_req.host, conn->getInfo().server_port);
		}
		if (!srv && !config_.getGlobalConfig().http.servers.empty()) {
			srv = &config_.getGlobalConfig().http.servers[0];
		}
		
		if (srv) {
			// Build 505 response using ErrorHandler
			Response versionResp = ErrorHandler::buildErrorResponse(505, *srv);
			versionResp.setHeader("Connection", "close");
			
			conn->setKeepAlive(false);
			conn->writeData(versionResp.toString());
			conn->setState(WRITING_RESPONSE);
			loop_->modifySocket(fd, conn, EVENTMASK_READ | EVENTMASK_WRITE);
		} else {
			// No config available - just close
			conn->setState(CLOSING);
			loop_->removeSocket(fd);
			// conn_pool_->removeConnection(fd);
		}
		
		// Clean up
		conn->clearReadBuffer();
		conn->resetForNewRequest();
		parser.reset();
		http_req = HttpRequest();
		return;
	}

	if (state == COMPLETE) {
		conn->setState(PROCESSING);
		Logger::debug("Complete request parsed fd=" + Utils::toString(fd));

		// ----- FIX: ensure we have full body before handling -----
		std::map<std::string,std::string>::iterator it = http_req.headers.find("Content-Length");
		if (it != http_req.headers.end()) {
			size_t expected = std::atoi(it->second.c_str());
			if (http_req.body.size() < expected) {
				Logger::warn("Incomplete body detected (" +
							Utils::toString(http_req.body.size()) + "/" +
							Utils::toString(expected) +
							" bytes), waiting for more data");
				conn->setState(READING_REQUEST);
				return; // defer handling until full body is received
			}
		}

		// ========== KEEP-ALIVE LOGIC  ==========
		bool keep_alive = true;

		// Check client's Connection header
		std::string connection_header = http_req.headers["Connection"];
		if (Utils::toLowerCase(connection_header) == "close") {
			keep_alive = false;
		}

		// HTTP/1.0 defaults to close unless explicitly keep-alive
		if (http_req.version == HTTP_1_0) {
			keep_alive = (Utils::toLowerCase(connection_header) == "keep-alive");
		}

		conn->setKeepAlive(keep_alive);
		Logger::debug("Keep-alive set to " + std::string(keep_alive ? "true" : "false") + 
					" for fd=" + Utils::toString(fd) + 
					" (HTTP/" + (http_req.version == HTTP_1_0 ? "1.0" : "1.1") + ")");
		// ========== END KEEP-ALIVE LOGIC ==========

		// Wrap request and choose a handler
		Request req(http_req);

		// 1. Identify the correct server block (by host/port)
		const ServerConfig* server = config_.findServer(req.getHost(), req.getPort());
		if (!server) {
			// No matching server found - use first server as default
			Logger::warn("No matching server for " + req.getHost() + ":" + 
						Utils::toString(req.getPort()) + ", using default");
			if (config_.getGlobalConfig().http.servers.empty()) {
				Logger::error("No servers configured!");
				conn->setState(CLOSING);
				return;
			}
			server = &config_.getGlobalConfig().http.servers[0];
		}

		// 2. Identify the correct location block (by URI prefix)
		Logger::debug("Server - Finding location for URI: " + req.getUri());
		const Location* location = config_.findLocation(*server, req.getUri());
		if (location) {
			Logger::debug("Server - Found location: " + location->path + " -> " + location->root);
		} else {
			Logger::debug("Server - No location found for URI: " + req.getUri());
		}

		// 3. Prepare handler context
		HandlerContext ctx = {
			req,         // Parsed request
			*server,     // Matched server config
			location,    // Matched location (can be NULL)
			conn,		 // Connection pointer
			&cgi_
		};

		// 4. Create appropriate handler based on method and context
		Handler* handler = Handler::createHandler(ctx);

		// 5. Generate response
		Response res = handler->handle(ctx);

		// 6. Check if this is an async CGI response (don't send immediately)
		if (conn->getState() == WAITING_FOR_CGI) {
			// CGI is executing asynchronously - don't send response yet
			Logger::debug("CGI async in progress for fd=" + Utils::toString(fd) + ", NOT sending response");
			delete handler;
			// Keep monitoring for client disconnect only (CGI will push response when done)
			loop_->modifySocket(fd, conn, EVENTMASK_READ);
			return;  // EXIT WITHOUT SENDING ANYTHING
		}

		// 7. Clean up handler
		delete handler;

		// 8. Send response back to client
		std::string connection_value = conn->getKeepAlive() ? "keep-alive" : "close";
		res.setHeader("Connection", connection_value);


		conn->writeData(res.toString());
		conn->setState(WRITING_RESPONSE);

		// ========== CLEAN UP REQUEST DATA ==========
		conn->consumeReadBuffer(parser.getBytesConsumed());
		parser.reset();
		http_req = HttpRequest();  // Reset request
		conn->resetForNewRequest();
		Logger::debug("Request data cleared for fd=" + Utils::toString(fd));

		// Monitor for writes
		loop_->modifySocket(fd, conn, EVENTMASK_READ | EVENTMASK_WRITE);
	}
}

// -----------------------------------------------------------------------------
// processWriteEvent
// -----------------------------------------------------------------------------
void Server::processWriteEvent(int fd, Connection* conn) {
    // FIRST: Check if pointer is null
    if (!conn) {
        Logger::debug("processWriteEvent called with null connection fd=" + Utils::toString(fd));
        return;
    }
    
    // Verify connection still exists in pool and hasn't been marked for deletion
    Connection* pool_conn = conn_pool_->getConnection(fd);
    if (!pool_conn || pool_conn != conn) {
        Logger::debug("processWriteEvent: connection fd=" + Utils::toString(fd) + " already removed");
        return;
    }
    
    // Check if marked for closing (from processReadEvent or processErrorEvent)
    ConnectionState state = conn->getState();
    if (state == CLOSING || state == CLOSED) {
        Logger::debug("processWriteEvent: connection fd=" + Utils::toString(fd) + " is closing, skipping");
        return;  // Will be cleaned up by cleanupClosed()
    }

	ssize_t n = conn->flushWriteBuffer();

	// Handle write errors or connection closure (n <= 0)
	if (n < 0) {
		// n < 0: Write error occurred (ECONNRESET, EPIPE, etc.)
		Logger::error("Server::processWriteEvent Write error on fd=" + Utils::toString(fd));
		conn->setState(CLOSING);
		// conn->close();
		loop_->removeSocket(fd);
		// conn_pool_->removeConnection(fd);
		return;
	}

	if (n == 0 && conn->hasDataToWrite()) {
		// n == 0 with data remaining: Socket closed by peer or not writable
		// This is unusual - if select() indicated writability but write() returns 0
		// with data remaining, the connection is likely broken
		Logger::warn("Server::processWriteEvent Write returned 0 on fd " + Utils::toString(fd) + " with pending data, closing");
		conn->setState(CLOSING);
		loop_->removeSocket(fd);
		// conn_pool_->removeConnection(fd);
		return;
	}

	// Check if all data has been written
	if (!conn->hasDataToWrite()) {
		if (conn->getState() == WRITING_RESPONSE) {
			if (conn->getKeepAlive()) {
				Logger::debug("Server::processWriteEvent Response sent, keeping connection alive (fd " + Utils::toString(fd) + ")");
				
				// RESET CONNECTION FOR NEXT REQUEST
				conn->setState(READING_REQUEST);
				conn->updateActivity(); // Reset timeout timer
				
				// Clear parser state
				RequestParser& parser = conn->getParser();
				parser.reset();
				
				// Clear HTTP request object
				HttpRequest& httpreq = conn->getHttpRequest();
				httpreq = HttpRequest(); // Reset to empty
				
				// Clear any leftover read buffer data
				conn->clearReadBuffer();
				conn->resetForNewRequest();
				
				Logger::debug("Server::processWriteEvent Connection (fd " + Utils::toString(fd) + ") reset for next request");
				
				// Monitor for reads only
				loop_->modifySocket(fd, conn, EVENTMASK_READ);
			} else {
				Logger::debug("Server::processWriteEvent Response sent, closing connection (fd " + Utils::toString(fd) + ")");
				conn->setState(CLOSING);
				// conn->close();
				loop_->removeSocket(fd);
				// conn_pool_->removeConnection(fd);
			}
		}
	}
	// If hasDataToWrite() is still true, keep monitoring for writes
	// The event loop will call us again when the socket is writable
}


// -----------------------------------------------------------------------------
// processErrorEvent: cleanup both client and listening sockets
// -----------------------------------------------------------------------------
void Server::processErrorEvent(int fd, Connection* conn) {
	if (conn) {
		Logger::error("Server::processErrorEvent Error on client fd=" + Utils::toString(fd));
		conn->setState(CLOSING);
		loop_->removeSocket(fd);
		// conn_pool_->removeConnection(fd);
	} else {
		Logger::error("Server::processErrorEvent Error on listening socket fd=" + Utils::toString(fd));
		for (size_t i = 0; i < listen_sockets_.size(); ++i) {
			if (listen_sockets_[i].fd == fd) {
				Socket::close(listen_sockets_[i].fd);
				listen_sockets_[i].fd = -1;
				Logger::warn("Server::processErrorEvent Listening socket closed due to error, will recreate on reload");
				break;
			}
		}
	}
}

// -----------------------------------------------------------------------------
// acceptNewConnection - FIXED: No errno usage, subject compliant
// -----------------------------------------------------------------------------
void Server::acceptNewConnection(SocketInfo& sock) {
	int accept_count = 0;
	const int MAX_ACCEPTS_PER_LOOP = DEFAULT_MAX_ACCEPTS_PER_LOOP;
	
	// Find the server config for this listening socket
	const ServerConfig* server_cfg = NULL;
	for (size_t i = 0; i < config_.getGlobalConfig().http.servers.size(); ++i) {
		const ServerConfig& cfg = config_.getGlobalConfig().http.servers[i];
		if (cfg.host == sock.host && cfg.port == sock.port) {
			server_cfg = &cfg;
			break;
		}
	}
	
	// Fallback to first server if no match found
	if (!server_cfg && !config_.getGlobalConfig().http.servers.empty()) {
		server_cfg = &config_.getGlobalConfig().http.servers[0];
	}
	
	while (accept_count < MAX_ACCEPTS_PER_LOOP) {
		std::string client_ip;
		int client_port;
		int client_fd = Socket::accept(sock.fd, client_ip, client_port);
		
		if (client_fd < 0) {
			Logger::debug("Server::acceptNewConnection Accept returned " + Utils::toString(client_fd) +
						" on listening fd=" + Utils::toString(sock.fd));
			break;
		}
		
		Logger::debug("Server::acceptNewConnection Accepted new client " + client_ip + ":" + Utils::toString(client_port) +
					" on fd=" + Utils::toString(client_fd));
		
		// Set non-blocking
		if (!Socket::setNonBlocking(client_fd)) {
			Logger::error("Server::acceptNewConnection Failed to set client fd=" + Utils::toString(client_fd) + " non-blocking");
			Socket::close(client_fd);
			continue;
		}
		
		// Create connection object
		Connection* conn = new Connection(client_fd, client_ip, client_port);
		if (!conn) {
			Logger::error("Server::acceptNewConnection Failed to allocate Connection object for fd=" + Utils::toString(client_fd));
			Socket::close(client_fd);
			continue;
		}
		
		// NEW: Apply timeout from config (convert seconds to milliseconds)
		if (server_cfg && server_cfg->client_header_timeout > 0) {
			int timeout_ms = server_cfg->client_header_timeout * 1000;
			conn->setTimeout(timeout_ms);
			Logger::debug("Server::acceptNewConnection Set connection timeout to " + 
						Utils::toString(server_cfg->client_header_timeout) + " seconds for fd=" + 
						Utils::toString(client_fd));
		}
		
		conn->setState(READING_REQUEST);
		
		// Add to connection pool
		if (!conn_pool_->addConnection(conn)) {
			Logger::warn("Server::acceptNewConnection Connection pool full, rejecting client " + client_ip + ":" +
						Utils::toString(client_port));
			delete conn;
			continue;
		}
		
		// Register client fd in event loop (read-only initially)
		if (!loop_->addSocket(client_fd, conn, EVENTMASK_READ)) {
			Logger::error("Server::acceptNewConnection Failed to add client fd=" + Utils::toString(client_fd) + " to EventLoop");
			conn_pool_->removeConnection(client_fd);
			continue;
		}
		
		accept_count++;
	}
	
	if (accept_count > 0) {
		Logger::debug("Server::acceptNewConnection Accepted " + Utils::toString(accept_count) +
					" new connections on listening fd=" + Utils::toString(sock.fd));
	}
}


// -----------------------------------------------------------------------------
// createListeningSockets - FIXED: Uses setReuseAddr, subject compliant
// -----------------------------------------------------------------------------
bool Server::createListeningSockets() {
	for (size_t i = 0; i < listen_sockets_.size(); ++i) {
		SocketInfo& sock = listen_sockets_[i];

		int fd = Socket::create();
		if (fd < 0) {
			Logger::error("Server::createListeningSockets Failed to create listening socket");
			return false;
		}

		if (!Socket::setReuseAddr(fd, true)) {
			Logger::error("Server::createListeningSockets Failed to set SO_REUSEADDR on fd=" + Utils::toString(fd));
			Socket::close(fd);
			return false;
		}

		if (!Socket::setNonBlocking(fd)) {
			Logger::error("Server::createListeningSockets Failed to set non-blocking on fd=" + Utils::toString(fd));
			Socket::close(fd);
			return false;
		}

		if (!Socket::bind(fd, sock.host, sock.port)) {
			Logger::error("Server::createListeningSockets Failed to bind listening socket to " + sock.host + ":" +
						Utils::toString(sock.port));
			Socket::close(fd);
			return false;
		}

		if (!Socket::listen(fd, sock.backlog)) {
			Logger::error("Server::createListeningSockets Failed to listen on fd=" + Utils::toString(fd));
			Socket::close(fd);
			return false;
		}

		sock.fd = fd;
		sock.created_at = std::time(NULL);

		// Add to event loop (NULL = listening socket)
		if (!loop_->addSocket(fd, NULL, EVENTMASK_READ)) {
			Logger::error("Server::createListeningSockets Failed to register listening fd=" + Utils::toString(fd) + " in EventLoop");
			Socket::close(fd);
			return false;
		}

		Logger::info("Server::createListeningSockets Listening on " + (sock.host.empty() ? "0.0.0.0" : sock.host) +
					":" + Utils::toString(sock.port));
	}

	return true;
}

// -----------------------------------------------------------------------------
// closeListeningSockets - Close all listening sockets
// -----------------------------------------------------------------------------
void Server::closeListeningSockets() {
	for (size_t i = 0; i < listen_sockets_.size(); ++i) {
		SocketInfo& sock = listen_sockets_[i];
		if (sock.fd > 0) {
			loop_->removeSocket(sock.fd);
			Socket::close(sock.fd);
			sock.fd = -1;
		}
	}
	Logger::info("Server::closeListeningSockets All listening sockets closed");
}

void Server::checkConnectionTimeouts() {
	if (!conn_pool_) return;
	
	std::vector<Connection*> connections = conn_pool_->getAllConnections();
	
	for (size_t i = 0; i < connections.size(); ++i) {
		Connection* conn = connections[i];
		if (!conn) continue;
		
		int fd = conn->getFd();
		ConnectionState state = conn->getState();
		
		if (state == WRITING_RESPONSE || state == CLOSING || state == CLOSED) {
			continue;
		}
		
		if (state != READING_REQUEST && state != WAITING_FOR_CGI) {
			continue;
		}
		
		if (!conn->isTimedOut()) {
			continue;
		}
		
		Logger::warn("Connection timed out on fd=" + Utils::toString(fd));
		
		if (state == READING_REQUEST) {
			Logger::debug("TIMEOUT CHECK: fd=" + Utils::toString(fd) + 
                 ", has_received_data=" + Utils::toString(conn->getInfo().has_received_data));
			// Only send 408 if data was received
			if (conn->getInfo().has_received_data) {
				Logger::debug("Sending 408 Request Timeout for fd=" + Utils::toString(fd));
				
				const ServerConfig* srv = NULL;
				HttpRequest& httpreq = conn->getHttpRequest();
				
				if (!httpreq.host.empty()) {
					srv = config_.findServer(httpreq.host, conn->getInfo().server_port);
				}
				if (!srv && !config_.getGlobalConfig().http.servers.empty()) {
					srv = &config_.getGlobalConfig().http.servers[0];
				}
				
				if (srv) {
					Response timeoutResp = ErrorHandler::buildErrorResponse(408, *srv);
					timeoutResp.setHeader("Connection", "close");
					conn->setKeepAlive(false);
					
					conn->writeData(timeoutResp.toString());
					conn->setState(WRITING_RESPONSE);
					loop_->modifySocket(fd, conn, EVENTMASK_READ | EVENTMASK_WRITE);
				} else {
					conn->setState(CLOSING);
					loop_->removeSocket(fd);
				}
			} else {
				// Silent close for idle connections (like nginx)
				Logger::debug("Silent timeout for fd=" + Utils::toString(fd) + " (no data received)");
				conn->setState(CLOSING);
				loop_->removeSocket(fd);
			}
		} else if (state == WAITING_FOR_CGI) {
			Logger::debug("CGI timeout on fd=" + Utils::toString(fd) + " - closing connection");
			conn->setState(CLOSING);
			loop_->removeSocket(fd);
		}
	}
}


// -----------------------------------------------------------------------------
// start - UPDATED: Handle CGI waiting states
// -----------------------------------------------------------------------------
bool Server::start() {
	if (!loop_ || !conn_pool_) {
		Logger::error("Server::start EventLoop or ConnectionPool not initialized");
		return false;
	}

	// Create and bind listening sockets
	if (!createListeningSockets()) {
		Logger::error("Server::start Failed to create listening sockets");
		return false;
	}

	Logger::info("Server::start Server starting main event loop...");

	while (!(shutdown_flag_ && *shutdown_flag_)) {
		// Run one iteration of the event loop
		std::vector<Event> events = loop_->pollEvents();

		// ========== Check for CGI completions on every iteration ==========
		cgi_.checkAllProcesses();
		processCGICompletions();

		checkConnectionTimeouts();

		for (size_t i = 0; i < events.size(); ++i) {
			Event& ev = events[i];
			Connection* conn = ev.conn;

			switch (ev.type) {
				case EVENT_HUP:
					processHangupEvent(ev.fd, ev.conn);
					break;
				case EVENT_READ:
					processReadEvent(ev.fd, conn);
					break;
				case EVENT_WRITE:
					processWriteEvent(ev.fd, conn);
					break;
				case EVENT_ERROR:
					processErrorEvent(ev.fd, conn);
					break;
				case EVENT_TIMEOUT:
					break;
				default:
					Logger::warn("Unknown event type on fd=" + Utils::toString(ev.fd));
					break;
			}
		}

		conn_pool_->cleanupClosed();

		// Handle configuration reload if requested
		if (reload_flag_ && *reload_flag_) {
			*reload_flag_ = 0;
			Logger::info("Reload flag detected, reloading configuration...");
			
			if (!reloadConfig()) {
				Logger::error("Failed to reload configuration");
			}
		}
	}

	Logger::info("Server shutting down...");
	cleanupResources();
	closeListeningSockets();
	return true;
}

// -----------------------------------------------------------------------------
// stop - Stop server gracefully
// -----------------------------------------------------------------------------
void Server::stop() {
	if (shutdown_flag_)
		*shutdown_flag_ = 1;
	if (loop_)
		loop_->stop();
	Logger::info("Server stop requested");
}

// -----------------------------------------------------------------------------
// cleanupResources - Clean up all resources
// -----------------------------------------------------------------------------
void Server::cleanupResources() {
	if (conn_pool_) {
		conn_pool_->closeAll();
		Logger::info("All connections cleaned up");
	}
}

// -----------------------------------------------------------------------------
// gracefulShutdownConnections - Close connections gracefully
// -----------------------------------------------------------------------------
void Server::gracefulShutdownConnections() {
	if (conn_pool_) {
		std::vector<Connection*> connections = conn_pool_->getAllConnections();
		for (size_t i = 0; i < connections.size(); ++i) {
			connections[i]->setState(CLOSING);
		}
		
		// Give connections a moment to close gracefully
		usleep(100000); // 100ms
		Logger::info("Connections set to graceful shutdown");
	}
}

// -----------------------------------------------------------------------------
// updateConnectionSettings - Update connection settings from config
// -----------------------------------------------------------------------------
void Server::updateConnectionSettings() {
	// This can be expanded to update per-connection settings if needed
	// For now, it's a placeholder for future enhancements
	Logger::debug("Connection settings updated from configuration");
}

// -----------------------------------------------------------------------------
// rollbackConfig - Rollback to previous configuration
// -----------------------------------------------------------------------------
bool Server::rollbackConfig(const Config& old_config) {
	Logger::warn("Rolling back to previous configuration...");

	// Restore old config
	config_ = old_config;

	// Rebuild sockets list from old config
	updateListeningSocketsFromConfig();

	// Close any sockets left from the failed reload
	closeListeningSockets();

	// Try to recreate sockets for old config
	if (!createListeningSockets()) {
		Logger::error("Rollback failed: could not restore old configuration");
		// At this point, server cannot recover — must shut down
		stop();
		return false;
	}

	Logger::info("Rollback successful, old configuration restored.");
	return true;
}

// -----------------------------------------------------------------------------
// reloadConfig - Reload server configuration
// -----------------------------------------------------------------------------
bool Server::reloadConfig() {
	Logger::info("Reloading configuration...");

	Config old_config = config_;  // Save old Config object
	Config new_config;
	
	if (!new_config.load(config_file_)) {
		Logger::warn("Config reload failed - keeping existing configuration");
		return false;
	}
	
	config_ = new_config;  // Swap to new config
	
	gracefulShutdownConnections();
	closeListeningSockets();
	updateListeningSocketsFromConfig();

	if (!createListeningSockets()) {
		Logger::error("Failed to create new listening sockets during reload");
		if (!rollbackConfig(old_config)) {
			Logger::error("CRITICAL: Rollback failed, server shutting down!");
			// Server will shut down via stop() called in rollbackConfig
		}
		return false;
	}

	Logger::info("Configuration reloaded successfully");
	return true;
}

void Server::processCGICompletions() {
	std::vector<std::pair<int, CGIResponse> > completed = cgi_.getCompletedProcesses();
	
	for (size_t i = 0; i < completed.size(); ++i) {
		int client_fd = completed[i].first;
		CGIResponse& cgi_resp = completed[i].second;
		
		Connection* conn = conn_pool_->getConnection(client_fd);
		if (conn && conn->getState() == WAITING_FOR_CGI) {
			Logger::debug("Server::processCGICompletions - CGI completed for fd=" + Utils::toString(client_fd) +
						" status=" + Utils::toString(cgi_resp.http_status));
			
			Response http_resp;
			
			// ========== USE ERRORHANDLER FOR ERRORS ==========
			if (cgi_resp.timed_out || !cgi_resp.success) {
				// Get the original HttpRequest from connection
				HttpRequest& http_req = conn->getHttpRequest();
				
				// Wrap it in a Request object
				Request req(http_req);
				
				// Find server and location config
				const ServerConfig* srv = config_.findServer(req.getHost(), req.getPort());
				if (!srv && !config_.getGlobalConfig().http.servers.empty()) {
					srv = &config_.getGlobalConfig().http.servers[0];
				}
				const Location* loc = srv ? config_.findLocation(*srv, req.getUri()) : NULL;
				
				// Build context for ErrorHandler
				HandlerContext ctx = { req, *srv, loc, conn, &cgi_ };
				
				// Call ErrorHandler with appropriate status code
				if (cgi_resp.timed_out) {
					Logger::warn("Server::processCGICompletions - CGI timed out for fd=" + Utils::toString(client_fd));
					http_resp = ErrorHandler(504).handle(ctx);
				} else {
					Logger::warn("Server::processCGICompletions - CGI execution failed for fd=" + Utils::toString(client_fd) +
								" with status=" + Utils::toString(cgi_resp.http_status));
					http_resp = ErrorHandler(cgi_resp.http_status).handle(ctx);
				}
				
			} else {
				// SUCCESS - Return actual CGI output
				Logger::debug("Server::processCGICompletions - CGI succeeded for fd=" + Utils::toString(client_fd));
				http_resp.setStatus(cgi_resp.http_status);
				
				// Copy headers from CGI response
				for (std::map<std::string, std::string>::const_iterator it = cgi_resp.headers.begin();
					it != cgi_resp.headers.end(); ++it) {
					http_resp.setHeader(it->first, it->second);
				}
				
				// Set body
				http_resp.setBody(cgi_resp.body);
			}
			// =================================================
			
			// Send response back to client
			conn->writeData(http_resp.toString());
			conn->setState(WRITING_RESPONSE);
			
			// Monitor for write completion
			loop_->modifySocket(client_fd, conn, EVENTMASK_READ | EVENTMASK_WRITE);
			
		} else if (conn) {
			Logger::warn("Server::processCGICompletions - CGI completed but connection fd=" + Utils::toString(client_fd) +
						" is in wrong state: " + Utils::toString(conn->getState()));
		} else {
			Logger::warn("Server::processCGICompletions - No connection found for completed CGI fd=" + Utils::toString(client_fd));
		}
	}
}


void Server::processHangupEvent(int fd, Connection* conn) {
	if (!conn) return;
	Logger::debug("Client disconnected (hangup) on fd=" + Utils::toString(fd));
	conn->setState(CLOSING);
	loop_->removeSocket(fd);
}

