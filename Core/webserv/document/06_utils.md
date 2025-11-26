# Web Server Project - 06_utils Module Documentation

## Overview

The `06_utils/` module provides **foundational utility services** that support all other components of the web server. It delivers essential functionality for string manipulation, type conversion, multi-level logging, configuration value parsing with units, and CGI-specific operations through a cohesive, header-oriented architecture.

**Design Philosophy**: Provide robust, reusable utilities with comprehensive error handling, C++98 compatibility, consistent behavior across all server components, and header-based implementations for optimal performance.

---

## Module Structure

```
06_utils/
├── Utils.hpp/cpp              # Core string and type conversion utilities
├── Logger.hpp/cpp             # Multi-level logging with file support
├── configUtils.hpp            # Configuration value parsing with unit support
├── cgiUtils.hpp               # CGI response parsing and helper functions
└── (Minimal .cpp files - primarily header-based)
```

---

## Core Responsibilities

| Responsibility | Description |
|----------------|-------------|
| **String Manipulation** | Trimming, case conversion, and safe parsing with C++98 compatibility |
| **Type Conversion** | Template-based toString and safe string-to-integer conversion |
| **Logging System** | Multi-level logging (DEBUG/INFO/WARN/ERROR) with colors and file output |
| **Configuration Parsing** | Size (K/M/G) and time (s/m/h) unit parsing with validation |
| **CGI Utilities** | CGI output parsing, query string generation, and debugging |
| **Input Validation** | Safe parsing with bounds checking and detailed error reporting |

---

## Component Architecture

### Utils (Core String and Type Utilities)

**Purpose**: Provide fundamental string manipulation and type conversion capabilities with safety and performance.

**Key Features**:
- Header-only template implementations for optimal performance
- C++98 compatible with no external dependencies
- Comprehensive error handling for parsing operations
- Unicode-safe character processing

#### Public Interface

```cpp
namespace Utils {
    // Template function for converting any type to string
    template <typename T>
    std::string toString(const T& value);
    
    // Convert string to integer with comprehensive validation
    int toInt(const std::string& str);
    
    // Remove leading and trailing whitespace
    std::string trim(const std::string& str);
    
    // Convert string to lowercase (ASCII only)
    std::string toLowerCase(const std::string& str);
}
```

**Key Behaviors**:
- `toString`: Type-safe conversion using `std::ostringstream`, never throws
- `toInt`: Validates entire string consumption, trims whitespace, checks bounds
- `trim`: Removes spaces, tabs, carriage returns, newlines
- `toLowerCase`: ASCII-only case conversion for C++98 compatibility

---

### Logger (Multi-level Logging System)

**Purpose**: Provide a configurable, multi-level logging system with both console and file output capabilities.

**Key Features**:
- Four distinct log levels with ANSI color coding
- Millisecond-precision timestamps
- Configurable minimum log level for filtering
- Optional file output with append mode
- C++98-compatible implementation

#### Data Structures

```cpp
class Logger {
public:
    enum Level {
        DEBUG,    // Detailed debugging information
        INFO,     // General operational messages
        WARN,     // Warning conditions
        ERROR     // Error conditions
    };

private:
    static std::ofstream logfile_;    // File output stream
    static bool use_file_;            // File logging enabled flag
    static Level min_level_;          // Minimum log level threshold
};
```

#### Public Interface

```cpp
class Logger {
public:
    // Initialize logging system with optional file output
    static void init(const std::string& filename = "");
    
    // Cleanup resources and close log file
    static void shutdown();
    
    // Set minimum log level for filtering
    static void setLevel(Level level);
    
    // Get current minimum log level
    static Level getLevel();
    
    // Logging methods for each level
    static void info(const std::string& msg);
    static void warn(const std::string& msg);
    static void error(const std::string& msg);
    static void debug(const std::string& msg);

private:
    // Internal logging implementation
    static void log(Level level, const std::string& msg);
    
    // Convert log level to string representation
    static std::string levelToString(Level level);
    
    // Convert log level to ANSI color code
    static std::string levelToColor(Level level);
};
```

