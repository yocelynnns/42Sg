# Webserv Project - Complete Data Structures Reference

## Overview
Comprehensive data structure reference matching the actual implementation across all modules. This document serves as a single source of truth for all types, enums, structs, and classes.

---

## 1. Core Networking Structures (00_core/)

### Connection Lifecycle
```cpp
enum ConnectionState {
    CONNECTING,       // Accepted but not yet ready
    READING_REQUEST,  // Receiving HTTP request  
    PROCESSING,       // Handler processing request
    WAITING_FOR_CGI,  // Waiting for CGI process completion
    WRITING_RESPONSE, // Sending HTTP response
    CLOSING,          // Gracefully closing
    CLOSED            // Fully terminated
};
```

### Connection Management
```cpp
struct ConnectionInfo {
    int fd;                    // Socket file descriptor
    std::string client_ip;     // Remote IP address
    int client_port;           // Remote port number
    std::string server_name;   // Virtual host name
    int server_port;           // Server port number
    ConnectionState state;     // Current lifecycle state
    size_t bytes_read;         // Total bytes received
    size_t bytes_written;      // Total bytes sent
    time_t created_at;         // Creation timestamp (ms)
    time_t last_activity;      // Last I/O timestamp (ms)
    int timeout_ms;            // Idle timeout (default: 60000ms)
    bool has_received_data;    // Whether any data has been received
};
```

```cpp
class Connection {
private:
    ConnectionInfo info_;
    std::string read_buf_;
    std::string write_buf_;
    bool keep_alive_;
    RequestParser parser_;
    HttpRequest http_req_;

public:
    // Request parsing
    RequestParser& getParser();
    HttpRequest&   getHttpRequest();
    void resetParserState();

    // State management
    void setState(ConnectionState state);
    ConnectionState getState() const;

    // CGI state management
    void setCGIWaiting(bool waiting);
    bool isWaitingForCGI() const;

    // Keep-alive
    void setKeepAlive(bool keep_alive);
    bool getKeepAlive() const;

    // Activity / timeout
    void updateActivity();
    bool isTimedOut() const;
    void setTimeout(int milliseconds);

    // I/O
    ssize_t readData();
    ssize_t writeData(const std::string& data);
    ssize_t flushWriteBuffer();

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

    // Static helpers
    static time_t now_ms();
};
```

```cpp
class ConnectionPool {
private:
    std::map<int, Connection*> pool_;
    size_t max_;

public:
    ConnectionPool(size_t max = 1024);
    ~ConnectionPool();

    bool addConnection(Connection* conn);
    bool removeConnection(int fd);
    Connection* getConnection(int fd);
    std::vector<Connection*> getAllConnections() const;
    void cleanupClosed();
    void closeAll();
    size_t size() const;
    size_t getMaxConnections() const;
    size_t getAvailableSlots() const;
};
```

### Event System
```cpp
enum EventType {
    EVENT_READ,      // Data available for reading
    EVENT_WRITE,     // Socket ready for writing
    EVENT_ERROR,     // Socket error occurred
    EVENT_TIMEOUT,   // Connection idle timeout
    EVENT_HUP        // Connection hangup
};

enum EventMask {
    EVENTMASK_READ  = 1 << 0,
    EVENTMASK_WRITE = 1 << 1
};

struct Event {
    int fd;           // File descriptor
    EventType type;   // Type of event
    Connection* conn; // Associated connection
    time_t timestamp; // When event occurred
};

struct SocketEntry {
    Connection* conn;
    int events;
};
```

```cpp
class EventLoop {
private:
    std::map<int, SocketEntry> sockets_;
    int epoll_fd_;
    bool running_;
    int timeout_ms_;
    int max_events_;
    volatile sig_atomic_t* stop_flag_;

public:
    explicit EventLoop(size_t max_connections = 1024);
    ~EventLoop();

    bool addSocket(int fd, Connection* conn, int events);
    bool modifySocket(int fd, Connection* conn, int events);
    bool removeSocket(int fd);
    std::vector<Event> pollEvents();
    void stop();
    bool isRunning() const;
    size_t getConnectionCount() const;

    void setTimeout(int ms);
    void setMaxEvents(int n);
    void setStopFlag(volatile sig_atomic_t* flag);
};
```

