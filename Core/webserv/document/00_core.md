# Web Server Project - 00_core Module Documentation

## Overview

The `00_core/` module forms the **foundation of the webserver**, providing all low-level networking infrastructure, connection lifecycle management, and the main event loop. It handles multiplexing I/O operations using **epoll**, manages client connections, ensures graceful startup/shutdown, and integrates **asynchronous CGI execution**.

**Design Philosophy**: Robust, efficient event-driven architecture using **epoll** for superior scalability, with proper non-blocking I/O, comprehensive error recovery, and explicit resource management.

---

## Module Structure

```
00_core/
├── Server.hpp/cpp              # Main server orchestrator
├── EventLoop.hpp/cpp           # **epoll**-based event multiplexer
├── Connection.hpp/cpp          # Individual client connection (with CGI states)
├── ConnectionPool.hpp/cpp      # Connection collection manager
├── Socket.hpp/cpp              # Low-level socket operations
└── NonBlockingIO.hpp/cpp       # Poll-compliant I/O wrappers
```

---

## Core Responsibilities

| Responsibility | Description |
|----------------|-------------|
| **Socket Management** | Create, bind, listen on sockets with `SO_REUSEADDR` |
| **Connection Handling** | Accept clients, manage lifecycle states (including CGI wait) |
| **Event Multiplexing** | Monitor file descriptors using **epoll** |
| **Event Dispatching** | Route read/write/error/hangup/timeout events to handlers |
| **Non-blocking I/O** | Perform partial reads/writes without blocking |
| **Timeout Enforcement** | **Per-phase timeouts**: header timeout, body timeout, silent idle close |
| **CGI Integration** | Manage asynchronous CGI execution states |
| **Resource Management** | Prevent leaks, handle graceful shutdown |
| **Configuration Reload** | Update settings without stopping server (with rollback safety) |

---

## Key Data Structures

### ConnectionState

Enumerates the distinct lifecycle stages of a client connection, including specialized states for CGI execution.

```cpp
enum ConnectionState {
    CONNECTING,       // Accepted but not yet ready
    READING_REQUEST,  // Receiving HTTP request
    PROCESSING,       // Handler processing request
    WAITING_FOR_CGI,  // **NEW: Waiting for CGI process completion**
    WRITING_RESPONSE, // Sending HTTP response
    CLOSING,          // Gracefully closing
    CLOSED            // Fully terminated
};
```

**State Transition Diagram**:

```
CONNECTING
    ↓
READING_REQUEST ←─────┐
    ↓                 │
PROCESSING            │
    ↓                 │ (keep-alive)
WAITING_FOR_CGI → WRITING_RESPONSE
    ↓                 │
    └─────────────────┘
          ↓
       CLOSING
          ↓
       CLOSED
```

**Validation**: Invalid transitions are rejected with warnings and logged.

### ConnectionInfo

Comprehensive metadata structure capturing all connection-related information for monitoring and management.

```cpp
struct ConnectionInfo {
    int fd;                    // Socket file descriptor
    std::string client_ip;     // Remote IP address
    int client_port;           // Remote port number
    std::string server_name;   // Virtual host name
    int server_port;           // Server port
    ConnectionState state;     // Current lifecycle state
    size_t bytes_read;         // Total bytes received
    size_t bytes_written;      // Total bytes sent
    time_t created_at;         // Creation timestamp (ms)
    time_t last_activity;      // Last I/O timestamp (ms)
    int timeout_ms;            // Idle timeout (default: 60000ms)
    bool has_received_data;    // **NEW: Whether any data was received (for timeout logic)**
};
```

### Event

Represents a single I/O event returned by the event loop to the server for processing.

```cpp
struct Event {
    int fd;                    // File descriptor that triggered the event
    EventType type;            // Type of event
    Connection* conn;          // Associated connection (NULL for listening sockets)
    time_t timestamp;          // When event occurred
};

enum EventType {
    EVENT_READ,      // Data available for reading
    EVENT_WRITE,     // Socket ready for writing
    EVENT_ERROR,     // Socket error occurred
    EVENT_TIMEOUT,   // Connection idle timeout
    EVENT_HUP        // **NEW: Connection hangup detected**
};
```

### EventMask

Bitmask specifying which I/O events to monitor for a file descriptor during epoll registration.

```cpp
enum EventMask {
    EVENTMASK_READ  = 1 << 0,  // Monitor for read readiness (EPOLLIN)
    EVENTMASK_WRITE = 1 << 1   // Monitor for write readiness (EPOLLOUT)
};
```

### SocketInfo

Metadata structure describing a listening socket created from server configuration.

```cpp
struct SocketInfo {
    int fd;                    // Listening file descriptor
    std::string host;          // Bound IP address (or empty for INADDR_ANY)
    int port;                  // Bound port number
    int backlog;               // Listen queue size (default: 128)
    time_t created_at;         // Socket creation timestamp

    // Constructor
    SocketInfo();
};
```

---

## Component Details

### Server (Main Orchestrator)

**Purpose**: Central coordinator managing the entire server lifecycle, configuration, CGI integration, and event processing.

**Key Responsibilities**:
- Create/manage listening sockets from configuration (with **deduplication**)
- Run main event loop with graceful shutdown support
- Route events to appropriate processing handlers
- Integrate HTTP parsing, handlers, **and async CGI**
- Support dynamic configuration reload with **rollback capability**
- Manage keep-alive connections with **HTTP version awareness**
- **Per-phase timeout enforcement** (header vs body)

**Public Interface**:

