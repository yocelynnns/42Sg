# Web Server Project - 04_cgi Module Documentation

## Overview

The `04_cgi/` module implements **Common Gateway Interface (CGI/1.1)** dynamic script execution, enabling the web server to generate dynamic content through external interpreters. It provides comprehensive process management, secure execution environments, timeout controls, and robust error handling with seamless integration into the request handler pipeline.

**Design Philosophy**: Secure, protocol-compliant CGI execution with explicit process lifecycle management, resource limits, and non-blocking I/O integration.

---

## Module Structure

```
04_cgi/
├── CGI.hpp/cpp                 # Core CGI engine with process management
├── CGIHandler.hpp/cpp          # HTTP handler integration and request routing
└── cgiUtils.hpp/cpp            # CGI output parsing and environment utilities
```

---

## Core Responsibilities

| Responsibility | Description |
|----------------|-------------|
| **Request Detection** | Identify CGI requests via file extensions and location configuration |
| **Script Validation** | Verify script existence, regular file type, and execute permissions |
| **Interpreter Mapping** | Map file extensions to interpreter binaries with configurable arguments |
| **Environment Construction** | Build CGI/1.1-compliant environment variables with security sanitization |
| **Process Execution** | Fork, execute scripts with non-blocking I/O via pipes, track PIDs |
| **Timeout Enforcement** | Monitor execution time with configurable per-location limits |
| **Output Parsing** | Separate CGI-generated headers from response body |
| **Error Handling** | Manage timeouts, exit codes, and malformed output with HTTP status mapping |
| **Statistics Tracking** | Collect execution metrics: success rates, timing, resource usage |
| **Process Limits** | Enforce concurrent CGI process limits to prevent resource exhaustion |

---

## Key Data Structures

### CGIInterpreter
Represents interpreter configuration for specific file extensions.

```cpp
struct CGIInterpreter {
    std::string extension;                // File extension (e.g., ".py", ".php")
    std::string interpreter_path;         // Path to interpreter executable
    std::vector<std::string> args;        // Additional interpreter arguments

    CGIInterpreter();
    CGIInterpreter(const std::string& ext, const std::string& path, 
                  const std::vector<std::string>& a = std::vector<std::string>());
};
```

### CGIRequest
Contains all data required for CGI script execution.

```cpp
struct CGIRequest {
    std::string script_path;              // Absolute resolved filesystem path
    std::string req_script_path;          // Original request path (for CGI variables)
    std::string interpreter;              // Interpreter binary to execute
    std::map<std::string, std::string> env; // CGI/1.1 environment variables
    std::string stdin_data;               // POST body data for stdin
    std::string working_dir;              // Execution working directory
    std::vector<std::string> script_args; // Command-line arguments

    CGIRequest();
    CGIRequest(const std::string& script, const std::string& interp, 
              const std::map<std::string, std::string>& environment,
              const std::string& stdin_data = "",
              const std::string& wd = ".",
              const std::vector<std::string>& args = std::vector<std::string>());
};
```

### CGIResponse
Comprehensive execution results with debugging information.

```cpp
struct CGIResponse {
    std::map<std::string, std::string> headers; // Parsed CGI headers (from stdout)
    std::string body;                           // Response body content
    int exit_code;                              // Child process exit code
    bool timed_out;                             // True if process timed out
    std::string error_output;                   // Captured stderr content
    
    // Convenience fields
    bool success;                               // True if exit_code == 0 && !timed_out
    int http_status;                            // Determined from output or exit code
    
    // Debug information
    std::map<std::string, std::string> environment; // Environment variables passed
    std::string executed_command;                   // Full command executed
    long execution_time_ms;                         // Execution duration
    time_t start_time;                              // Execution start timestamp

    // Helper methods
    size_t getContentLength() const;
    bool hasHeaders() const;
    std::string getHeader(const std::string& name) const;
    bool hasHeader(const std::string& name) const;

    CGIResponse();
};
```

### CGIStats
Execution statistics for monitoring and analysis.

