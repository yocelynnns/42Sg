#include "Connection.hpp"
#include "06_utils/Logger.hpp"
#include "06_utils/Utils.hpp"
#include <unistd.h>  // for ::close

// -----------------------------------------------------------------------------
// Utility: current time in ms (C++98 compatible)
// -----------------------------------------------------------------------------
time_t Connection::now_ms() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return static_cast<time_t>(tv.tv_sec) * 1000 + tv.tv_usec / 1000;
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------
Connection::Connection(int fd, const std::string& ip, int port) {
	info_.fd = fd;
	info_.client_ip = ip;
	info_.client_port = port;
	info_.state = CONNECTING;
	info_.bytes_read = 0;
	info_.bytes_written = 0;
	info_.created_at = now_ms();
	info_.last_activity = info_.created_at;
	info_.server_name = "";
	info_.server_port = port;
	info_.timeout_ms = 60000;  // 60 seconds default
	info_.has_received_data = false;

	keep_alive_ = true; // HTTP/1.1 default

	Logger::debug("Connection created: fd " + Utils::toString(fd) +
				" from " + ip + ":" + Utils::toString(port));
}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
Connection::~Connection() {
	close();
	Logger::debug("Connection destroyed: fd " + Utils::toString(info_.fd));
}

// -----------------------------------------------------------------------------
// Keep-alive management
// -----------------------------------------------------------------------------
void Connection::setKeepAlive(bool keep_alive) {
	keep_alive_ = keep_alive;
	Logger::debug("Connection fd " + Utils::toString(info_.fd) +
				" keep-alive set to " + (keep_alive ? "true" : "false"));
}

bool Connection::getKeepAlive() const {
	return keep_alive_;
}

// -----------------------------------------------------------------------------
// State management - validate transitions
// -----------------------------------------------------------------------------
void Connection::setState(ConnectionState new_state) {
	bool valid_transition = false;

	if (info_.state == new_state) {
		Logger::debug("Redundant state transition to " + Utils::toString(new_state) + 
					" on fd " + Utils::toString(info_.fd));
		return;  // Skip the rest of the logic
	}

	switch (info_.state) {
		case CONNECTING:
			valid_transition = (new_state == READING_REQUEST || new_state == CLOSING);
			break;
		case READING_REQUEST:
			valid_transition = (new_state == PROCESSING || 
							new_state == WRITING_RESPONSE ||
							new_state == CLOSING);
			break;
		case PROCESSING:
			valid_transition = (new_state == WRITING_RESPONSE || 
							new_state == WAITING_FOR_CGI || 
							new_state == CLOSING);
			break;
		case WAITING_FOR_CGI:
			valid_transition = (new_state == WRITING_RESPONSE || new_state == CLOSING);
			break;
		case WRITING_RESPONSE:
			valid_transition = (new_state == READING_REQUEST || new_state == CLOSING);
			break;
		case CLOSING:
			valid_transition = (new_state == CLOSED);
			break;
		case CLOSED:
			valid_transition = false;
			break;
	}

	if (!valid_transition) {
		Logger::warn("Invalid state transition from " + Utils::toString(info_.state) +
					" to " + Utils::toString(new_state) + " on fd " + Utils::toString(info_.fd));
		return;
	}

	// Update activity for active states (except WAITING_FOR_CGI which is passive waiting)
	if (new_state == READING_REQUEST || 
		new_state == PROCESSING || 
		new_state == WRITING_RESPONSE) {
		updateActivity();
	}
	
	Logger::debug("Connection fd " + Utils::toString(info_.fd) +
				" state: " + Utils::toString(info_.state) +
				" -> " + Utils::toString(new_state));
	info_.state = new_state;
}

// -----------------------------------------------------------------------------
// CGI State Management
// -----------------------------------------------------------------------------
bool Connection::isWaitingForCGI() const {
	return info_.state == WAITING_FOR_CGI;
}

void Connection::setCGIWaiting(bool waiting) {
	if (waiting && info_.state == PROCESSING) {
		setState(WAITING_FOR_CGI);
	} else if (!waiting && info_.state == WAITING_FOR_CGI) {
		setState(WRITING_RESPONSE);
	}
}

ConnectionState Connection::getState() const {
	return info_.state;
}

// -----------------------------------------------------------------------------
// Activity / timeout
// -----------------------------------------------------------------------------
void Connection::updateActivity() {
	info_.last_activity = now_ms();
}

bool Connection::isTimedOut() const {
	time_t current_time = now_ms();
	time_t elapsed = current_time - info_.last_activity;
	bool timed_out = elapsed > static_cast<time_t>(info_.timeout_ms);

	if (timed_out) {
		Logger::warn("Connection fd " + Utils::toString(info_.fd) +
					" timed out after " + Utils::toString(elapsed) + " ms");
	}
	return timed_out;
}

void Connection::setTimeout(int milliseconds) {
	if (milliseconds > 0) {
		info_.timeout_ms = milliseconds;
		Logger::debug("Connection fd " + Utils::toString(info_.fd) +
					" timeout set to " + Utils::toString(milliseconds) + " ms");
	}
}