```cpp
class Server {
public:
    // Constructor: Loads configuration and initializes components
    explicit Server(const std::string& config_file);
    
    // Destructor: Cleanup resources, close all connections
    ~Server();

    // Start the main event loop (blocking until shutdown)
    bool start();
    
    // Request graceful shutdown
    void stop();
    
    // **CGI completion processor** - handles async CGI results
    void processCGICompletions();
    
    // Reload configuration from file with rollback on failure
    bool reloadConfig();
    
    // Create and bind all listening sockets from config
    bool createListeningSockets();
    
    // Close all listening sockets
    void closeListeningSockets();

    // Set signal flag pointer for graceful shutdown (SIGTERM/SIGINT)
    void setShutdownFlag(volatile sig_atomic_t* flag);
    
    // Set signal flag pointer for config reload (SIGHUP)
    void setReloadFlag(volatile sig_atomic_t* flag);

private:
    // Update internal socket list from loaded config (**deduplicates host:port**)
    void updateListeningSocketsFromConfig();
    
    // Handle read event: accept clients, parse requests, **validate content length**
    void processReadEvent(int fd, Connection* conn);
    
    // Handle write event: send response data, **reset for keep-alive**
    void processWriteEvent(int fd, Connection* conn);
    
    // Handle error event: close connection or listening socket
    void processErrorEvent(int fd, Connection* conn);
    
    // **Handle hangup event: client disconnected**
    void processHangupEvent(int fd, Connection* conn);
    
    // Accept pending connections on a listening socket
    void acceptNewConnection(SocketInfo& sock);
    
    // Check for timed-out connections (per-phase timeouts)
    void checkConnectionTimeouts();
    
    // Close all client connections and free resources
    void cleanupResources();
    
    // Set all connections to CLOSING state for graceful shutdown
    void gracefulShutdownConnections();
    
    // Apply updated connection settings from config
    void updateConnectionSettings();
    
    // Restore previous config if reload fails
    bool rollbackConfig(const Config& old_config);

    // Prevent copying
    Server(const Server&);
    Server& operator=(const Server&);

    // Members
    EventLoop* loop_;
    ConnectionPool* conn_pool_;
    std::vector<SocketInfo> listen_sockets_;
    volatile sig_atomic_t* shutdown_flag_;
    volatile sig_atomic_t* reload_flag_;
    std::string config_file_;
    CGI cgi_;                     // **NEW: CGI manager for async execution**
    Config config_;
};
```

**Request Processing Flow with CGI**:

```
1. Client connects → accept() → new Connection → READING_REQUEST

2. Data arrives (EVENT_READ) → readData() → RequestParser.parse()

3. Parse complete → PROCESSING → Handler::createHandler()

4. If CGI handler:
   - Spawns CGI process
   - Sets state: WAITING_FOR_CGI
   - **Returns immediately without sending response**

5. Main loop continues polling → cgi_.checkAllProcesses()

6. CGI completion detected → processCGICompletions()
   - Builds Response from CGI output or error
   - Sets state: WRITING_RESPONSE
   - Writes response to client

7. EVENT_WRITE → flushWriteBuffer() → Response sent
```

**Enhanced Timeout Logic**:

```
For each connection:
    ↓
If state is READING_REQUEST:
    If no data received yet:
        **Silent timeout**: close without 408 (like nginx)
    Else:
        Send 408 Request Timeout response
        ↓
        Set Connection: close header
        ↓
        Transition to WRITING_RESPONSE → CLOSING

If state is WAITING_FOR_CGI:
    **Use CGI-specific timeout (client_body_timeout)**
    ↓
    On timeout: close immediately
```

**Configuration Reload with Rollback**:

```
1. SIGHUP → reload_flag = 1
2. Save old_config = config_
3. Load new_config from file
4. If load fails:
   - Log warning
   - Return false (keep old config)
5. config_ = new_config
6. Graceful shutdown connections
7. Close old listening sockets
8. Create new listening sockets
9. If socket creation fails:
   - Log error
   - rollbackConfig(old_config)
   - **If rollback fails: stop() server**
10. Return success
```

---

### EventLoop (epoll Event Multiplexer)

**Purpose**: Monitor file descriptors using **epoll** for efficient event detection at scale.

**Why epoll?**
- **Superior Performance**: O(1) per operation vs O(n) for select()
- **Scalability**: Handles thousands of connections efficiently
- **Edge-triggered Support**: Available for future optimizations
- **No fd_set Limitations**: Not limited by FD_SETSIZE

**Public Interface**:

```cpp
class EventLoop {
public:
    // Constructor: Initialize event loop with max connection capacity
    explicit EventLoop(size_t max_connections = 1024);
    
    // Destructor: Stop loop and cleanup epoll fd
    ~EventLoop();

    // Register a socket for event monitoring
    // events: bitmask of EVENTMASK_READ | EVENTMASK_WRITE
    // conn: NULL for listening sockets, Connection* for clients
    bool addSocket(int fd, Connection* conn, int events);
    
    // Modify event mask for an existing socket
    bool modifySocket(int fd, Connection* conn, int events);
    
    // Unregister a socket from monitoring
    bool removeSocket(int fd);

    // Poll for events (blocks until events or timeout)
    // Returns vector of Event objects
    std::vector<Event> pollEvents();
    
    // Request event loop to stop
    void stop();
    
    // Check if event loop is running
    bool isRunning() const;
    
    // Get number of monitored sockets
    size_t getConnectionCount() const;

    // Set epoll_wait() timeout in milliseconds
    void setTimeout(int ms);
    
    // Set maximum events to return per iteration
    void setMaxEvents(int n);
    
    // Set external stop flag pointer (for signal handling)
    void setStopFlag(volatile sig_atomic_t* flag);

private:
    struct SocketEntry {
        Connection* conn;
        int events;  // Internal event mask (EVENTMASK_READ | EVENTMASK_WRITE)
        
        // Constructor
        SocketEntry() : conn(NULL), events(0) {}
    };

    // **epoll file descriptor**
    int epoll_fd_;
    bool running_;
    int timeout_ms_;
    int max_events_;
    volatile sig_atomic_t* stop_flag_;
    std::map<int, SocketEntry> sockets_;

    // Run one iteration of event loop
    std::vector<Event> runOnce();
    
    // Check all connections for timeout and add timeout events
    void checkTimeouts(std::vector<Event>& events);
    
    // Remove closed connections from monitoring
    void cleanupClosedConnections();
    
    // **Convert internal mask to epoll flags**
    int eventMaskToEpoll(int mask);

    // Prevent copying
    EventLoop(const EventLoop&);
    EventLoop& operator=(const EventLoop&);
};
```

**Event Detection Flow with epoll**:

```
pollEvents() called
    ↓
Allocate epoll_events array
    ↓
epoll_wait(epoll_fd, epoll_events, max_events, timeout_ms)
    ↓
Cases:
    - nready < 0: Error, log and return empty
    - nready = 0: Timeout, checkTimeouts() → cleanup
    - nready > 0: Process ready file descriptors
    ↓
For each epoll_event:
    - Extract fd and epoll_ev (bitmask)
    - Look up SocketEntry in sockets_ map
    - **Check EPOLLHUP first** (highest priority)
    - **Check EPOLLIN** → EVENT_READ
    - **Check EPOLLOUT** → EVENT_WRITE
    - **Add timeout events** from checkTimeouts()
    ↓
cleanupClosedConnections()
    ↓
Return vector of Event objects
```

**epoll Event Flags**:

```
Internal Mask    →    epoll Flags
EVENTMASK_READ   →    EPOLLIN | EPOLLERR | EPOLLHUP
EVENTMASK_WRITE  →    EPOLLOUT | EPOLLERR | EPOLLHUP
```

**No Busy Waiting**:
- `epoll_wait()` blocks efficiently
- Returns only when events occur or timeout expires
- **Native kernel scaling** for large connection counts

---

### Connection (Client State Manager)

**Purpose**: Represent a single client connection with full lifecycle management, HTTP parsing, **CGI state tracking**, and **sophisticated timeout logic**.

**Key Features**:
- State machine with **7 validated transitions** (including CGI)
- Millisecond-precision activity tracking
- Integrated HTTP request parser with **reset capability**
- Keep-alive support with **HTTP version awareness**
- **Per-phase timeout support** (header vs body)
- Buffer management for partial I/O
- **Received-data tracking** for silent timeout logic

**Public Interface**:

```cpp
class Connection {
public:
    // Constructor: Create connection with client info
    Connection(int fd, const std::string& ip, int port);
    
    // Destructor: Close socket and cleanup
    ~Connection();

    // Get reference to HTTP request parser
    RequestParser& getParser();
    
    // Get reference to parsed HTTP request
    HttpRequest& getHttpRequest();
    
    // Reset parser state for next request (keep-alive)
    void resetParserState();

    // Set connection state with validation
    void setState(ConnectionState state);
    
    // Get current connection state
    ConnectionState getState() const;

    // **CGI state management**
    void setCGIWaiting(bool waiting);
    bool isWaitingForCGI() const;

    // Set keep-alive flag (based on HTTP headers)
    void setKeepAlive(bool keep_alive);
    
    // Check if connection should be kept alive
    bool getKeepAlive() const;

    // Update last activity timestamp to current time
    void updateActivity();
    
    // Check if connection has exceeded idle timeout
    bool isTimedOut() const;
    
    // Set idle timeout in milliseconds
    void setTimeout(int milliseconds);

    // Perform single non-blocking read, append to read buffer
    // Returns: bytes read, 0 for EOF, -1 for error/would-block
    ssize_t readData();
    
    // Append data to write buffer and attempt single write
    // Returns: bytes written, -1 for error
    ssize_t writeData(const std::string& data);
    
    // Attempt to write pending data in write buffer
    // Returns: bytes written, -1 for error
    ssize_t flushWriteBuffer();

    // Get reference to read buffer (for parser)
    const std::string& getReadBuffer() const;
    
    // Clear both read and write buffers
    void clearBuffers();
    
    // Clear only read buffer
    void clearReadBuffer();
    
    // Remove specified bytes from read buffer (after parsing)
    void consumeReadBuffer(size_t bytes);
    
    // Check if write buffer has pending data
    bool hasDataToWrite() const;

    // **Reset connection for next keep-alive request**
    void resetForNewRequest();

    // Check if connection is valid (fd >= 0 and not CLOSED)
    bool isValid() const;
    
    // Check if connection is closed
    bool isClosed() const;
    
    // Close connection and free resources
    void close();

    // Get socket file descriptor
    int getFd() const;
    
    // Get connection metadata
    const ConnectionInfo& getInfo() const;
    
    // Get formatted status string for logging
    std::string getStatusString() const;
    
    // Get connection age in milliseconds
    time_t getAge() const;
    
    // Get idle time in milliseconds
    time_t getIdleTime() const;

    // **Get current time in milliseconds**
    static time_t now_ms();

private:
    ConnectionInfo info_;
    std::string read_buf_;
    std::string write_buf_;
    bool keep_alive_;
    RequestParser parser_;     // Incremental parser
    HttpRequest http_req_;     // Parsed request data

    // Prevent copying
    Connection(const Connection&);
    Connection& operator=(const Connection&);
};
```