```cpp
struct CGIStats {
    size_t total_executions;           // Total scripts executed
    size_t successful_executions;      // Successful completions
    size_t timed_out_executions;       // Timeout occurrences
    size_t failed_executions;          // Failed executions
    std::map<std::string, size_t> executions_by_extension; // Count by file type
    std::map<std::string, size_t> executions_by_script;    // Count per script
    long total_execution_time_ms;      // Cumulative execution time
    std::map<int, size_t> executions_by_status; // Count by HTTP status
    size_t total_content_bytes;        // Total bytes returned

    // Helper methods
    double getSuccessRate() const;
    double getAverageExecutionTime() const;
    double getAverageResponseSize() const;
    std::string getMostUsedExtension() const;

    CGIStats();
};
```

### PendingCGI
Internal tracking for active CGI processes.

```cpp
struct PendingCGI {
    pid_t pid;                    // Child process ID
    int stdout_fd;                // Read pipe for stdout
    int stderr_fd;                // Read pipe for stderr
    int stdin_fd;                 // Write pipe for stdin (-1 if not needed)
    time_t start_time;            // Execution start timestamp
    std::string stdout_buffer;    // Accumulated stdout data
    std::string stderr_buffer;    // Accumulated stderr data
    int client_fd;                // Connection fd for response routing
    CGIRequest request;           // CGI request data
    int timeout_seconds;          // Timeout threshold
    bool process_complete;        // Execution finished flag
    bool headers_parsed;          // Headers extracted from output
    CGIResponse response;         // Execution results
};
```

---

## Component Details

### CGI Class (Core Execution Engine)

Manages interpreter registration, script execution, process monitoring, and statistics.

**Public Interface**:

```cpp
class CGI {
public:
    // Lifecycle
    CGI();
    ~CGI();

    // Interpreter Management
    void addInterpreter(const std::string& extension, const std::string& interpreter_path, 
                       const std::vector<std::string>& args = std::vector<std::string>());
    bool supportsCGI(const std::string& file_extension) const;
    void removeInterpreter(const std::string& extension);
    std::vector<std::string> getSupportedExtensions() const;
    CGIInterpreter getInterpreter(const std::string& extension) const;

    // Statistics Access
    CGIStats getStats() const;
    void resetStats();

    // Process Management
    size_t getActiveProcessCount() const;
    void killAllActiveProcesses();
    size_t getMaxProcesses(HandlerContext& ctx) const;
    bool canExecute(HandlerContext& ctx) const;
    int getTimeout(HandlerContext& ctx) const;

    // Asynchronous Execution
    bool executeAsync(HandlerContext& ctx, int client_fd);
    void checkAllProcesses();
    std::vector<std::pair<int, CGIResponse> > getCompletedProcesses();

private:
    std::map<std::string, CGIInterpreter> interpreters;
    std::set<pid_t> active_processes;
    std::map<pid_t, PendingCGI> pending_processes_;
    std::vector<std::pair<int, CGIResponse> > completed_responses_;
    CGIStats stats;

    // Process tracking
    void registerProcess(pid_t pid);
    void unregisterProcess(pid_t pid);
    
    // Statistics
    void updateStats(const CGIResponse& response, const std::string& script_path, 
                    const std::string& extension);
    
    // Request construction
    CGIRequest buildCGIRequest(HandlerContext& ctx) const;
    std::map<std::string, std::string> buildEnvironment(HandlerContext& ctx) const;

    // Process execution
    bool startProcess(const CGIRequest& req, PendingCGI& pending, 
                     int client_fd, int timeout_seconds);
    void checkProcessCompletion(PendingCGI& pending);
    void cleanupProcess(PendingCGI& pending);
    void readAvailableData(PendingCGI& pending);
};
```

**Key Methods**:
- `executeAsync`: Non-blocking execution entry point
- `checkAllProcesses`: Polls active processes for completion
- `getCompletedProcesses`: Retrieves finished executions for response generation
- `canExecute`: Enforces concurrent process limits
- `buildCGIRequest`: Constructs execution context from HTTP request
- `buildEnvironment`: Creates CGI/1.1 environment variables

### CGIHandler Class (HTTP Handler Integration)

Bridges the HTTP handler system with the CGI execution engine.

**Public Interface**:

```cpp
class CGIHandler : public Handler {
public:
    CGIHandler(CGI& cgi);
    ~CGIHandler();

    // Handler interface implementation
    bool canHandle(const Request& req, const Location& loc) const;
    Response handle(HandlerContext& ctx);

private:
    CGI &cgi_;  // CGI execution engine reference

    Response convertToHttpResponse(const CGIResponse& cgi_resp) const;
};
```

