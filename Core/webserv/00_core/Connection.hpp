#ifndef WEBSERV_00_CORE_CONNECTION_HPP
#define WEBSERV_00_CORE_CONNECTION_HPP

#include <string>
#include <unistd.h>       // for ssize_t
#include <sys/time.h>     // for gettimeofday
#include "NonBlockingIO.hpp"
#include "02_http/RequestParser.hpp"
#include "02_http/Request.hpp"

// -----------------------------------------------------------------------------
// Connection State
// -----------------------------------------------------------------------------
enum ConnectionState {
	CONNECTING,       // Accepted but not yet ready
	READING_REQUEST,  // Waiting for complete request
	PROCESSING,       // Request being handled
	WAITING_FOR_CGI,  // Waiting for CGI execution
	WRITING_RESPONSE, // Sending response to client
	CLOSING,          // Closing gracefully
	CLOSED            // Fully closed
};

// -----------------------------------------------------------------------------
// Connection Info
// -----------------------------------------------------------------------------
struct ConnectionInfo {
	int fd;                    // Socket FD
	std::string client_ip;     // Remote IP
	int client_port;           // Remote port
	std::string server_name;   // Virtual host
	int server_port;           // Port this connection belongs to
	ConnectionState state;     // Current state
	size_t bytes_read;         // Accumulated input
	size_t bytes_written;      // Accumulated output
	time_t created_at;         // Creation time in ms
	time_t last_activity;      // Last I/O time in ms
	int timeout_ms;            // Configured timeout in ms
	bool has_received_data;    // Whether any data has been received
};

// -----------------------------------------------------------------------------
// Connection Class
// -----------------------------------------------------------------------------
// Represents a single client connection. Manages state, buffers, I/O, timeouts,
// and request parsing. All I/O is poll-compliant and goes through NonBlockingIO.
// -----------------------------------------------------------------------------
class Connection {
public:
	Connection(int fd, const std::string& ip, int port);
	~Connection();

	// Request parsing
	RequestParser& getParser();
	HttpRequest&   getHttpRequest();
	void resetParserState();

	// State management
	void setState(ConnectionState state);
	ConnectionState getState() const;

	// Keep-alive
	void setKeepAlive(bool keep_alive);
	bool getKeepAlive() const;

	// Activity / timeout
	void updateActivity();
	bool isTimedOut() const;
	void setTimeout(int milliseconds);

	// I/O
	ssize_t readData();                   // poll-compliant single read
	ssize_t writeData(const std::string& data); // poll-compliant single write
	ssize_t flushWriteBuffer();           // flush pending writes

	// Buffers
	const std::string& getReadBuffer() const;
	void clearBuffers();
	void clearReadBuffer();
	void consumeReadBuffer(size_t bytes);
	bool hasDataToWrite() const;
	void resetForNewRequest();

	// Lifecycle
	bool isValid() const;
	bool isClosed() const;
	void close();

	// Info
	int getFd() const;
	const ConnectionInfo& getInfo() const;
	std::string getStatusString() const;

	time_t getAge() const;
	time_t getIdleTime() const;

	// CGI state management
	void setCGIWaiting(bool waiting);
	bool isWaitingForCGI() const;
	
	// Helpers
	static time_t now_ms();
	
private:
	ConnectionInfo info_;
	std::string read_buf_;
	std::string write_buf_;
	bool keep_alive_;

	RequestParser parser_;   // per-connection incremental parser
	HttpRequest   http_req_; // parsed data target


	// Prevent copying
	Connection(const Connection&);
	Connection& operator=(const Connection&);
};

#endif // WEBSERV_00_CORE_CONNECTION_HPP