### Socket Management
```cpp
struct SocketInfo {
    int fd;              // Listening FD
    std::string host;    // Bound host
    int port;            // Bound port
    int backlog;         // Listen backlog
    time_t created_at;   // Creation time
};
```

```cpp
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
```

### Non-Blocking I/O
```cpp
class NonBlockingIO {
public:
    static ssize_t readOnce(int fd, std::string& out);
    static ssize_t writeOnce(int fd, const std::string& in);
};
```

### Server Orchestrator
```cpp
class Server {
private:
    EventLoop* loop_;
    ConnectionPool* conn_pool_;
    std::vector<SocketInfo> listen_sockets_;
    volatile sig_atomic_t* shutdown_flag_;
    volatile sig_atomic_t* reload_flag_;
    std::string config_file_;
    CGI cgi_;
    Config config_;

public:
    explicit Server(const std::string& config_file);
    ~Server();

    bool start();
    void stop();
    void processCGICompletions();
    bool reloadConfig();

    bool createListeningSockets();
    void closeListeningSockets();
    void setShutdownFlag(volatile sig_atomic_t* flag);
    void setReloadFlag(volatile sig_atomic_t* flag);
};
```

---

## 2. Configuration Structures (01_config/)

### Configuration Hierarchy
```cpp
struct GlobalConfig {
    EventsConfig events;
    HttpConfig http;
    bool has_events;
    bool has_http;
};

struct EventsConfig {
    int connection_timeout;
    size_t max_connections;
    int cgi_timeout;
    int cgi_max_processes;
};

struct HttpConfig {
    std::vector<ServerConfig> servers;
};
```

### Server Configuration
```cpp
struct ServerConfig {
    // Network
    std::string host;
    int port;
    std::vector<std::string> server_names;

    // File serving
    std::string default_root;
    std::vector<std::string> default_index;
    std::string upload_dir;

    // Limits and Timeouts
    size_t client_max_body_size;
    int connection_timeout;
    size_t max_connections;
    int client_header_timeout;
    int client_body_timeout;

    // CGI
    int cgi_timeout;
    int cgi_max_processes;

    // Error handling
    std::map<int, std::string> error_pages;

    // Access Control
    int return_code;
    std::string return_url;
    bool deny_all;
    std::vector<std::string> denied_ips;

    // Session Management
    bool sessions_enabled;
    int session_timeout;
    std::string session_cookie_name;

    // Locations
    std::vector<Location> locations;
};
```

### Location Configuration
```cpp
struct Location {
    // Path matching
    std::string path;

    // File serving
    std::string root;
    std::vector<std::string> index_files;
    bool autoindex;

    // HTTP Methods
    std::vector<std::string> allowed_methods;

    // Uploads
    bool upload_enable;
    std::string upload_dir;

    // CGI
    bool cgi_enable;
    std::vector<std::string> cgi_extensions;
    std::map<std::string, std::string> cgi_interpreters;
    std::string default_cgi_interpreter;
    std::string cgi_path;
    int cgi_timeout;
    int cgi_max_processes;

    // Limits
    size_t client_max_body_size;

    // Access Control and Redirects
    std::string redirect_url;
    int return_code;
    std::string return_url;
    bool deny_all;
    std::vector<std::string> denied_ips;
};
```