---

## Configuration Hierarchy

### Inheritance Flow

Values cascade from global defaults to location-specific configurations:

```
EventsConfig (global defaults)
    ↓
ServerConfig (per-server settings)
    ↓
Location (most specific, per-URL path)
```

### Configuration Directives

| Directive | Context | Purpose | Default |
|-----------|---------|---------|---------|
| `cgi_enable` | location | Enable CGI processing for location | `false` |
| `cgi_extensions` | location | Recognized CGI file extensions | `[]` |
| `cgi_interpreters` | location | Extension → interpreter mapping | `{}` |
| `default_cgi_interpreter` | location | Fallback interpreter path | `""` |
| `cgi_timeout` | events, server, location | Execution timeout (seconds) | `30` |
| `cgi_max_processes` | events, server, location | Concurrent process limit | `10` |

### Default Application

**Inheritance Rules**:
- Location-specific values override server defaults
- Server values override global event values
- Hard-coded defaults applied if no configuration provided

**Example Cascade**:
```
Events: cgi_timeout = 30s, cgi_max_processes = 10
    ↓
Server: cgi_timeout = 45s (overrides Events)
    ↓
Location /api: cgi_timeout = 60s (overrides Server)
Location /cgi: cgi_timeout = 45s (inherits from Server)
```

---

## Execution Flow

### Request Processing Lifecycle

```
1. Handler Detection
   HandlerFactory::createHandler()
   ↓
   Check extension in ctx.loc->cgi_extensions
   ↓
   Verify ctx.loc->cgi_enable == true
   ↓
   Validate script exists and is executable
   ↓
   Confirm interpreter mapping exists
   ↓
   Create CGIHandler

2. Asynchronous Execution
   CGIHandler::handle()
   ↓
   cgi_.executeAsync(ctx, client_fd)
   ↓
   Build CGIRequest (resolve path, set environment)
   ↓
   Create stdin/stdout/stderr pipes (non-blocking)
   ↓
   fork() → child process
   ↓
   Child: chdir(), execve(interpreter, [interpreter, script], env)
   Parent: register PID, store PendingCGI state
   ↓
   Return to main event loop

3. Process Monitoring
   Server::processCGICompletions()
   ↓
   cgi_.checkAllProcesses()
   ↓
   For each pending process:
      readAvailableData() → append to buffers
      checkProcessCompletion() → waitpid(WNOHANG)
      ↓
      If timeout exceeded:
         kill(pid, SIGKILL)
         Mark timed_out = true
      ↓
      If exited (WIFEXITED):
         Capture exit_code via WEXITSTATUS()
         Mark process_complete = true
      ↓
      If signaled (WIFSIGNALED):
         Log termination signal
         Mark process_complete = true

4. Response Generation
   PendingCGI::process_complete == true
   ↓
   Parse CGI output (headers + body separation)
   ↓
   Validate required headers (Content-Type)
   ↓
   Determine http_status:
      - From Status: header if present
      - From exit_code (0 → 200, non-zero → 502)
      - From timed_out flag (504)
   ↓
   Update statistics (total, success, timeout counts)
   ↓
   Store in completed_responses_ (pair<client_fd, CGIResponse>)
   ↓
   cleanupProcess() → close pipes, unregister PID

5. Completion Handling
   Server retrieves completed_responses_
   ↓
   For each completion:
      Find connection by fd
      ↓
      If connection waiting for CGI:
         convertToHttpResponse() → HTTP Response
         conn->writeData(response)
         conn->setState(WRITING_RESPONSE)
         updateActivity()
      ↓
   Clear completed_responses_ list
```

---

## Validation Strategy

### Pre-Execution Validation

**Script Validation**:
- Script path resolved via handler path resolution system
- `stat()` verification: file exists and is regular file (S_ISREG)
- `access()` verification: execute permission granted (X_OK)
- Path safety check: within document root boundary

**Interpreter Validation**:
- Extension exists in `cgix_interpreters` map or `default_cgi_interpreter` set
- Interpreter path absolute and executable
- Working directory accessible by child process

**Configuration Validation**:
- `cgi_enable` true for location
- File extension in `cgi_extensions` list
- Concurrent processes under `cgi_max_processes` limit