**CGI State Management**:

```cpp
// While CGI is executing:
conn->setCGIWaiting(true);   // PROCESSING → WAITING_FOR_CGI
    ↓
// Activity timer NOT updated (passive waiting)
    ↓
// CGI completes:
conn->setCGIWaiting(false);  // WAITING_FOR_CGI → WRITING_RESPONSE
```

**Timeout Detection Logic**:

```cpp
// In isTimedOut():
time_t current_time = now_ms();
time_t elapsed = current_time - info_.last_activity;
bool timed_out = elapsed > static_cast<time_t>(info_.timeout_ms);

// Special handling in checkConnectionTimeouts():
if (!conn->getInfo().has_received_data) {
    // **Silent timeout**: no data received at all
    conn->setState(CLOSING);
    // **NO 408 response sent** (like nginx)
} else {
    // Data was received but request incomplete
    // Send 408 Request Timeout
}
```

**Buffer Management**:

**Read Buffer**:
- Accumulates incoming data from socket
- Parser consumes data incrementally via `parse()`
- `getBytesConsumed()` tracks processed bytes
- `consumeReadBuffer()` removes processed data
- `clearReadBuffer()` resets between keep-alive requests
- Partial data preserved for next read event

**Write Buffer**:
- Accumulates outgoing response data
- `writeData()` attempts transmission, handles partial writes
- Remaining data stays buffered for subsequent write events
- Buffer cleared only when fully transmitted
- `hasDataToWrite()` checks for pending data

**Poll-Compliant I/O**:
- `readData()`: Single non-blocking read, returns bytes read
- `writeData()`: Single non-blocking write, returns bytes written
- `flushWriteBuffer()`: Attempt to write pending data
- **Never blocks**, always returns immediately

**Keep-Alive Reset Sequence**:

```
After response fully sent and keep-alive true:
    ↓
conn->setState(READING_REQUEST);
    ↓
conn->updateActivity();
    ↓
conn->getParser().reset();
    ↓
conn->getHttpRequest() = HttpRequest();  // Reset
    ↓
conn->clearReadBuffer();
    ↓
conn->resetForNewRequest();
    ↓
loop_->modifySocket(fd, conn, EVENTMASK_READ);  // Monitor reads only
```

---

### ConnectionPool (Connection Manager)

**Purpose**: Centralized container for all active client connections with explicit memory ownership and **CGI-aware cleanup**.

**Memory Management Strategy**:

The pool owns all Connection pointers and is responsible for their lifecycle:

```
Connection created → Pool takes ownership
    ↓
Stored in map: fd → Connection*
    ↓
Connection used during its lifetime (including CGI wait)
    ↓
Connection no longer needed (CLOSED or CLOSING)
    ↓
removeConnection(fd) called
    ↓
delete Connection (calls ~Connection, closes fd)
    ↓
Remove from map
```

**Public Interface**:

```cpp
class ConnectionPool {
public:
    // Constructor: Create pool with maximum capacity
    ConnectionPool(size_t max = 1024);
    
    // Destructor: Close all connections and free memory
    ~ConnectionPool();

    // Add connection to pool (takes ownership)
    // Returns false if pool full or connection already exists
    bool addConnection(Connection* conn);

    // Remove and delete connection by file descriptor
    // Returns false if connection not found
    bool removeConnection(int fd);

    // Get connection by file descriptor
    // Returns NULL if not found
    Connection* getConnection(int fd);

    // Get all connections as vector (for iteration)
    std::vector<Connection*> getAllConnections() const;

    // Remove connections in CLOSED or **CLOSING** state (memory-safe)
    void cleanupClosed();

    // Close and delete all connections (graceful shutdown)
    void closeAll();

    // Get current number of active connections
    size_t size() const;

    // Get maximum allowed connections
    size_t getMaxConnections() const;

    // Get number of available connection slots
    size_t getAvailableSlots() const;

private:
    std::map<int, Connection*> pool_; // map fd → Connection*
    size_t max_;                       // maximum allowed connections

    // Prevent copying
    ConnectionPool(const ConnectionPool&);
    ConnectionPool& operator=(const ConnectionPool&);
};
```

**Key Operations**:

**Add Connection**:
- Validates connection is not null
- Checks pool not at capacity
- Ensures fd not already registered
- **Applies per-server timeout from config**

**Remove Connection**:
- Finds connection by fd
- **Deletes Connection object** (automatic fd close)
- Removes from map
- Returns success/failure

**Cleanup Closed**:
- Two-phase process to prevent iterator invalidation
- Phase 1: Collect all **CLOSED or CLOSING** connection fds
- Phase 2: Remove each one safely
- Logs number of connections cleaned

**Close All**:
- Three-phase safe shutdown:
  1. Collect all Connection pointers
  2. Clear map first (prevents double-deletion)
  3. Delete all collected connections

**Resource Tracking**:
- `size()`: Current active connection count
- `getMaxConnections()`: Maximum allowed
- `getAvailableSlots()`: Remaining capacity

**Connection Limit Enforcement**:
```
Max connections: 1024 (default)

On new connection:
    If size() >= max:
        Reject connection
        Log warning
    Else:
        Accept connection
        Add to pool
        Apply timeout from matched server config
```