### Configuration Management
```cpp
struct Token {
    std::string value;
    int line;
};

class Config {
private:
    GlobalConfig global_config_;

public:
    Config();
    Config(const Config& other);
    Config& operator=(const Config& other);

    bool load(const std::string& filename);
    bool validateConfig() const;
    void setDefaults();

    const std::vector<ServerConfig>& getServers() const;
    const GlobalConfig& getGlobalConfig() const;
    const ServerConfig* findServer(const std::string& host, int port) const;
    const Location* findLocation(const ServerConfig& server, const std::string& path) const;
};

class ConfigParser {
public:
    ConfigParser();
    bool parseFile(const std::string& filename, GlobalConfig& global_config);

private:
    bool parseEventsBlock(std::vector<Token>& tokens, size_t& index, GlobalConfig& global_config);
    bool parseHttpBlock(std::vector<Token>& tokens, size_t& index, HttpConfig& http, GlobalConfig& global_config);
    bool parseServerBlock(std::vector<Token>& tokens, size_t& index, ServerConfig& server);
    bool parseLocationBlock(std::vector<Token>& tokens, size_t& index, Location& location);
    bool parseDirective(const std::vector<Token>& tokens, size_t& index,
                       ServerConfig* server, Location* location, EventsConfig* events);
    std::vector<Token> tokenize(std::istream& input);
    void validateDirective(const std::string& directive,
                          const std::vector<std::string>& values,
                          const std::string& context, int line);
};
```

---

## 3. HTTP Protocol Structures (02_http/)

### HTTP Enums
```cpp
enum HttpMethod { GET, POST, DELETE, HEAD, PUT, OPTIONS, UNKNOWN };
enum HttpVersion { HTTP_1_0, HTTP_1_1, HTTP_UNKNOWN_VERSION };
```

### Request Representation
```cpp
struct HttpRequest {
    // Core request line
    HttpMethod method;
    std::string uri;
    HttpVersion version;

    // Headers and body
    std::map<std::string, std::string> headers;
    std::string body;

    // Parsed metadata
    std::string path;
    bool keep_alive;
    size_t content_length;
    bool is_chunked;

    // Client context
    std::string host;
    int port;
    std::string client_ip;
    int client_port;

    // Path resolution
    std::string resolved_path;
    std::string request_path;

    // Cookies
    std::map<std::string, std::string> cookies;

    HttpRequest();
};

class Request {
private:
    HttpRequest raw;

public:
    explicit Request(const HttpRequest& req);

    HttpMethod getMethod() const;
    const std::string& getPath() const;
    const std::string& getBody() const;
    std::string getCookie(const std::string& name) const;
    std::string getHeader(const std::string& name) const;
    bool hasHeader(const std::string& name) const;
    const std::map<std::string, std::string>& getAllHeaders() const;
    std::string getUri() const;
    std::string getHost() const;
    int getPort() const;
    const std::string& getRemoteAddr() const;
    int getRemotePort() const;
    
    void setReqPath(const std::string& path);
    const std::string& getReqPath() const;
    void setResolvedPath(const std::string& path);
    const std::string& getResolvedPath() const;
    bool hasResolvedPath() const;
    
    std::map<std::string, std::string> parseQueryString() const;
};
```

### Response Representation
```cpp
class Response {
private:
    HttpVersion version;
    int status_code;
    std::string reason_phrase;
    std::map<std::string, std::string> headers;
    std::string body;
    bool headers_sent;
    std::vector<Cookie> cookies_;

public:
    Response();

    void setStatus(int code);
    void setHeader(const std::string& name, const std::string& value);
    void setBody(const std::string& content);
    void setContentType(const std::string& type);
    void setContentLength(size_t length);
    void setKeepAlive(bool status);
    void addDateHeader();
    void addCookie(const Cookie& cookie);
    void clearCookies();

    int getStatus() const;
    const std::string& getReasonPhrase() const;
    const std::string& getHeader(const std::string& name) const;
    bool hasHeader(const std::string& header) const;
    const std::map<std::string, std::string>& getAllHeaders() const;
    const std::string& getBody() const;
    HttpVersion getVersion() const;
    bool isHeadersSent() const;
    const std::vector<Cookie>& getCookies() const;

    std::string toString() const;
};
```