### Post-Execution Validation

**Output Parsing**:
- Header/body separation via double CRLF (`\r\n\r\n`)
- Required headers: Content-Type must be present
- Optional headers: Status, Location, Set-Cookie
- Body length verification against Content-Length

**Exit Code Mapping**:
- `exit_code == 0 && success == true` → 200 OK
- `exit_code != 0` → 502 Bad Gateway (script error)
- `exit_code == -1` (signal termination) → 502 Bad Gateway
- `timed_out == true` → 504 Gateway Timeout

**Header Integrity**:
- Header names sanitized (no CRLF injection)
- Content-Type validated presence
- Content-Length matches body size if present

---

## Error Handling

### Error Types and HTTP Status Mapping

| Error Type | Detection Point | HTTP Status | Cause |
|------------|----------------|-------------|-------|
| **No Interpreter** | Handler creation | 500 | Extension not mapped, no default |
| **Script Not Found** | Path validation | 404 | File does not exist on filesystem |
| **Not Executable** | Permission check | 403 | Script lacks execute permission |
| **Not Regular File** | File type check | 403 | Target is directory or special file |
| **Process Limit** | Pre-execution | 503 | Concurrent processes at maximum |
| **Execution Timeout** | Process monitoring | 504 | Script exceeded timeout seconds |
| **Non-Zero Exit** | Exit code check | 502 | Script returned failure code |
| **Signal Termination** | Wait status | 502 | Script killed by signal |
| **Missing Content-Type** | Output parsing | 502 | CGI output missing required header |
| **Malformed Output** | Header parsing | 502 | Invalid header/body separation |
| **Pipe Creation** | Process start | 500 | Failed to create communication pipes |
| **Fork Failure** | fork() call | 500 | System resource exhaustion |

### Error Recovery

**Process Cleanup**:
- All pipes closed on error
- Child processes killed (SIGKILL)
- PIDs unregistered from active set
- Resources freed immediately

**Connection State**:
- WAITING_FOR_CGI → WRITING_RESPONSE on completion/errors
- Error responses generated via ErrorHandler
- Connection may close on errors depending on keep-alive

**Logging Strategy**:
- **Debug**: Configuration, environment variables, command construction
- **Info**: Successful executions (script, PID, duration)
- **Warn**: Timeouts, partial writes, non-zero exit codes
- **Error**: Failures, permission issues, pipe errors, fork failures

---

## Security Considerations

### Path and File Security

**Traversal Prevention**:
- Scripts must pass handler path resolution validation
- Resolved path must start with document root
- `../` sequences blocked during path resolution
- Symbolic links constrained to root boundaries
- Working directory set to script directory (chdir safety)

**Script Integrity**:
- Only regular files executable (S_ISREG)
- Execute permission required (access X_OK)
- Extension must match configured `cgi_extensions`
- No shell scripts without explicit interpreter

### Process Isolation

**Resource Separation**:
- Each script runs in dedicated child process
- Memory isolated via fork() copy-on-write
- File descriptors limited to stdin/stdout/stderr pipes
- Parent environment not inherited (explicit envp only)
- Process limits prevent fork bombs

**Execution Constraints**:
- `chdir()` to script directory before execution
- No parent process file descriptor inheritance
- Controlled environment variables only
- Timeout enforcement prevents infinite loops
- Signal-based termination (SIGKILL) on timeout

### Resource Management

**Process Limits**:
- `cgi_max_processes` enforces fork capacity
- `canExecute()` checks active_processes.size() before fork
- Warning logged when limit reached (503 returned)
- Processes killed on timeout to free resources

**I/O Buffering**:
- Pipe buffers size-limited (4096 bytes per read)
- Non-blocking reads prevent parent process hang
- Stdout/stderr accumulated in string buffers
- Large outputs constrained by available memory

### Environment Security

**Controlled Variables**:
- Only CGI/1.1 specified variables passed
- HTTP headers sanitized and transformed (HTTP_*)
- No sensitive system variables exposed
- REQUEST_METHOD, PATH_INFO, QUERY_STRING validated
- DOCUMENT_ROOT from configuration (not filesystem)

**Header Sanitization**:
- HTTP header names: lowercase → uppercase, '-' → '_'
- Header values trimmed of whitespace
- No CRLF injection in header names/values
- REDIRECT_STATUS set to "200" for PHP compatibility