---

### Socket (Low-Level Operations)

**Purpose**: Provide low-level socket primitives with proper error handling and **strict subject compliance** (no errno usage).

**Subject Compliance**:
- **No errno usage**: All error checking via return values only
- **Non-blocking by default**: All client sockets set to O_NONBLOCK
- **SO_REUSEADDR**: Enabled for all listening sockets

**Public Interface**:

```cpp
// SocketInfo: metadata for a listening socket
struct SocketInfo {
    int fd;                    // Listening file descriptor
    std::string host;          // Bound IP address
    int port;                  // Bound port number
    int backlog;               // Listen queue size
    time_t created_at;         // Creation timestamp

    // Constructor (declaration only - no implementation in header)
    SocketInfo();
};

// Socket: low-level socket abstraction
class Socket {
public:
    // Create a new TCP socket (AF_INET, SOCK_STREAM)
    // Returns: socket fd, or -1 on error
    static int create();
    
    // Set socket to non-blocking mode using fcntl
    // Returns: true on success, false on failure
    static bool setNonBlocking(int fd);
    
    // Enable/disable SO_REUSEADDR socket option
    // Returns: true on success, false on failure
    static bool setReuseAddr(int fd, bool reuse = true);

    // Bind socket to host:port
    // host: IP address or empty for INADDR_ANY
    // Returns: true on success, false on failure
    static bool bind(int fd, const std::string& host, int port);
    
    // Start listening for incoming connections
    // backlog: size of pending connection queue
    // Returns: true on success, false on failure
    static bool listen(int fd, int backlog);
    
    // Accept a new connection (non-blocking)
    // ip: filled with client IP address
    // port: filled with client port number
    // Returns: client fd on success, -1 if no pending connections or error
    static int accept(int fd, std::string& ip, int& port);

    // Close a socket safely (checks fd >= 0)
    static void close(int fd);

private:
    // Prevent instantiation - all methods are static
    Socket();
    Socket(const Socket&);
    Socket& operator=(const Socket&);
};
```

**Socket Creation Flow**:

```
create()
    ↓
socket(AF_INET, SOCK_STREAM, 0)
    ↓
Return fd (negative on error)

Listening Socket Setup:
    ↓
setReuseAddr(fd, true)
    ↓
setNonBlocking(fd)
    ↓
bind(fd, host, port)
    ↓
listen(fd, backlog)
    ↓
Add to EventLoop with EVENTMASK_READ

Client Socket Setup:
    ↓
accept(listening_fd) → client_fd (may be -1)
    ↓
if client_fd >= 0:
    setNonBlocking(client_fd)
```

**Non-Blocking Configuration**:
- Get current flags: `fcntl(fd, F_GETFL, 0)`
- Set non-blocking: `fcntl(fd, F_SETFL, flags | O_NONBLOCK)`
- **Critical for epoll operation**

**SO_REUSEADDR Benefits**:
- Allows immediate rebind after server restart
- Prevents "Address already in use" errors
- Critical for development and testing

**Accept Without errno**:
```
client_fd = accept(listening_fd, &addr, &addrlen)

If client_fd >= 0:
    Success - extract client info via inet_ntop()
    Return client_fd
Else:
    -1 (no pending connections or error)
    Don't check errno per subject requirements
    Let caller handle (break accept loop)
```

---

### NonBlockingIO (I/O Wrappers)

**Purpose**: Provide poll-compliant single-operation I/O primitives that **never block**.

**Design Principle**: **Subject requirement**: Never perform I/O without prior poll/epoll notification.

**Public Interface**:

```cpp
class NonBlockingIO {
public:
    // Perform single non-blocking read into string buffer
    // Reads at most 4096 bytes and appends to 'out'
    // Returns: bytes read (>0), 0 for EOF, -1 for would-block/error
    static ssize_t readOnce(int fd, std::string& out);

    // Perform single non-blocking write from string buffer
    // Writes at most in.size() bytes from 'in'
    // Returns: bytes written (>0), 0 if would block
    static ssize_t writeOnce(const std::string& in);

private:
    // Prevent instantiation - utility class
    NonBlockingIO();
    NonBlockingIO(const NonBlockingIO&);
    NonBlockingIO& operator=(const NonBlockingIO&);
};
```

**Read Operation**:

```
readOnce(fd, out_string)
    ↓
Allocate 4KB buffer on stack (char buffer[4096])
    ↓
Call read(fd, buffer, sizeof(buffer))
    ↓
Cases:
    n > 0:  Append buffer[0..n] to out_string, return n
    n == 0: EOF detected, return 0
    n < 0:  EAGAIN/EWOULDBLOCK or error, return n
```

**Write Operation**:

```
writeOnce(fd, in_string)
    ↓
If string empty: return 0
    ↓
Call write(fd, in.c_str(), in.size())
    ↓
Cases:
    n > 0:  n bytes written, return n
    n <= 0: Would block or error, return 0
```

**Buffer Size**:
- **4096 bytes** chosen as optimal balance
- Matches typical page size
- Reduces system call overhead
- Prevents excessive memory usage

**Single Operation Guarantee**:
- Each call performs **exactly one** read/write syscall
- Partial operations handled by caller (Server/Connection)
- **Guaranteed non-blocking** when used with epoll

---

## Request Processing Flow

### Complete Connection Lifecycle