### Request Parser
```cpp
enum ParseState {
    PARSING_REQUEST_LINE,
    PARSING_HEADERS,
    PARSING_BODY,
    PARSING_CHUNKED_BODY,
    COMPLETE,
    ERROR,
    UNKNOWN_VERSION
};

class RequestParser {
private:
    ParseState state;
    size_t content_length;
    size_t bytes_read;
    std::string error_message;
    std::string buffer;
    size_t bytes_consumed_;

public:
    RequestParser();

    ParseState parse(const std::string& data, HttpRequest& request);
    ParseState getState() const;
    std::string getError() const;
    void reset();
    size_t getBytesConsumed() const;
    void resetBytesConsumed();
};
```

### HTTP Utilities
```cpp
class HttpUtils {
public:
    static HttpMethod stringToMethod(const std::string& str);
    static std::string methodToString(HttpMethod method);
    static std::string normalizeHeaderName(const std::string& name);
    static std::string getCurrentDate();
    static std::string getStatusMessage(int status_code);
    static std::string getMimeType(const std::string& extension);
    static std::string urlDecode(const std::string& str);
};
```

---

## 4. Handler System (03_handlers/)

### Handler Context
```cpp
struct HandlerContext {
    Request& req;
    const ServerConfig& config;
    const Location* loc;
    Connection* conn;
    CGI* cgi;
};
```

### Handler Base
```cpp
class Handler {
public:
    virtual ~Handler();
    virtual Response handle(HandlerContext& ctx) = 0;
    
    static Handler* createHandler(HandlerContext& ctx);
    static bool isMethodAllowed(HttpMethod method, const std::vector<std::string>& allowed);
    static std::string resolvePath(const std::string& request_path, HandlerContext& ctx);
    static bool isPathSafe(const std::string& path, const std::string& root);
    static std::string normalizePath(const std::string& path);
    
    static Session* getSessionFromRequest(const Request& req);
    static Cookie createSessionCookie(const Session& session);
    static void destroySession(const Request& req);
    static Session* getOrCreateSession(Request& req, Response& res);

protected:
    void setCommonHeaders(Response& response);
};
```

### Static File Handler
```cpp
class StaticFileHandler : public Handler {
public:
    StaticFileHandler();
    ~StaticFileHandler();
    Response handle(HandlerContext& ctx);

private:
    bool serveFile(const std::string& filePath, Response& res, std::string method);
};
```

### AutoIndex Handler
```cpp
class AutoIndexHandler : public Handler {
public:
    AutoIndexHandler();
    ~AutoIndexHandler();
    Response handle(HandlerContext& ctx);

private:
    std::pair<int, std::string> generateDirectoryListing(const std::string& dirPath, const std::string& requestPath);
};
```

### Upload Handler
```cpp
struct UploadedFile {
    std::string fileName;
    std::string contentType;
    std::vector<char> data;
};

class UploadHandler : public Handler {
private:
    std::string _uploadDirectory;

public:
    UploadHandler();
    UploadHandler(const std::string& uploadDir);
    ~UploadHandler();
    Response handle(HandlerContext& ctx);

private:
    std::vector<UploadedFile> parseMultipart(const Request& request);
    bool saveFile(const UploadedFile& file, std::string& savedPath);
    bool validateFile(const UploadedFile& file, const Location loc);
    std::string generateUniqueFilename(const std::string& original);
};
```

### Delete Handler
```cpp
class DeleteHandler : public Handler {
public:
    DeleteHandler();
    ~DeleteHandler();
    Response handle(HandlerContext& ctx);

private:
    bool isDeletionSafe(const std::string& path, HandlerContext& ctx);
};
```

