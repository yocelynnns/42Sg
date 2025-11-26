# Web Server Project - 01_config Module Documentation

## Overview

The `01_config/` module is responsible for **loading, parsing, and validating server configuration** from Nginx-style configuration files. It provides a **hierarchical configuration tree** (Events → HTTP → Server → Location) that defines all aspects of server behavior: listening addresses, file serving, request handling, resource limits, security policies, **CGI configuration**, and **access control**.

**Design Philosophy**: Nginx-inspired syntax with comprehensive validation, safe defaults, clear inheritance chains, and **robust error reporting with line numbers**.

---

## Module Structure

```
01_config/
├── Config.hpp/cpp          # Configuration storage and management
├── ConfigParser.hpp/cpp    # Lexer and parser implementation
└── configUtils.hpp/cpp     # Value parsing utilities (time/size units)
```

---

## Core Responsibilities

| Responsibility | Description |
|----------------|-------------|
| **File Parsing** | Read and tokenize Nginx-style configuration files |
| **Hierarchy Building** | Construct events, http, server, and location objects with proper nesting |
| **Validation** | Ensure syntax, semantic correctness, and value constraints |
| **Default Application** | Apply safe fallbacks with inheritance from parent contexts |
| **Runtime Access** | Efficient configuration lookup for handlers and connection management |
| **Unit Handling** | Parse time (s, ms) and size (K, M, G) values with validation |
| **Access Control** | Parse `deny` and `return` directives for security and routing |

---

## Configuration Hierarchy

### Structure Diagram

```
GlobalConfig
    ├── EventsConfig (global defaults)
    │   ├── connection_timeout
    │   ├── max_connections
    │   ├── cgi_timeout
    │   └── cgi_max_processes
    │
    └── HttpConfig
        └── ServerConfig[] (multiple servers)
            ├── host, port (listen address)
            ├── server_name (virtual host)
            ├── default_root (document root)
            ├── client_max_body_size
            ├── connection_timeout
            ├── client_header_timeout
            ├── client_body_timeout
            ├── cgi_timeout
            ├── cgi_max_processes
            ├── upload_dir
            ├── error_pages (status → file)
            ├── return_code, return_url
            ├── deny_all, denied_ips
            │── sessions_enabled, session_timeout, session_cookie_name
            │
            └── Location[] (URL path routing)
                ├── path (URL prefix)
                ├── root (document root override)
                ├── allowed_methods (GET, POST, DELETE)
                ├── autoindex (directory listing)
                ├── upload_enable, upload_dir
                ├── cgi_enable, cgi_ext, cgi_pass, cgi_path
                ├── cgi_timeout, cgi_max_processes
                ├── client_max_body_size (override)
                ├── return_code, return_url
                ├── deny_all, denied_ips
```

### Inheritance Flow

Values cascade from global to specific contexts:

```
EventsConfig (broadest)
    ↓
ServerConfig (per virtual host)
    ↓
Location (most specific, per URL path)
```

**Inheritance Rules**:
- `cgi_timeout`/`cgi_max_processes`: events → server → location
- `client_max_body_size`: server → location (location can override)
- `upload_dir`: server → location → global default (`./assets/upload`)
- `return_code`/`return_url`: server → location (location can override)
- `deny_all`/`denied_ips`: server → location (location can override)
- `connection_timeout`: events → server

---

## Key Data Structures

### GlobalConfig

Root of the configuration tree.

```cpp
struct GlobalConfig {
    EventsConfig events;        // Global event settings
    HttpConfig http;            // HTTP configuration block
    bool has_events;            // Events block was defined
    bool has_http;              // HTTP block was defined
};
```

### EventsConfig

Global settings for connection management and CGI defaults.

```cpp
struct EventsConfig {
    int connection_timeout;     // Global connection idle timeout (seconds)
    size_t max_connections;     // Global max concurrent connections
    int cgi_timeout;            // Global CGI script timeout (seconds)
    int cgi_max_processes;      // Global max concurrent CGI processes
};
```

**Defaults**:
- `connection_timeout`: 60 seconds
- `max_connections`: 1024
- `cgi_timeout`: 30 seconds
- `cgi_max_processes`: 10

### HttpConfig

Container for all server blocks.

```cpp
struct HttpConfig {
    std::vector<ServerConfig> servers;  // All defined servers
};
```

### ServerConfig