// -----------------------------------------------------------------------------
// Read data - POLL COMPLIANT
// -----------------------------------------------------------------------------
ssize_t Connection::readData() {
	ssize_t n = NonBlockingIO::readOnce(info_.fd, read_buf_);
	if (n > 0) {
		info_.bytes_read += n;
		info_.has_received_data = true;
		Logger::debug("READ DATA: has_received_data = TRUE for fd=" + Utils::toString(info_.fd));
		updateActivity();
		Logger::debug("Connection fd " + Utils::toString(info_.fd) +
					" read " + Utils::toString(n) + " bytes");
	} else if (n == 0) {
		Logger::debug("EOF on fd " + Utils::toString(info_.fd));
		setState(CLOSING);
	} else {
		Logger::debug("Read returned " + Utils::toString(n) +
					" on fd " + Utils::toString(info_.fd));
	}
	return n;
}

// -----------------------------------------------------------------------------
// Write data - POLL COMPLIANT
// -----------------------------------------------------------------------------
ssize_t Connection::writeData(const std::string& data) {
	if (!data.empty()) write_buf_ += data;

	if (write_buf_.empty()) return 0;

	ssize_t n = NonBlockingIO::writeOnce(info_.fd, write_buf_);
	if (n > 0) {
		info_.bytes_written += n;
		updateActivity();
		Logger::debug("Connection fd " + Utils::toString(info_.fd) +
					" wrote " + Utils::toString(n) + " bytes");

		if ((size_t)n >= write_buf_.size()) {
			write_buf_.clear();
		} else {
			write_buf_ = write_buf_.substr(n);
		}
	} else if (n < 0) {
		Logger::error("Write error on fd " + Utils::toString(info_.fd));
		// setState(CLOSING);
		// Don't set state here - let caller (processWriteEvent) handle cleanup
	}
	return n;
}

ssize_t Connection::flushWriteBuffer() {
	return writeData("");
}

// -----------------------------------------------------------------------------
// Buffer management
// -----------------------------------------------------------------------------
const std::string& Connection::getReadBuffer() const {
	return read_buf_;
}

void Connection::clearBuffers() {
	read_buf_.clear();
	write_buf_.clear();
	Logger::debug("Cleared buffers for fd " + Utils::toString(info_.fd));
}

void Connection::clearReadBuffer() {
	read_buf_.clear();
	Logger::debug("Cleared read buffer for fd " + Utils::toString(info_.fd));
}

void Connection::resetForNewRequest() {
    info_.has_received_data = false;
    Logger::debug("Connection reset for new request on fd " + Utils::toString(info_.fd));
}

void Connection::consumeReadBuffer(size_t bytes) {
	if (bytes >= read_buf_.size()) {
		read_buf_.clear();
	} else {
		read_buf_ = read_buf_.substr(bytes);
	}
	Logger::debug("Consumed " + Utils::toString(bytes) +
				" bytes from read buffer, fd " + Utils::toString(info_.fd));
}

bool Connection::hasDataToWrite() const {
	return !write_buf_.empty();
}

// -----------------------------------------------------------------------------
// Lifecycle
// -----------------------------------------------------------------------------
bool Connection::isValid() const {
	return info_.fd >= 0 && info_.state != CLOSED;
}

bool Connection::isClosed() const {
	return info_.state == CLOSED || info_.fd < 0;
}

void Connection::close() {
	if (info_.fd >= 0) {
		Logger::debug("Closing connection fd " + Utils::toString(info_.fd));
		::close(info_.fd);
		info_.fd = -1;
	}
	if (info_.state != CLOSED) {
		setState(CLOSED);
	}
	read_buf_.clear();
	write_buf_.clear();
}

// -----------------------------------------------------------------------------
// Info and debugging
// -----------------------------------------------------------------------------
int Connection::getFd() const {
	return info_.fd;
}

const ConnectionInfo& Connection::getInfo() const {
	return info_;
}

std::string Connection::getStatusString() const {
	std::string status = "Connection fd=" + Utils::toString(info_.fd);
	status += " state=" + Utils::toString(info_.state);
	status += " bytes_read=" + Utils::toString(info_.bytes_read);
	status += " bytes_written=" + Utils::toString(info_.bytes_written);
	status += " read_buf_size=" + Utils::toString(read_buf_.size());
	status += " write_buf_size=" + Utils::toString(write_buf_.size());
	status += " keep_alive=" + std::string(keep_alive_ ? "true" : "false");

	time_t age = now_ms() - info_.created_at;
	status += " age=" + Utils::toString(age) + "ms";

	time_t idle = now_ms() - info_.last_activity;
	status += " idle=" + Utils::toString(idle) + "ms";

	return status;
}

time_t Connection::getAge() const {
	return now_ms() - info_.created_at;
}

time_t Connection::getIdleTime() const {
	return now_ms() - info_.last_activity;
}

// -----------------------------------------------------------------------------
// Parser access
// -----------------------------------------------------------------------------
RequestParser& Connection::getParser() {
	return parser_;
}

HttpRequest& Connection::getHttpRequest() {
	return http_req_;
}

void Connection::resetParserState() {
	parser_.reset();
	http_req_ = HttpRequest();
	Logger::debug("Reset parser state for fd " + Utils::toString(info_.fd));
}