---

## Integration with Other Modules

### With 03_handlers/Handler System

**CGIHandler** (`03_handlers`):
- Instantiated when file extension matches `cgi_extensions`
- Validates script existence and executability before execution
- Uses pre-resolved path from `ctx.req.getResolvedPath()`
- Returns immediately after `executeAsync()` (no blocking)
- Connection state set to WAITING_FOR_CGI

**Path Resolution Reuse**:
- Leverages handler system's centralized path resolution
- No duplicate validation in CGI module
- Trusts resolved path safety checks
- Uses `ctx.req.getResolvedPath()` for execution

### With 01_config/Configuration System

**Location Configuration**:
- `cgi_enable` activates CGI processing for location
- `cgi_extensions` defines recognized file types (e.g., `.py`, `.php`)
- `cgi_interpreters` maps extensions to interpreter paths
- `default_cgi_interpreter` provides fallback for unmapped extensions
- `cgi_timeout` and `cgi_max_processes` control resource usage

**Configuration Access**:
- `getTimeout()` reads from location → server → events hierarchy
- `getMaxProcesses()` reads from location → server configuration
- Interpreter mappings location-specific (no inheritance)

### With 02_http/HTTP Layer

**Environment Construction**:
- HttpMethod converted to string (GET, POST, DELETE)
- uri, path, query string extracted from HttpRequest
- Headers transformed to HTTP_* format
- Content-Type and Content-Length passed directly
- SERVER_NAME from `ctx.req.getHost()`
- SERVER_PORT from `ctx.config.port`

**Request Body Handling**:
- POST body from `ctx.req.getBody()` → `stdin_data`
- CONTENT_LENGTH set from "Content-Length" header
- CONTENT_TYPE set from "Content-Type" header
- Empty body for GET requests (stdin redirected from `/dev/null`)

**CGI to HTTP Conversion**:
- CGIResponse::headers → Response headers
- CGIResponse::body → Response body
- CGIResponse::http_status → Response status code
- CGIResponse::error_output logged for debugging

### With 06_utils/Utility Functions

**CGI Utilities** (`06_utils/cgiUtils.hpp`):
- `CGIUtils::parseCGIOutput()`: Separates headers from body
- `CGIUtils::makeQueryString()`: Constructs QUERY_STRING from parsed params
- `CGIUtils::parseStatusLine()`: Extracts HTTP status from Status header
- `CGIUtils::extractHttpStatus()`: Determines final HTTP status code
- `CGIUtils::setSuccessFlag()`: Evaluates execution success conditions
- `CGIUtils::generateDebugInfo()`: Creates execution summary

**Logger Integration**:
- `Logger::debug()`: Configuration, environment, process registration
- `Logger::info()`: Successful execution details (PID, duration)
- `Logger::warn()`: Timeouts, partial writes, non-zero exits
- `Logger::error()`: Failures, pipe errors, fork failures

**String Utilities**:
- `Utils::toString()`: PID and integer conversions
- `HttpUtils::methodToString()`: Method enum to string for CGI

---

## Advanced Topics

### Custom Interpreter Support

**Interpreter Configuration**:
- Any executable binary can serve as interpreter
- Additional command-line arguments configurable per extension
- Example: `.py` → `/usr/bin/python3 -u` (unbuffered)
- Default interpreter applies to all extensions not explicitly mapped

**Timeout Customization**:
- Per-extension timeout via CGIInterpreter struct
- Fallback to location → server → events cascade
- PHP scripts may need longer timeouts (image processing)
- Python scripts typically shorter (fast execution)

### Statistics and Monitoring

**Performance Metrics**:
- `getSuccessRate()`: Percentage of successful executions
- `getAverageExecutionTime()`: Mean execution duration
- `getAverageResponseSize()`: Mean response body size
- `getMostUsedExtension()`: Most frequently executed file type

**Usage Tracking**:
- `executions_by_extension`: Maps extension to count
- `executions_by_script`: Maps script path to count
- `executions_by_status`: Maps HTTP status to count
- Resettable via `resetStats()` for load testing

**Debugging Integration**:
- `debugExecute()` mode for troubleshooting
- Environment inspection without full execution
- Command construction validation
- Execution time measurement precision: milliseconds