Represents a virtual host with its own settings, timeouts, and access control.

```cpp
struct ServerConfig {
    // Network
    std::string host;                       // Listen IP ("0.0.0.0", "127.0.0.1")
    int port;                               // Listen port (8080, 80)
    std::vector<std::string> server_names;  // Virtual host names
    
    // File serving
    std::string default_root;               // Document root
    std::vector<std::string> default_index; // Index files (["index.html"])
    std::string upload_dir;                 // Default upload directory
    
    // Limits and Timeouts
    size_t client_max_body_size;            // Request body limit (bytes)
    int connection_timeout;                 // Connection idle timeout
    size_t max_connections;                 // Max concurrent connections
    int client_header_timeout;              // Header read timeout (NEW)
    int client_body_timeout;                // Body read timeout (NEW)
    
    // CGI Configuration
    int cgi_timeout;                        // CGI timeout (seconds)
    int cgi_max_processes;                  // Max concurrent CGI processes (NEW)
    
    // Error handling
    std::map<int, std::string> error_pages; // Status → custom error page
    
    // Access Control
    int return_code;                        // HTTP return code (NEW)
    std::string return_url;                 // Return/redirect URL (NEW)
    bool deny_all;                          // Deny all access flag (NEW)
    std::vector<std::string> denied_ips;    // Denied IP addresses (NEW)
    
    // Session Management
    bool sessions_enabled;                  // Enable sessions
    int session_timeout;                    // Session timeout (seconds)
    std::string session_cookie_name;        // Session cookie name
    
    // Locations
    std::vector<Location> locations;        // Location blocks
};
```

**Defaults**:
- `client_max_body_size`: 1 MB
- `default_root`: "/var/www/html"
- `default_index`: ["index.html"]
- `session_timeout`: 3600 seconds (1 hour)
- `session_cookie_name`: "SESSIONID"
- `deny_all`: false
- `return_code`: 0 (no return)
- `cgi_max_processes`: inherits from events (10)

### Location

URL path-specific configuration with method restrictions, CGI, and upload settings.

```cpp
struct Location {
    // Path matching
    std::string path;                           // URL path ("/", "/api", "/upload")
    
    // File serving
    std::string root;                           // Document root override
    std::vector<std::string> index_files;       // Index files
    bool autoindex;                             // Directory listing
    
    // HTTP Methods
    std::vector<std::string> allowed_methods;   // ["GET", "POST", "DELETE"]
    
    // Uploads
    bool upload_enable;                         // Enable file uploads (NEW)
    std::string upload_dir;                     // Upload destination
    
    // CGI Configuration
    bool cgi_enable;                            // Enable CGI processing (NEW)
    std::vector<std::string> cgi_extensions;    // [".py", ".php"]
    std::map<std::string, std::string> cgi_interpreters;  // Extension → interpreter
    std::string default_cgi_interpreter;        // Fallback interpreter
    std::string cgi_path;                       // CGI script directory (NEW)
    int cgi_timeout;                            // CGI timeout override
    int cgi_max_processes;                      // Max CGI processes override (NEW)
    
    // Limits
    size_t client_max_body_size;                // Body size override
    
    // Access Control and Redirects
    std::string redirect_url;                   // HTTP redirect target
    int return_code;                            // Return directive code (NEW)
    std::string return_url;                     // Return directive URL (NEW)
    bool deny_all;                              // Deny all access (NEW)
    std::vector<std::string> denied_ips;        // Denied IPs (NEW)
};
```

**Defaults**:
- `allowed_methods`: ["GET", "POST", "DELETE"]
- `autoindex`: false
- `upload_enable`: false
- `upload_dir`: inherits from server or uses `./assets/upload`
- `cgi_enable`: false
- `cgi_timeout`: inherits from server (30s)
- `cgi_max_processes`: inherits from server (10)
- `client_max_body_size`: inherits from server (1MB)
- `deny_all`: false
- `return_code`: 0 (no return)

### Token

Represents a parsed token from the config file.

```cpp
struct Token {
    std::string value;          // Token text ("server", "{", "8080")
    int line;                   // Source line number (for error reporting)
};
```

---

## Component Details

### Config (Storage and Management)

**Purpose**: Store and provide access to the complete parsed configuration with validation, defaults, and **runtime lookup**.