```
1. Listening Socket Event
   ↓
   Server::processReadEvent(fd, NULL) [conn is NULL]
   ↓
   acceptNewConnection() called
   ↓
   Socket::accept() returns client_fd
   ↓
   Socket::setNonBlocking(client_fd)
   ↓
   Create new Connection object
   ↓
   Apply timeout from matched server config via setTimeout()
   ↓
   conn_pool_->addConnection() validates capacity via getAvailableSlots()
   ↓
   loop_->addSocket(client_fd, conn, EVENTMASK_READ)
   ↓
   Connection state: READING_REQUEST

2. Client Data Arrives
   ↓
   Server::processReadEvent(fd, conn)
   ↓
   conn->readData() → Append to read buffer
   ↓
   RequestParser::parse() processes data incrementally
   ↓
   If parse complete → conn->setState(PROCESSING)
   ↓
   Handler creates response or spawns CGI process via HandlerContext
   ↓
   If CGI → conn->setCGIWaiting(true) → WAITING_FOR_CGI
   ↓
   If standard → conn->writeData(response) → WRITING_RESPONSE

3. CGI Execution (Async)
   ↓
   Main loop continues: loop_->pollEvents() via runOnce()
   ↓
   cgi_.checkAllProcesses() detects completion
   ↓
   processCGICompletions() matches fd to Connection via getConnection()
   ↓
   Builds Response from CGIResponse or ErrorHandler
   ↓
   conn->writeData(cgi_output) → WRITING_RESPONSE

4. Response Sending
   ↓
   Server::processWriteEvent(fd, conn)
   ↓
   conn->flushWriteBuffer() sends data incrementally
   ↓
   When buffer empty (hasDataToWrite() == false):
        IF getKeepAlive() == true:
            resetParserState() and resetForNewRequest()
            conn->setState(READING_REQUEST)
            loop_->modifySocket(fd, EVENTMASK_READ)
        ELSE:
            conn->setState(CLOSING)
            loop_->removeSocket(fd)
            // cleanupClosed() will call removeConnection()

5. Timeout or Error
   ↓
   checkConnectionTimeouts() detects idle connection via isTimedOut()
   ↓
   Creates EVENT_TIMEOUT entry with timestamp
   ↓
   Server processes timeout (silent close or 408 via ErrorHandler)
   ↓
   OR: processErrorEvent()/processHangupEvent() triggers immediate CLOSING

6. Cleanup
   ↓
   EventLoop::cleanupClosedConnections() runs
   ↓
   Identifies connections where !isValid() or getState() == CLOSING
   ↓
   conn_pool_->removeConnection(fd) → deletes Connection via delete
   ↓
   loop_->removeSocket(fd) removes from epoll via epoll_ctl(EPOLL_CTL_DEL)
   ↓
   Connection destructor closes fd via ::close(), memory freed
```

---

## Configuration Integration

### Server Block Matching by Host:Port

**Process**:
```
Request arrives with Host: example.com:8080
    ↓
Extract hostname and port from HttpRequest.host/http_req.port
    ↓
Search configuration for exact server_name match on port 8080 via config_.findServer()
    ↓
IF found: Use matching ServerConfig pointer
IF not found: Use first server block as default
    ↓
Extract location-specific settings from Location* loc:
    - client_header_timeout, client_body_timeout
    - client_max_body_size
    - Path resolution settings (root, index_files)
    - CGI configuration (cgi_enable, cgi_extensions, cgi_interpreters)
    - Upload configuration (upload_enable, upload_dir)
    - Error pages mapping (error_pages map)
    - Access control (deny_all, denied_ips, return, redirect_url)
```

### Dynamic Configuration Reload

**Reload Sequence**:
```
SIGHUP signal received → reload_flag = 1
    ↓
Main loop detects flag on next iteration in start()
    ↓
reloadConfig() triggered
    ↓
Save old_config = config_ (deep copy object via operator=)
    ↓
new_config.load(config_file_) with validation
    ↓
IF load fails:
    Logger::warn("Reload failed - keeping existing configuration")
    Return false (keep old config)
    ↓
config_ = new_config
    ↓
gracefulShutdownConnections() → Set all to CLOSING via setState()
    ↓
usleep(100000) // 100ms grace period for writes to complete
    ↓
closeListeningSockets()
    ↓
updateListeningSocketsFromConfig() [deduplicates host:port pairs]
    ↓
createListeningSockets()
    ↓
IF socket creation fails:
    Logger::error("Failed to create new listening sockets during reload")
    rollback_result = rollbackConfig(old_config)
    ↓
    IF rollback_result == false:
        Logger::critical("CRITICAL: Rollback failed, server shutting down!")
        stop()
    ↓
    Return false
    ↓
Logger::info("Configuration reloaded successfully")
Return true
```

---

## Error Handling

### Graceful Degradation

**Socket Creation Failure**:
- Logger::error with specific failure reason (bind, listen, etc.)
- Continue initializing remaining sockets
- Server runs on subset of configured ports
- No crash, partial service maintained

**Accept Failure** (-1 return):
- **No errno checking** per subject requirements
- Logger::debug records return value
- Assumes EAGAIN/EWOULDBLOCK (no pending connections)
- Breaks accept loop immediately
- Returns to event loop, will retry on next EVENT_READ

**Client I/O Errors** (readData() or writeData() returns negative):
- Logger::error with fd and connection state context
- Connection::setState(CLOSING) called
- EventLoop::removeSocket(fd) removes from epoll
- ConnectionPool::cleanupClosed() deletes Connection object
- Other connections in pool unaffected, continue processing