### Error Handler
```cpp
class ErrorHandler : public Handler {
private:
    int _status;
    std::string _location_url;

public:
    ErrorHandler();
    ErrorHandler(int status);
    ErrorHandler(int status, const std::string& url);
    ~ErrorHandler();
    Response handle(HandlerContext& ctx);

    static Response buildErrorResponse(int status, const ServerConfig& config);
    static Response buildResponseWithLocation(int code, const std::string& url);
};
```

---

## 5. CGI System (04_cgi/)

### CGI Interpreter
```cpp
struct CGIInterpreter {
    std::string extension;
    std::string interpreter_path;
    std::vector<std::string> args;

    CGIInterpreter();
    CGIInterpreter(const std::string& ext, const std::string& path, 
                  const std::vector<std::string>& a = std::vector<std::string>());
};
```

### CGI Request
```cpp
struct CGIRequest {
    std::string script_path;
    std::string req_script_path;
    std::string interpreter;
    std::map<std::string, std::string> env;
    std::string stdin_data;
    std::string working_dir;
    std::vector<std::string> script_args;

    CGIRequest();
    CGIRequest(const std::string& script, const std::string& interp, 
              const std::map<std::string, std::string>& environment,
              const std::string& stdin_data = "",
              const std::string& wd = ".",
              const std::vector<std::string>& args = std::vector<std::string>());
};
```

### CGI Response
```cpp
struct CGIResponse {
    std::map<std::string, std::string> headers;
    std::string body;
    int exit_code;
    bool timed_out;
    std::string error_output;
    bool success;
    int http_status;
    std::map<std::string, std::string> environment;
    std::string executed_command;
    long execution_time_ms;
    time_t start_time;

    CGIResponse();

    size_t getContentLength() const;
    bool hasHeaders() const;
    std::string getHeader(const std::string& name) const;
    bool hasHeader(const std::string& name) const;
};
```

### CGI Statistics
```cpp
struct CGIStats {
    size_t total_executions;
    size_t successful_executions;
    size_t timed_out_executions;
    size_t failed_executions;
    std::map<std::string, size_t> executions_by_extension;
    std::map<std::string, size_t> executions_by_script;
    long total_execution_time_ms;
    std::map<int, size_t> executions_by_status;
    size_t total_content_bytes;

    CGIStats();

    double getSuccessRate() const;
    double getAverageExecutionTime() const;
    double getAverageResponseSize() const;
    std::string getMostUsedExtension() const;
};
```

### CGI Process Tracking
```cpp
struct PendingCGI {
    pid_t pid;
    int stdout_fd;
    int stderr_fd;
    int stdin_fd;
    time_t start_time;
    std::string stdout_buffer;
    std::string stderr_buffer;
    int client_fd;
    CGIRequest request;
    int timeout_seconds;
    bool process_complete;
    bool headers_parsed;
    CGIResponse response;
};
```

### CGI Manager
```cpp
class CGI {
private:
    std::map<std::string, CGIInterpreter> interpreters;
    std::set<pid_t> active_processes;
    std::map<pid_t, PendingCGI> pending_processes_;
    std::vector<std::pair<int, CGIResponse> > completed_responses_;
    CGIStats stats;

public:
    CGI();
    ~CGI();

    void addInterpreter(const std::string& extension, const std::string& interpreter_path, 
                       const std::vector<std::string>& args = std::vector<std::string>());
    bool supportsCGI(const std::string& file_extension) const;
    void removeInterpreter(const std::string& extension);
    std::vector<std::string> getSupportedExtensions() const;
    CGIInterpreter getInterpreter(const std::string& extension) const;

    CGIStats getStats() const;
    void resetStats();

    size_t getActiveProcessCount() const;
    void killAllActiveProcesses();
    size_t getMaxProcesses(HandlerContext& ctx) const;
    bool canExecute(HandlerContext& ctx) const;
    int getTimeout(HandlerContext& ctx) const;

    bool executeAsync(HandlerContext& ctx, int client_fd);
    void checkAllProcesses();
    std::vector<std::pair<int, CGIResponse> > getCompletedProcesses();
};
```