**Key Features**:
- Full configuration hierarchy storage
- Inheritance system for default value propagation
- Copy semantics for safe configuration reloads
- **Efficient server and location lookup functions**
- **Comprehensive validation with detailed error logging**

**Public Interface**:

```cpp
class Config {
public:
    // Constructors
    Config();
    Config(const Config& other);                    // Copy constructor
    Config& operator=(const Config& other);         // Copy assignment
    
    // Load configuration from file, parse, apply defaults, and validate
    // Returns true on success, false on error
    bool load(const std::string& filename);
    
    // Validate entire configuration hierarchy
    // Checks required fields, value ranges, and semantic correctness
    // Returns true if valid, false otherwise
    bool validateConfig() const;
    
    // Apply default values and inheritance rules
    // Called automatically after parsing
    void setDefaults();

    // Accessors
    // Get all configured servers
    const std::vector<ServerConfig>& getServers() const;
    
    // Get global configuration (events and http)
    const GlobalConfig& getGlobalConfig() const;
    
    // **Find server by host and port (virtual host matching)**
    // Returns pointer to ServerConfig or NULL if not found
    // Performs case-insensitive host/server_name matching
    const ServerConfig* findServer(const std::string& host, int port) const;
    
    // **Find best matching location for a path (longest prefix match)**
    // Returns pointer to Location or NULL if no match
    const Location* findLocation(const ServerConfig& server, 
                                const std::string& path) const;

private:
    // Validation helpers
    bool validateServer(const ServerConfig& server) const;
    bool validateLocation(const Location& location) const;
    
    GlobalConfig global_config_;  // Stores entire configuration
};
```

**Server Matching Algorithm** (Case-Insensitive):

```
Find server for request "example.com:8080":
    ↓
Convert request host to lowercase: "example.com"
    ↓
Iterate through all servers:
    ↓
    Convert server.host to lowercase
    ↓
    Check: server.host == "example.com" && server.port == 8080
    ↓
    If no match, check all server.server_names (case-insensitive)
    ↓
    If match: return server
    ↓
If no match: return NULL (caller uses first server as default)
```

**Location Matching Algorithm** (Longest Prefix):

```
Find location for path "/api/users/123":
    ↓
Initialize: best_match = NULL, best_length = 0
    ↓
For each location in server:
    ↓
    Check if path starts with location.path:
        "/api/users/123".find("/api") == 0 → YES
        ↓
        Check if location.path.length() > best_length:
            4 > 0 → YES
            ↓
            Update: best_match = this location, best_length = 4
    ↓
Continue checking other locations (looking for longer matches)
    ↓
Return best_match (most specific location)
```

---

### ConfigParser (Lexer and Parser)

**Purpose**: Parse Nginx-style configuration files into structured objects through tokenization and recursive descent parsing.

**Key Features**:
- Token-based lexing with line number tracking
- Recursive descent parsing for nested blocks
- Context-aware directive validation
- **Comprehensive error reporting with line numbers**
- **Support for new directives and CGI configuration**

**Public Interface**:

```cpp
class ConfigParser {
public:
    ConfigParser();
    
    // Parse configuration file and populate GlobalConfig
    // Returns true on success, false on parse error
    // Logs detailed error messages with line numbers
    bool parseFile(const std::string& filename, GlobalConfig& global_config);

private:
    // Block parsing methods
    bool parseEventsBlock(std::vector<Token>& tokens, size_t& index, 
                         GlobalConfig& global_config);
    bool parseHttpBlock(std::vector<Token>& tokens, size_t& index, 
                       HttpConfig& http, GlobalConfig& global_config);
    bool parseServerBlock(std::vector<Token>& tokens, size_t& index, 
                         ServerConfig& server);
    bool parseLocationBlock(std::vector<Token>& tokens, size_t& index, 
                           Location& location);
    
    // Directive parsing
    // Parses single directive and applies it to appropriate context
    bool parseDirective(const std::vector<Token>& tokens, size_t& index,
                       ServerConfig* server, Location* location, EventsConfig* events);
    
    // Utilities
    // Convert input stream into vector of tokens
    // Handles whitespace, comments (#), and special characters ({ } ;)
    std::vector<Token> tokenize(std::istream& input);
    
    // Validate directive is allowed in current context
    // Throws std::runtime_error if invalid
    void validateDirective(const std::string& directive,
                          const std::vector<std::string>& values,
                          const std::string& context, int line);
};
```

**Parsing Flow**:

```
parseFile(filename)
    ↓
Open file and create input stream
    ↓
tokenize(stream) → vector<Token>
    ↓
Process tokens sequentially:
    ↓
    Token = "events" → parseEventsBlock()
        ↓
        Expect "{"
        ↓
        Parse directives until "}"
        ↓
        Set global_config.has_events = true
    ↓
    Token = "http" → parseHttpBlock()
        ↓
        Expect "{"
        ↓
        Parse directives and server blocks
        ↓
        Set global_config.has_http = true
    ↓
    Token = "server" → parseServerBlock()
        ↓
        Expect "{"
        ↓
        Parse directives and location blocks
        ↓
        Add to http.servers
    ↓
All tokens processed → return true
```

**Tokenization Process**:

```
Input line: "listen 127.0.0.1:8080; # comment"

Processing:
    ↓
Skip whitespace
    ↓
Extract "listen" (non-special characters)
    ↓
Skip whitespace
    ↓
Extract "127.0.0.1:8080" (until special char or whitespace)
    ↓
Extract ";" (special character)
    ↓
Skip comment (from # to end of line)
    ↓
Result: ["listen", "127.0.0.1:8080", ";"]
```

**Special Characters**:
- `{` - Block start
- `}` - Block end
- `;` - Statement terminator
- `#` - Comment start (rest of line ignored)

**Context Validation**:

Each directive is only valid in specific contexts:

| Directive | Valid Contexts | Purpose |
|-----------|----------------|---------|
| `connection_timeout` | events, server | Connection idle timeout |
| `max_connections` | events, server | Max concurrent connections |
| `cgi_timeout` | events, server, location | CGI execution timeout |
| `cgi_max_processes` | events, server, location | Max concurrent CGI processes |
| `listen` | server | Bind address/port |
| `server_name` | server | Virtual host names |
| `root` | server, location | Document root |
| `index` | server, location | Index files |
| `upload_dir` | server, location | Upload directory |
| `client_max_body_size` | server, location | Request body limit |
| `client_header_timeout` | server | Header read timeout |
| `client_body_timeout` | server | Body read timeout |
| `error_page` | server | Custom error pages |
| `return` | server, location | HTTP return/redirect |
| `deny` | server, location | Access control |
| `allowed_methods` | location | HTTP method whitelist |
| `autoindex` | location | Directory listing |
| `upload_enable` | location | Enable file uploads |
| `cgi_enable` | location | Enable CGI processing |
| `cgi_ext` | location | CGI file extensions |
| `cgi_pass` | location | Extension-to-interpreter mapping |

---

### configUtils (Value Parsing)

**Purpose**: Parse configuration values with units and provide validation helpers.

**Key Functions**:

```cpp
namespace ConfigUtils {
    // Parse time value with unit suffix
    // Supports: "30s" (seconds), "500ms" (milliseconds)
    // Returns: value in seconds (as integer)
    // Throws: std::runtime_error on invalid format
    int parseTimeWithUnit(const std::string& value, int line);
    
    // Parse size value with unit suffix
    // Supports: "1M" (megabytes), "512K" (kilobytes), "2G" (gigabytes)
    // Returns: value in bytes
    // Throws: std::runtime_error on invalid format
    size_t parseSizeWithUnit(const std::string& value, int line);
    
    // Helper to create vector from 1-3 strings (for C++98 compatibility)
    // Used for defining allowed contexts in directive validation
    std::vector<std::string> makeVector(const std::string& s1, 
                                       const std::string& s2 = "", 
                                       const std::string& s3 = "");
}
```

**Unit Conversion**:

**Time Units**:
```
"30s"    → 30 seconds
"500ms"  → 0 seconds (integer division truncates)
"1000ms" → 1 second
"2s"     → 2 seconds
```

**Size Units**:
```
"1K"   → 1024 bytes
"1M"   → 1048576 bytes (1024 * 1024)
"10M"  → 10485760 bytes
"1G"   → 1073741824 bytes (1024 * 1024 * 1024)
"512K" → 524288 bytes
```

**Parsing Logic**:

```
Parse "10M":
    ↓
Extract numeric part: "10"
    ↓
Extract unit: "M"
    ↓
Convert numeric: 10
    ↓
Apply multiplier: 10 * 1024 * 1024 = 10485760
    ↓
Return: 10485760 bytes
```

---

## Directive Reference

### Events Block Directives