**Log Format**:
```
[2024-01-15 14:30:25.123] [INFO] Server started on port 8080
[2024-01-15 14:30:26.456] [DEBUG] CGI script executed: /cgi/test.py
[2024-01-15 14:30:27.789] [WARN] Client body timeout: 127.0.0.1
[2024-01-15 14:30:28.012] [ERROR] Failed to bind socket: Address already in use
```

**Color Coding**:
- DEBUG: Cyan
- INFO: Green
- WARN: Yellow
- ERROR: Red

---

### configUtils (Configuration Value Parsing)

**Purpose**: Parse configuration values with unit suffixes and provide validation for size and time directives.

**Key Features**:
- Size parsing with binary units (K, M, G)
- Time parsing with standard units (s, m, h)
- Line number tracking for error reporting
- Comprehensive error messages with context

#### Public Interface

```cpp
namespace ConfigUtils {
    // Parse size strings with unit suffixes
    // Throws: std::runtime_error on invalid format
    size_t parseSizeWithUnit(const std::string& sizeStr, int line = 0);
    
    // Parse time strings with unit suffixes
    // Throws: std::runtime_error on invalid format
    int parseTimeWithUnit(const std::string& timeStr, int line = 0);
    
    // Vector construction helpers (C++98 compatibility)
    std::vector<std::string> makeVector(const char* first);
    std::vector<std::string> makeVector(const char* first, const char* second);
    std::vector<std::string> makeVector(const char* first, const char* second, 
                                      const char* third);
}
```

**Supported Units**:
- **Size**: K (1024), M (1048576), G (1073741824)
- **Time**: s (1), m (60), h (3600)

---

### cgiUtils (CGI-specific Utilities)

**Purpose**: Provide specialized utilities for CGI script execution, output parsing, and debugging.

**Key Features**:
- CGI output parsing with header/body separation
- HTTP status code extraction from CGI responses
- Query string generation from parameter maps
- Comprehensive debug information generation

#### Public Interface

```cpp
namespace CGIUtils {
    // Generate URL-encoded query string from parameters
    std::string makeQueryString(const std::map<std::string, std::string>& params);
    
    // Parse CGI script output into structured response
    void parseCGIOutput(const std::string& output, CGIResponse& result);
    
    // Parse Status header line from CGI output
    void parseStatusLine(const std::string& status_line, CGIResponse& result);
    
    // Determine final HTTP status code based on execution results
    void extractHttpStatus(CGIResponse& result);
    
    // Set success flag based on execution results
    void setSuccessFlag(CGIResponse& result);
    
    // Generate detailed debug information for CGI requests
    std::string generateDebugInfo(const CGIRequest& req);
}
```

**CGI Output Parsing**:
- Separates headers from body via double CRLF (`\r\n\r\n`)
- Extracts Status, Content-Type, and custom headers
- Validates required headers (Content-Type)

**Status Determination**:
- `timed_out` → 504 Gateway Timeout
- `exit_code != 0` → 500 Internal Server Error
- `http_status` from Status header or defaults

---

## Integration Patterns

### With 01_config/ (Configuration System)

**Value Parsing**:
```cpp
server.client_max_body_size = ConfigUtils::parseSizeWithUnit("10M", line);
server.cgi_timeout = ConfigUtils::parseTimeWithUnit("30s", line);
```

**Vector Construction**:
```cpp
location.allowed_methods = ConfigUtils::makeVector("GET", "POST", "DELETE");
```

**Logging**:
```cpp
Logger::info("Loaded configuration from " + config_file);
```

### With 02_http/ (HTTP Layer)

**String Conversion**:
```cpp
headers["Content-Length"] = Utils::toString(body.size());
int port = Utils::toInt(req.getHeader("Host").substr(colon_pos + 1));
```

**Header Processing**:
```cpp
std::string normalized = Utils::toLowerCase(header_name);
std::string trimmed_value = Utils::trim(header_value);
```

**Logging**:
```cpp
Logger::debug("Parsed request: " + method + " " + path);
Logger::warn("Invalid header: " + header_line);
```

### With 03_handlers/ (Handler System)