**Connection Hangup** (EVENT_HUP):
- epoll detects EPOLLHUP during runOnce()
- Server::processHangupEvent() logs "Client disconnected (hangup)"
- Connection::setState(CLOSING) marks for cleanup
- No further I/O attempted on hung-up socket
- cleanupClosedConnections() handles resource release

### HTTP-Level Error Responses

**400 Bad Request** (Parser ERROR state):
- RequestParser enters ERROR state with error_message set
- Server::processReadEvent() detects state == ERROR
- ErrorHandler::buildErrorResponse(400, *srv) creates response
- Response includes error details from parser.getError()
- Connection: close header set automatically by ErrorHandler
- conn->writeData() sends response
- Connection marked CLOSING, parser reset via resetParserState()

**413 Payload Too Large** (Content-Length exceeds limit):
- Validated in processReadEvent() before body reading
- http_req.content_length compared to srv->client_max_body_size
- **Immediate rejection** prevents resource waste
- ErrorHandler::buildErrorResponse(413, *srv) creates response
- res.setHeader("Connection", "close")
- conn->setKeepAlive(false)
- conn->writeData() sends response immediately
- State set to WRITING_RESPONSE

**408 Request Timeout** (Idle timeout):
- **Conditional behavior** based on has_received_data flag
- If data received: ErrorHandler(408) creates response with Connection: close
- If no data: Silent close (no response) - Logger::debug only
- Distinguishes slow clients from port scanners (nginx behavior)

**504 Gateway Timeout** (CGI execution timeout):
- Detected in processCGICompletions() when cgi_resp.timed_out == true
- Original HandlerContext reconstructed from Connection's HttpRequest
- ErrorHandler(504) creates response with proper server context
- Connection closed after sending

**Configuration Errors**:
- Load failure: Logger::warn, returns false, old config retained
- Socket creation failure: Logger::error, triggers rollback
- Rollback failure: Logger::critical, calls stop(), server exits gracefully

---

## Integration with Other Modules

### With 01_config/

**Configuration Delivery**:
- `Config` object (config_) provides server and location matching
- `ServerConfig` supplies timeout values (client_header_timeout, client_body_timeout)
- `Location` blocks provide path-specific settings:
  - upload_enable, upload_dir
  - cgi_enable, cgi_extensions, cgi_interpreters
  - allowed_methods, deny_all, denied_ips
  - return, redirect_url for immediate responses
- `error_pages` mapping used by ErrorHandler for custom pages
- `listen_sockets_` deduplication uses host:port from all server blocks

**Dynamic Updates**:
- Configuration reload updates config_ object atomically
- Subsequent requests use new settings immediately
- CGI and upload handlers re-read location config per request
- Timeout values applied to new connections via setTimeout()

### With 02_http/

**Request Parsing**:
- `RequestParser` processes data from Connection's read buffer incrementally
- `ParseState` returned determines next action (PARSING_*, COMPLETE, ERROR)
- Parser's `getBytesConsumed()` enables safe buffer cleanup via `consumeReadBuffer()`
- `HttpRequest` struct populated by parser, accessed via `getHttpRequest()`
- Connection calls `resetParserState()` after each complete request for keep-alive reuse

**Response Generation**:
- `Response` objects built by handlers or ErrorHandler
- `toString()` converts to wire format for `writeData()`
- Keep-alive logic uses `getKeepAlive()` to determine connection persistence
- HTTP version detection (HTTP/1.0 vs HTTP/1.1) drives keep-alive defaults

**Protocol Handling**:
- `shouldKeepAlive()` determines persistence from version and Connection header
- Content-Length validation prevents excessive memory usage
- Chunked transfer encoding handled transparently in parser via `PARSING_CHUNKED_BODY`

### With 03_handlers/

**Handler Creation**:
- `Handler::createHandler(HandlerContext& ctx)` receives context with Connection pointer
- Context provides access to config, location, request via ctx.req, and CGI manager via ctx.cgi
- Connection state updates (WAITING_FOR_CGI) happen within handler handle() execution
- resolved_path stored in Request object via setResolvedPath() for consistency

**Path Resolution**:
- Handler calls `Handler::resolvePath()` static utility with ctx
- Resolved path stored in Request via `setResolvedPath()`
- Connection provides client addressing via getInfo().client_ip for access control logging
- Path validation prevents directory traversal attacks via isPathSafe()

**Response Sending**:
- Handlers call `conn->writeData(response_string)` to stage response
- Connection state set to WRITING_RESPONSE before handler returns
- Keep-alive reset handled by Server in processWriteEvent() after full transmission

### With 04_cgi/

**Async Execution**:
- `CGIHandler` spawns process via `ctx.cgi->executeNonBlocking()`
- Connection set to WAITING_FOR_CGI state via setCGIWaiting(true)
- CGI manager tracks process independently of connection state

**Completion Detection**:
- `Server::start()` calls `cgi_.checkAllProcesses()` each loop iteration
- Completed processes retrieved via `cgi_.getCompletedProcesses()` returning vector<pair<int, CGIResponse>>
- `Server::processCGICompletions()` matches client_fd to Connection via `conn_pool_->getConnection()`

**Response Handling**:
- `CGIResponse` contains stdout, status_code, headers, timed_out flag
- SUCCESS: Build Response from CGI output with setBody() and setStatus()
- TIMEOUT: ErrorHandler(504) with HandlerContext from original request
- FAILURE: ErrorHandler with CGI status code
- Final response sent via `conn->writeData()` and state set to WRITING_RESPONSE