### CGI Handler
```cpp
class CGIHandler : public Handler {
private:
    CGI &cgi_;

public:
    CGIHandler(CGI& cgi);
    ~CGIHandler();

    bool canHandle(const Request& req, const Location& loc) const;
    Response handle(HandlerContext& ctx);

private:
    Response convertToHttpResponse(const CGIResponse& cgi_resp) const;
};
```

---

## 6. Session Management (05_session/)

### Cookie
```cpp
class Cookie {
private:
    std::string name_;
    std::string value_;
    std::string path_;
    std::string domain_;
    int maxAge_;
    bool httpOnly_;
    bool secure_;

public:
    Cookie();
    Cookie(const std::string& name, const std::string& value);

    void setName(const std::string& name);
    void setValue(const std::string& value);
    void setPath(const std::string& path);
    void setDomain(const std::string& domain);
    void setMaxAge(int maxAge);
    void setHttpOnly(bool httpOnly);
    void setSecure(bool secure);

    const std::string& getName() const;
    const std::string& getValue() const;
    const std::string& getPath() const;
    const std::string& getDomain() const;
    int getMaxAge() const;
    bool isHttpOnly() const;
    bool isSecure() const;

    std::string toString() const;
    static Cookie parse(const std::string& cookieStr);
};
```

### Session
```cpp
const std::time_t SESSION_TIMEOUT_1MIN = 60;
const std::time_t SESSION_TIMEOUT_10MIN = 600;
const std::time_t SESSION_TIMEOUT_30MIN = 1800;
const std::time_t SESSION_TIMEOUT_60MIN = 18000;
const std::time_t SESSION_TIMEOUT_24HOURS = 86400;

class Session {
private:
    std::string id_;
    std::map<std::string, std::string> data_;
    std::time_t creationTime_;
    std::time_t lastAccessTime_;
    std::time_t expirationTime_;

public:
    Session();
    Session(const std::string& id);

    const std::string& getId() const;
    void setData(const std::string& key, const std::string& value);
    std::string getData(const std::string& key) const;
    bool hasData(const std::string& key) const;
    void removeData(const std::string& key);
    void clear();
    const std::map<std::string, std::string>& getAllData() const;

    std::time_t getCreationTime() const;
    std::time_t getLastAccessTime() const;
    void updateAccessTime();
    bool isExpired() const;
    void setExpiration(std::time_t expiration);
    std::time_t getExpiration() const;
};
```

### Session Manager
```cpp
class SessionManager {
private:
    std::map<std::string, Session> sessions_;
    std::time_t sessionTimeout_;

    SessionManager();
    std::string generateSessionId();

public:
    static SessionManager& getInstance();

    Session& createSession();
    Session* getSession(const std::string& sessionId);
    bool destroySession(const std::string& sessionId);
    void cleanupExpiredSessions();

    void setSessionTimeout(std::time_t timeout);
    std::time_t getSessionTimeout() const;
    size_t getActiveSessionsCount() const;
};
```

### Session Demo Handler
```cpp
class SessionDemoHandler : public Handler {
public:
    SessionDemoHandler();
    virtual ~SessionDemoHandler();
    virtual Response handle(HandlerContext& ctx);
};
```

---

## 7. Utility Structures (06_utils/)

### Core Utilities
```cpp
namespace Utils {
    template <typename T>
    std::string toString(const T& value);

    int toInt(const std::string& str);
    std::string trim(const std::string& str);
    std::string toLowerCase(const std::string& str);
}
```

### Logging System
```cpp
class Logger {
public:
    enum Level { DEBUG, INFO, WARN, ERROR };

    static void init(const std::string& filename = "");
    static void shutdown();
    static void setLevel(Level level);
    static Level getLevel();
    static void info(const std::string& msg);
    static void warn(const std::string& msg);
    static void error(const std::string& msg);
    static void debug(const std::string& msg);
};
```