**File Operations**:
```cpp
Logger::info("Serving file: " + file_path);
std::string ext = Utils::toLowerCase(getFileExtension(path));
```

**Error Handling**:
```cpp
Logger::error("File not found: " + resolved_path);
return ErrorHandler(404).handle(ctx);
```

### With 04_cgi/ (CGI Module)

**Output Parsing**:
```cpp
CGIUtils::parseCGIOutput(cgi_stdout, response);
CGIUtils::extractHttpStatus(response);
CGIUtils::setSuccessFlag(response);
```

**Debugging**:
```cpp
Logger::debug(CGIUtils::generateDebugInfo(cgi_request));
```

**Query Strings**:
```cpp
env["QUERY_STRING"] = CGIUtils::makeQueryString(req.parseQueryString());
```

### With 05_session/ (Session Management)

**ID Generation**:
```cpp
std::string session_id = Utils::toString(generateSessionId());
```

**Cookie Parsing**:
```cpp
Cookie cookie = Cookie::parse(cookie_header_value);
```

**Logging**:
```cpp
Logger::info("Session created: " + session_id);
Logger::debug("Session data: " + Utils::toString(session_count));
```

---

## Error Handling Strategy

### Parse Errors

**configUtils**:
- Invalid unit suffixes throw `std::runtime_error` with line numbers
- Non-numeric values generate descriptive error messages
- Empty inputs explicitly rejected

**Utils::toInt**:
- Returns 0 for invalid inputs (non-throwing)
- Bounds checking prevents integer overflow
- Whitespace trimming avoids parsing issues

### Logging Errors

**File Logging**:
- Failed file open logged to stderr but doesn't terminate
- File write errors silently fall back to console-only
- Continues operation even with logging subsystem issues

### CGI Parsing Errors

**Output Parsing**:
- Malformed headers skipped with debug logging
- Missing Status headers fall back to implicit determination
- Continues processing with best-effort parsing

---

## Security Considerations

### Input Validation

**Integer Conversion**:
- `Utils::toInt` validates entire string consumption
- Bounds checking prevents integer overflow
- Whitespace trimming avoids bypass attempts

**Path Safety**:
- No direct filesystem operations in utilities
- Caller responsible for path validation
- No shell command generation

### Logging Security

**Information Disclosure**:
- Debug logging disabled by default in production
- No sensitive data (passwords, tokens) in log messages
- File permissions enforced by logging initialization

### CGI Security

**Output Parsing**:
- No code execution in parsing functions
- Header injection prevention through proper formatting
- Size limits enforced by calling code

---

## Configuration and Customization

### Log Level Control

**Runtime Adjustment**:
```cpp
// Development mode
Logger::setLevel(Logger::DEBUG);

// Production mode
Logger::setLevel(Logger::ERROR);
```

### File Logging

**Configuration Options**:
```cpp
// Console-only
Logger::init();

// File logging
Logger::init("/var/log/webserv.log");

// Custom level with file
Logger::init("debug.log");
Logger::setLevel(Logger::DEBUG);
```

### Unit Extensibility

**Adding Units**:
- Modify `parseSizeWithUnit` for additional size units
- Extend `parseTimeWithUnit` for days, weeks
- Maintain backward compatibility

---

## Summary

The `06_utils/` module provides essential foundational services:

✅ **Comprehensive string utilities** with safety and performance  
✅ **Robust type conversion** with validation  
✅ **Multi-level logging** with filtering and file support  
✅ **Configuration parsing** with unit support  
✅ **CGI utilities** for output parsing and debugging  
✅ **C++98 compatibility** with modern design  
✅ **Header-oriented architecture** for performance  
✅ **Extensive integration** with all server components  

**Key Strengths**:
- Consistent error handling across all utilities
- Performance-optimized inline implementations
- Comprehensive input validation
- Flexible logging with multiple destinations
- Specialized parsing for configuration and CGI

**Integration Excellence**:
- Seamless with configuration system
- Essential for HTTP processing
- Critical for CGI execution
- Foundation for session management

This utilities module forms the backbone of the web server, providing reliable, performant, and safe operations that enable all higher-level functionality while maintaining code consistency and reducing duplication.