| Directive | Values | Description | Default |
|-----------|--------|-------------|---------|
| `connection_timeout`| time | Connection idle timeout | 60s |
| `max_connections` | number | Max concurrent connections | 1024 |
| `cgi_timeout` | time | CGI script timeout | 30s |
| `cgi_max_processes`| number | Max concurrent CGI processes | 10 |

### Server Block Directives

| Directive | Values | Description | Default |
|-----------|--------|-------------|---------|
| `listen` | IP:port or port | Listen address | **Required** |
| `server_name` | hostname list | Virtual host names | [] |
| `root` | path | Document root | /var/www/html |
| `index` | file list | Index files | [index.html] |
| `upload_dir` | path | Upload directory | ./assets/upload |
| `client_max_body_size`| size | Request body limit | 1M |
| `connection_timeout`| time | Connection idle timeout | 60s |
| `client_header_timeout`| time | Header read timeout | inherits |
| `client_body_timeout`| time | Body read timeout | inherits |
| `max_connections`| number | Max connections | 1024 |
| `cgi_timeout` | time | CGI timeout | 30s |
| `cgi_max_processes`| number | Max CGI processes | 10 |
| `error_page` | status path | Custom error pages | {} |
| `return` | code [url] | HTTP return/redirect | 0 (none) |
| `deny` | all or IPs | Access control | [] |
| `sessions_enabled`| on/off | Enable sessions | false |
| `session_timeout`| time | Session timeout | 3600s |
| `session_cookie_name`| string | Cookie name | SESSIONID |

### Location Block Directives

| Directive | Values | Description | Default |
|-----------|--------|-------------|---------|
| `root` | path | Document root override | inherits |
| `index` | file list | Index files | inherits |
| `autoindex` | on/off | Directory listing | off |
| `allowed_methods`| method list | HTTP method whitelist | [GET,POST,DELETE] |
| `upload_enable`| on/off | Enable file uploads | off |
| `upload_dir` | path | Upload destination | inherits |
| `cgi_enable` | on/off | Enable CGI processing | off |
| `cgi_ext` | extension list | CGI extensions (e.g., .py) | [] |
| `cgi_pass` | interpreter OR ext interpreter | Interpreter mapping | see below |
| `cgi_path` | path | CGI script directory | "" |
| `cgi_timeout` | time | CGI timeout override | inherits |
| `cgi_max_processes`| number | Max CGI processes | inherits |
| `client_max_body_size`| size | Body size override | inherits |
| `return` | code [url] | Return/redirect | inherits |
| `deny` | all or IPs | Access control | inherits |

**CGI Pass Directive Formats**:
```
cgi_pass /usr/bin/python3;              // Set default interpreter
cgi_pass .py /usr/bin/python3;          // Map extension .py
cgi_pass .php /usr/bin/php-cgi;         // Map extension .php
```

---

## Inheritance and Default Application

### Default Value Cascade

**Inheritance Chain**:

```
1. Hard-coded defaults in Config.cpp
    ↓
2. EventsConfig (global defaults)
    ↓
3. ServerConfig (server-specific)
    ↓
4. Location (most specific)
```

### Default Application Process

```
After parsing completes:
    ↓
Call Config::setDefaults()
    ↓
For EventsConfig:
    If connection_timeout == 0 → 60
    If max_connections == 0 → 1024
    If cgi_timeout == 0 → 30
    If cgi_max_processes == 0 → 10
    ↓
For each ServerConfig:
    If client_max_body_size == 0 → 1MB
    If default_root empty → "/var/www/html"
    If default_index empty → ["index.html"]
    If connection_timeout == 0 → events.connection_timeout
    If max_connections == 0 → events.max_connections
    If cgi_timeout == 0 → events.cgi_timeout
    If cgi_max_processes == 0 → events.cgi_max_processes
    If client_header_timeout == 0 → inherits
    If client_body_timeout == 0 → inherits
    If upload_dir empty → "./assets/upload"
    ↓
    For each Location:
        If root empty && redirect_url empty → server.default_root
        If index_files empty → server.default_index
        If allowed_methods empty → ["GET","POST","DELETE"]
        If cgi_timeout == 0 → server.cgi_timeout
        If cgi_max_processes == 0 → server.cgi_max_processes
        If client_max_body_size == 0 → server.client_max_body_size
        If upload_dir empty → server.upload_dir or "./assets/upload"
        If return_code == 0 → server.return_code
        If return_url empty → server.return_url
        If !deny_all → server.deny_all
        If denied_ips empty → server.denied_ips
```