### Debug Mode

**Development Diagnostics**:
- Verbose logging of all environment variables
- Full command-line printed before execve
- Stdin data hex dump for validation
- Stdout/stderr capture details
- Exit code and signal information

**Safe Execution**:
- Debug mode uses synchronous execution (blocking)
- Not for production use (blocks event loop)
- Validates configuration without forking
- Checks interpreter paths and permissions

---

## Key Design Decisions

### Why Non-Blocking Execution?

**Decision**: Implement fully asynchronous CGI execution to prevent blocking the main event loop.

**Rationale**:
- **Scalability**: Event loop continues serving other clients during CGI execution
- **Resource Efficiency**: No threads, minimal memory overhead per request
- **Timeout Control**: Parent process can enforce execution time limits
- **Integration**: Seamless with epoll-based architecture
- **Responsiveness**: Server remains responsive under heavy CGI load

**Trade-off**: Increased complexity with process management, state tracking, and completion polling.

### Why Centralized PID Management?

**Decision**: Track all active CGI processes in `active_processes` set with lifecycle hooks.

**Rationale**:
- **Resource Accounting**: Precise count for `canExecute()` limit enforcement
- **Cleanup Safety**: Global kill on server shutdown prevents zombie processes
- **Debug Visibility**: Process list available for monitoring
- **Leak Prevention**: Automatic cleanup in all exit paths

### Why Pipe-Based I/O?

**Decision**: Use `pipe()` for stdin/stdout/stderr communication with non-blocking mode.

**Rationale**:
- **Isolation**: Strong separation between parent and child processes
- **Flexibility**: Can write POST data to stdin, capture all outputs
- **Non-Blocking**: Set O_NONBLOCK for seamless event loop integration
- **Reliability**: Kernel-managed buffering, no temporary files

**Limitation**: Pipes have finite buffer size; large POST bodies may require multiple writes.

### Why Execute Directly (No Shell)?

**Decision**: Use `execve()` directly rather than `system()` or shell invocation.

**Rationale**:
- **Security**: No shell injection vulnerabilities possible
- **Control**: Explicit argv and envp arrays
- **Performance**: No shell process overhead
- **Reliability**: Direct interpreter execution, no shell interpretation

**Requirement**: Interpreter path must be absolute and executable.

### Why Statistics Collection?

**Decision**: Track detailed execution metrics across multiple dimensions.

**Rationale**:
- **Monitoring**: Production visibility into CGI performance
- **Debugging**: Identify slow scripts or common failures
- **Capacity Planning**: Understand resource usage patterns
- **Optimization**: Data-driven performance improvements

**Implementation**: Lightweight counters updated on completion, no performance impact.

---

## Summary

The `04_cgi/` module provides enterprise-grade CGI execution with:

✅ **Full CGI/1.1 Compliance**: Complete environment variable specification  
✅ **Secure Process Isolation**: Fork/exec model with controlled environment  
✅ **Non-Blocking Architecture**: Asynchronous execution integrated with event loop  
✅ **Resource Protection**: Process limits, timeouts, and memory constraints  
✅ **Centralized Path Reuse**: Leverages handler path resolution system  
✅ **Comprehensive Error Handling**: Appropriate HTTP status mapping  
✅ **Detailed Statistics**: Multi-dimensional execution metrics  
✅ **Flexible Configuration**: Extension-based interpreter mapping with inheritance  
✅ **Production Monitoring**: Real-time process tracking and completion polling  

**Key Strengths**:
- **Security-First**: Multiple validation layers, no shell invocation, process isolation
- **Event-Driven**: Seamless non-blocking integration with epoll architecture
- **Resource-Aware**: Enforced limits prevent server exhaustion
- **Debuggable**: Extensive logging, statistics, and debug mode
- **Standards-Compliant**: Full CGI/1.1 protocol implementation

**Integration Excellence**:
- Reuses handler path resolution for consistency and security
- Integrates with configuration inheritance system
- Transforms HTTP requests to CGI environment correctly
- Converts CGI responses to HTTP responses seamlessly
- Works with connection state management (WAITING_FOR_CGI)

This CGI implementation provides a robust, secure foundation for dynamic content generation while maintaining the server's performance, security, and architectural integrity.