### Configuration Utilities
```cpp
namespace ConfigUtils {
    size_t parseSizeWithUnit(const std::string& sizeStr, int line = 0);
    int parseTimeWithUnit(const std::string& timeStr, int line = 0);
    std::vector<std::string> makeVector(const char* first);
    std::vector<std::string> makeVector(const char* first, const char* second);
    std::vector<std::string> makeVector(const char* first, const char* second, const char* third);
}
```

### CGI Utilities
```cpp
namespace CGIUtils {
    std::string makeQueryString(const std::map<std::string, std::string>& params);
    void parseCGIOutput(const std::string& output, CGIResponse& result);
    void parseStatusLine(const std::string& status_line, CGIResponse& result);
    void extractHttpStatus(CGIResponse& result);
    void setSuccessFlag(CGIResponse& result);
    std::string generateDebugInfo(const CGIRequest& req);
}
```

---

## Key Constants and Defaults

### Configuration Defaults
```cpp
const size_t DEFAULT_CLIENT_MAX_BODY_SIZE = 1024 * 1024; // 1MB
const int DEFAULT_CONNECTION_TIMEOUT = 60;              // 60 seconds
const size_t DEFAULT_MAX_CONNECTIONS = 1024;           // 1024 connections
const int DEFAULT_CGI_TIMEOUT = 30;                    // 30 seconds
const int DEFAULT_MAX_CGI_PROCESSES = 10;                 // 10 processes
const std::string DEFAULT_UPLOAD_DIR = "./assets/upload"; // Upload directory

// Session timeouts
const std::time_t SESSION_TIMEOUT_1MIN = 60;
const std::time_t SESSION_TIMEOUT_10MIN = 600;
const std::time_t SESSION_TIMEOUT_30MIN = 1800;
const std::time_t SESSION_TIMEOUT_60MIN = 18000;
const std::time_t SESSION_TIMEOUT_24HOURS = 86400;
```

### Event Loop Constants
```cpp
#define SERVER_POLL_TIME 20
```

---

## Implementation Notes

### Memory Management
- **ConnectionPool** owns all Connection objects (RAII pattern)
- **SessionManager** singleton owns all Session objects
- **CGI** manages process lifecycle and cleanup
- Raw pointers used with explicit ownership (C++98 compatibility)

### Thread Safety
- Single-threaded event loop design
- No mutexes or locks required
- Connection state managed within event loop

### Security Design
- Path validation at multiple layers
- Input size limits enforced
- CGI process isolation and timeouts
- Session ID randomization
- HttpOnly cookies by default

### Performance Optimizations
- **epoll** for scalable I/O multiplexing
- Non-blocking I/O throughout
- Buffer consumption tracking for keep-alive
- Lazy session cleanup
- Process limits for resource protection

---

## Change Log

### Version 2.0 (Current)
- Added WAITING_FOR_CGI state and CGI-related fields
- Added access control fields (deny_all, denied_ips, return_code)
- Added session management structures
- Added NonBlockingIO and Server classes
- Enhanced timeout configuration (client_header_timeout, client_body_timeout)
- Comprehensive field-level documentation

### Version 1.0
- Initial data structure documentation
- Basic connection and request structures
- Core configuration hierarchy
```

---

## Summary

✅ **Validation Complete**: All data structures from header files are now captured in the documentation.

### Key Updates Made:
1. **Added missing structures**: `NonBlockingIO`, `Server`, `SocketEntry`, `PendingCGI`
2. **Enhanced field completeness**: Added all fields to structs with proper types
3. **Added missing fields**: `has_received_data` in ConnectionInfo, access control fields
4. **Organized by module**: Clear section hierarchy matching codebase
5. **Added constants**: All default values and timeout constants
6. **Enhanced formatting**: Consistent code blocks with proper syntax highlighting
7. **Added implementation notes**: Memory management, thread safety, security design