---

## Validation Strategy

### Syntax Validation (During Parsing)

**Checks**:
- Valid token sequence (blocks properly opened/closed)
- Semicolons after directives (comprehensive checking)
- Directive allowed in current context
- At least one value for each directive
- Port numbers in valid range (1-65535)
- HTTP methods are GET, POST, or DELETE only

**Error Types**:
- Missing semicolon (with line number)
- Wrong context for directive
- Missing value for directive
- Unexpected token
- Unclosed block
- **Invalid port number** (1-65535)
- **Invalid HTTP method**

### Semantic Validation (After Parsing)

**Checks**:
- Required blocks present (http, at least one server)
- Each server has valid port (1-65535)
- Each server has root directory
- Each location has path
- Each location has at least one handler (root, redirect, or return)

**Validation Flow**:

```
validateConfig()
    ↓
Check servers.size() > 0
    ↓
For each server:
    ↓
    validateServer():
        Check 0 < port <= 65535
        Check default_root not empty
        ↓
        For each location:
            validateLocation():
                Check path not empty
                Check (root || redirect_url || return_code != 0)
                ↓
                If all valid: continue
                If invalid: return false
    ↓
All valid: return true
```

---

## Error Handling

### Parse Errors

| Error Type | Message Format | Cause |
|------------|----------------|-------|
| File Access | "Cannot open config file: X" | File doesn't exist/no permission |
| Syntax Error | "Expected '{' after server at line X" | Missing opening brace |
| Missing Semicolon | "Missing ';' at the end of line X" | Statement not terminated |
| Unknown Directive | "Unknown directive 'X' at line Y" | Typo/unsupported directive |
| Context Violation | "Directive 'X' not allowed in 'Y' context" | Directive in wrong block |
| **Invalid Port** | "Invalid port number 'X' at line Y. Port must be between 1-65535." | Port out of range |
| **Invalid Method** | "Invalid HTTP method 'X' at line Y. Allowed: GET, POST, DELETE" | Unsupported HTTP method |
| **Missing Values** | "Directive 'X' requires values at line Y" | No values provided |

### Validation Errors

| Error Type | Message Format | Cause |
|------------|----------------|-------|
| Missing Required | "No server blocks defined" | HTTP block has no servers |
| Missing Root | "Server missing root directory" | Server has no root directive |
| Invalid Port | "Invalid port number: X" | Port validation failed |
| Location Error | "Location missing root, redirect, or return directive" | Location has no handler |

### Error Recovery

**Strategy**:
- Parse as much as possible before failing
- Report first error encountered with **exact line number**
- Log detailed error messages
- Return false to indicate failure

**No Partial Configuration**:
- If any error occurs, entire config load fails
- Server must have valid configuration to start
- Prevents running with broken configuration

---

## Configuration Integration with Core

### Listening Socket Creation

```
Server::updateListeningSocketsFromConfig():
    ↓
Iterate through global_config.http.servers
    ↓
Deduplicate by host:port pairs
    ↓
Create SocketInfo for each unique listen address
    ↓
Store in listen_sockets_ vector
```

### Timeout Application

```
Server::acceptNewConnection():
    ↓
Find matching server config
    ↓
Extract client_header_timeout
    ↓
conn->setTimeout(timeout_ms)
    ↓
conn->setState(READING_REQUEST)
```

### CGI Configuration Usage

```
Handler::createHandler():
    ↓
Check location.cgi_enable
    ↓
If true and file extension in location.cgi_extensions:
    ↓
Look up interpreter in location.cgi_interpreters
    ↓
Use default_cgi_interpreter if no extension match
    ↓
Apply location.cgi_timeout and cgi_max_processes
    ↓
Create CGI handler
```

---

## Security Considerations

### Path Validation

**Risk**: Malicious paths in configuration could expose system files.

**Mitigation**:
- Validate root directories exist and are accessible
- Ensure upload directories are within document root
- Check CGI script directories don't include sensitive paths

### Access Control Enforcement

**Deny Directives**:
- Properly parsed and stored in config
- Handler must enforce these rules
- IP matching implemented in request processing

**Return Directives**:
- Redirect codes validated (301, 302, 303, 307, 308)
- Error codes validated (400-599)
- URLs sanitized to prevent header injection