### With 06_utils/

**Logger Integration**:
- **Extensive debug logging** throughout event loop and connection lifecycle
- State transitions logged with old→new state and fd via Logger::debug
- I/O operations log byte counts and error conditions
- Timeout events log idle duration via Logger::warn
- Configuration reload logged with success/failure details via Logger::info/error/warn/critical

**Utils Helpers**:
- `Utils::toString()` converts numeric values for logging strings
- Time utilities provide millisecond precision for activity tracking via timeval
- String utilities used for header manipulation and path operations in resolvePath()

**Error Message Generation**:
ErrorHandler uses `HttpUtils::getStatusMessage()` for default error page generation, ensuring consistent status reason phrases across the application.

---

## Key Design Decisions

### Why epoll Over select()?

**Decision**: Migrated from select() to epoll for superior scalability.

**Rationale**:
- **Performance**: O(1) per operation vs O(n) for large connection counts
- **Scalability**: Handles thousands of concurrent connections efficiently
- **No Hard Limits**: Not constrained by FD_SETSIZE (1024)
- **Modern Standard**: Well-supported on Linux, industry standard
- **Future-Proof**: Edge-triggered mode available for optimizations

**Trade-off**: Linux-specific, but acceptable for project scope.

### Why WAITING_FOR_CGI State?

**Decision**: Added explicit state for asynchronous CGI execution.

**Rationale**:
- **Non-blocking**: Server remains responsive during CGI execution
- **Timeout Control**: Different timeout policies for passive waiting
- **State Visibility**: Clear separation from active processing
- **Error Handling**: Distinct timeout and error paths
- **Resource Efficiency**: No threads blocked, no busy-waiting

**Implementation**: Activity timer not updated during CGI wait, main loop checks CGI completions each iteration via checkAllProcesses().

### Why Silent Timeout for Idle Connections?

**Decision**: Close connections that never send data without HTTP response.

**Rationale**:
- **Security**: Prevents revealing server presence to port scanners
- **Efficiency**: Saves bandwidth on clearly dead connections
- **Best Practice**: Mimics nginx behavior in production
- **Standards**: RFC doesn't mandate 408 for truly idle connections

**Implementation**: `has_received_data` flag in ConnectionInfo tracks reception, silent close when false.

### Why Two-Phase Cleanup Everywhere?

**Decision**: Always collect items first, then remove/delete in separate phase.

**Rationale**:
- **Iterator Safety**: Prevents invalidation during iteration
- **Consistency**: Same pattern across ConnectionPool, EventLoop, CGI manager
- **Predictability**: Easier to reason about cleanup timing
- **Correctness**: Avoids subtle use-after-free bugs

**Pattern Applied**: `cleanupClosed()` collects file descriptors first, then removes them in separate loop.

### Why Raw Pointers in ConnectionPool?

**Decision**: Use raw pointers with explicit ownership (C++98 compatibility).

**Rationale**:
- **C++98 Compliance**: No unique_ptr available
- **Clear Ownership**: Pool explicitly owns via new/delete
- **Memory Safety**: Two-phase deletion prevents issues
- **Explicit Control**: Deletion timing controlled and predictable
- **RAII**: Destructors ensure cleanup in all paths

**Safety Measures**: No copying allowed (private copy constructor/assignment), explicit deletion only through removeConnection().

### Why Per-Phase Timeouts?

**Decision**: Different timeouts for headers, body, and CGI phases.

**Rationale**:
- **Real-world Needs**: Headers should arrive quickly, uploads can be slow
- **Security**: Prevents slowloris attacks on request line parsing
- **Flexibility**: CGI timeout separate from client data timeout
- **Nginx Compatibility**: Industry-standard timeout policies

**Implementation**: Connection stores timeout_ms but Server applies different defaults based on parser state and location config from client_header_timeout/client_body_timeout.

---

## Summary

The `00_core/` module provides a **production-ready, scalable foundation** for the webserver:

✅ **Event-driven architecture** using **epoll** for superior concurrent performance  
✅ **Robust connection management** with 7-state validated lifecycle  
✅ **Async CGI integration** with explicit WAITING_FOR_CGI state  
✅ **Sophisticated timeout logic**: per-phase, silent idle close, proper 408 responses  
✅ **Memory-safe resource handling** with explicit ownership and two-phase cleanup  
✅ **Dynamic configuration reload** with automatic rollback on failure  
✅ **HTTP/1.1 integration** via parser and keep-alive connection reuse  
✅ **Poll-compliant I/O** for guaranteed non-blocking operations  
✅ **Comprehensive error handling**: 400, 408, 413, 504 responses  
✅ **Security features**: Timeout protection, size limits, path validation  

**Integration Excellence**:
- Seamless coordination with HTTP parsing layer (RequestParser integration)
- Direct configuration system integration with deduplication
- Clean handler interface for business logic isolation (HandlerContext)
- Efficient CGI module coordination for dynamic content (processCGICompletions)
- Comprehensive logging via Logger for monitoring/debugging

**Production Features**:
- Graceful shutdown capability via stop() and gracefulShutdownConnections()
- Signal handling (SIGTERM, SIGHUP) for reload and termination
- Resource leak prevention via RAII patterns in destructors
- Scalable to thousands of concurrent connections via epoll
- Standards-compliant HTTP behavior with keep-alive
- Industry-compatible timeout policies (silent idle close, per-phase timeouts)

This core infrastructure enables higher-level modules to focus on application logic while relying on a **stable, efficient, and well-tested networking foundation**.