### Resource Limits

**Prevent DoS**:
- `client_max_body_size`: prevents excessive memory usage
- `max_connections`: prevents connection exhaustion
- `cgi_timeout`: prevents hung CGI processes
- `cgi_max_processes`: prevents fork bombs
- `client_header_timeout`: prevents slowloris attacks
- `client_body_timeout`: prevents slow uploads

**Safe Defaults**:
- 1 MB body size (reasonable for most requests)
- 1024 max connections (sufficient for moderate load)
- 30s CGI timeout (prevents indefinite hangs)
- 60s connection timeout (balances keep-alive and resources)

### CGI Security

**Interpreter Validation**:
- Ensure interpreter paths are absolute
- Verify interpreters exist and are executable
- Restrict to approved interpreters

**Script Directory Isolation**:
- CGI scripts should be in dedicated directories
- Separate from document root when possible
- Proper permissions (execute but not world-writable)

---

## Integration with Other Modules

### With 00_core/Server

**Usage**:
- Create listening sockets from `server.host` and `server.port`
- Apply connection limits from `max_connections`
- Set timeouts from `connection_timeout`, `client_header_timeout`, `client_body_timeout`
- **Reload configuration on SIGHUP signal**

### With 02_http/Request

**Usage**:
- Enforce `client_max_body_size` during request parsing
- Use timeouts for header and body reading
- Validate request against `allowed_methods`

### With 03_handlers/Handler

**Usage**:
- Match server by Host header and port using `findServer()`
- Find location by longest prefix using `findLocation()`
- Use location configuration for:
  - Document root (`root`)
  - CGI settings (`cgi_enable`, `cgi_ext`, `cgi_pass`, `cgi_path`)
  - Upload settings (`upload_enable`, `upload_dir`)
  - Access control (`deny_all`, `denied_ips`)
  - Error pages (`error_pages`)

### With 04_cgi/CGI

**Usage**:
- Check `location.cgi_enable` flag
- Use `location.cgi_extensions` for file type detection
- Map extensions to interpreters via `location.cgi_interpreters`
- Apply `location.cgi_timeout` and `location.cgi_max_processes`
- Use `location.cgi_path` for script directory

### With 05_session/SessionManager

**Usage**:
- Check `server.sessions_enabled` flag
- Use `server.session_timeout` for expiration
- Use `server.session_cookie_name` for cookie identification

---

## Advanced Topics

### CGI Pass Directive Parsing

**Enhanced Parsing Logic**:

```
parseDirective() for "cgi_pass":
    ↓
If values.size() == 1:
    // Single value: set as default interpreter
    location->default_cgi_interpreter = values[0]
    ↓
Else if values.size() >= 2:
    // Two values: extension → interpreter mapping
    location->cgi_interpreters[values[0]] = values[1]
    ↓
    Example: "cgi_pass .py /usr/bin/python3"
    ↓
    Sets: cgi_interpreters[".py"] = "/usr/bin/python3"
```

### Configuration Reload Safety

**Copy Semantics**:

```
Config& operator=(const Config& other):
    ↓
Deep copy of global_config
    ↓
All servers, locations, and maps copied
    ↓
Safe for rollback during reload
```

---

## Summary

The `01_config/` module provides a **robust, secure configuration system**:

✅ **Nginx-style syntax** for familiarity and ease of use  
✅ **Hierarchical structure** with clear inheritance rules  
✅ **Comprehensive validation** catching errors early (ports, methods, syntax)  
✅ **Safe defaults** ensuring sensible behavior with minimal config  
✅ **Flexible configuration** supporting CGI, uploads, access control  
✅ **Unit support** for time and size values  
✅ **Copy semantics** for safe reloads and rollbacks  
✅ **Detailed error reporting** with exact line numbers  
✅ **Security features**: limits, timeouts, access control  

**New Capabilities**:
- **Per-phase timeouts**: `client_header_timeout`, `client_body_timeout`
- **CGI limits**: `cgi_max_processes` prevents resource exhaustion
- **Access control**: `deny`, `return` directives for security
- **Upload management**: `upload_enable`, `upload_dir`
- **CGI flexibility**: `cgi_enable`, `cgi_path` for fine-grained control

This configuration system enables **flexible, secure, and maintainable** server deployments with comprehensive control over all server behaviors.
