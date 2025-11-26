# Web Server Project - 03_handlers Module Documentation

## Overview

The `03_handlers/` module implements the **request processing layer** that transforms HTTP requests into appropriate responses. It serves as the core business logic layer, bridging the HTTP protocol (`02_http/`) with filesystem operations, CGI execution, and session management while using configuration (`01_config/`) for routing and behavior control.

**Key Innovation**: This implementation features a **centralized path resolution system** that pre-resolves file paths once and stores them in the request object, enabling consistent and efficient path handling across all handlers.

**Design Philosophy**: Factory-based handler selection with security-first path resolution, comprehensive error handling, and seamless integration with all server components.

---

## Module Structure

```
03_handlers/
├── Handler.hpp/cpp              # Abstract base + factory + path resolution
├── StaticFileHandler.hpp/cpp    # Serves static files
├── AutoIndexHandler.hpp/cpp     # Generates directory listings  
├── UploadHandler.hpp/cpp        # Handles file uploads via multipart/form-data
├── DeleteHandler.hpp/cpp        # Handles DELETE requests
└── ErrorHandler.hpp/cpp         # Generates error responses
```

**External Handlers** (located in their respective modules):
- `CGIHandler` - `04_cgi/` module
- `SessionDemoHandler` - `05_session/` module

---

## Core Responsibilities

| Responsibility | Description |
|----------------|-------------|
| **Path Resolution** | Centralized, one-time path resolution with comprehensive safety checks |
| **Handler Selection** | Dynamic handler creation via factory pattern based on request context |
| **Static File Serving** | Serve files with proper MIME types, binary support, and caching headers |
| **Directory Listings** | Generate modern, responsive HTML listings with dark/light mode support |
| **File Uploads** | Parse multipart/form-data, validate files, and save with duplicate detection |
| **File Deletion** | Safely remove files with multiple security layers |
| **Error Responses** | Return configured or auto-generated error pages |
| **CGI Delegation** | Identify CGI requests and delegate to CGI module |
| **Session Management** | Provide session utilities for request handling |
| **Method Validation** | Enforce allowed HTTP methods per location configuration |

---

## Key Data Structures

### HandlerContext

Context structure passed to all handlers containing request, configuration, and location information.

```cpp
struct HandlerContext {
    Request& req;                 // Mutable reference (stores resolved path)
    const ServerConfig& config;   // Server configuration  
    const Location* loc;          // Matched location block
    Connection* conn;             // Connection pointer
    CGI* cgi;                     // CGI manager pointer
};
```

### UploadedFile

Represents a file uploaded via multipart form data.

```cpp
struct UploadedFile {
    std::string fileName;         // Original filename
    std::string contentType;      // MIME type from Content-Type header
    std::vector<char> data;       // Binary file data
};
```

### Handler (Abstract Base Class)

Defines the interface for all request handlers with factory and utility methods.

```cpp
class Handler {
public:
    virtual ~Handler();
    virtual Response handle(HandlerContext& ctx) = 0;
    
    // Factory and utility methods
    static Handler* createHandler(HandlerContext& ctx);
    static bool isMethodAllowed(HttpMethod method, 
                               const std::vector<std::string>& allowed);
    static std::string resolvePath(const std::string& request_path, 
                                   HandlerContext& ctx);
    static bool isPathSafe(const std::string& path, const std::string& root);
    static std::string normalizePath(const std::string& path);
    
    // Session management
    static Session* getSessionFromRequest(const Request& req);
    static Cookie createSessionCookie(const Session& session);
    static void destroySession(const Request& req);
    static Session* getOrCreateSession(Request& req, Response& res);

protected:
    void setCommonHeaders(Response& response);
};
```

### StaticFileHandler

Serves static files with proper headers and binary support.

```cpp
class StaticFileHandler : public Handler {
public:
    StaticFileHandler();
    ~StaticFileHandler();
    Response handle(HandlerContext& ctx);

private:
    bool serveFile(const std::string& filePath, Response& res, 
                   std::string method);
};
```

### AutoIndexHandler

Generates styled HTML directory listings.

```cpp
class AutoIndexHandler : public Handler {
public:
    AutoIndexHandler();
    ~AutoIndexHandler();
    Response handle(HandlerContext& ctx);

private:
    std::pair<int, std::string> generateDirectoryListing(const std::string& dirPath, 
                                                        const std::string& requestPath);
};
```

### UploadHandler

Handles file uploads via multipart/form-data encoding.

```cpp
class UploadHandler : public Handler {
public:
    UploadHandler();
    UploadHandler(const std::string& uploadDir);
    ~UploadHandler();
    Response handle(HandlerContext& ctx);

private:
    std::string _uploadDirectory;

    std::vector<UploadedFile> parseMultipart(const Request& request);
    bool saveFile(const UploadedFile& file, std::string& savedPath);
    bool validateFile(const UploadedFile& file, const Location loc);
    std::string generateUniqueFilename(const std::string& original);
};
```

### DeleteHandler

Safely handles DELETE requests for file removal.

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

### ErrorHandler

Generates error responses with configurable or auto-generated pages.

```cpp
class ErrorHandler : public Handler {
public:
    ErrorHandler();
    ErrorHandler(int status);
    ErrorHandler(int status, const std::string& url);
    ~ErrorHandler();
    Response handle(HandlerContext& ctx);

    // Static helpers
    static Response buildErrorResponse(int status, const ServerConfig& config);
    static Response buildResponseWithLocation(int code, const std::string& url);

private:
    int _status;
    std::string _location_url;
};
```

---

## Component Details

### Handler (Base Class)

**Purpose**: Provides the abstract interface for all handlers, implements the factory method for handler selection, and offers centralized path resolution with security validation.

**Key Features**:
- **Factory Pattern**: Analyzes request context to instantiate the appropriate handler type
- **Path Resolution**: Performs one-time path resolution with URL decoding, root combination, and safety validation
- **Method Validation**: Checks if the HTTP method is allowed for the matched location
- **Security Layer**: Validates paths against traversal attacks and enforces root boundaries
- **Session Utilities**: Provides helper methods for session retrieval and creation
- **Common Headers**: Sets standard response headers (Date, Server, Connection)

**Factory Selection Process**:
The factory method evaluates the request context through a hierarchical decision tree. It first checks for special routes (session demo), then validates location existence and method permissions. Access control directives (deny_all, denied_ips, return, redirect) are processed next. For valid requests, it performs path resolution once and stores the result. Then it selects handlers based on: CGI extensions, upload configuration, request method, filesystem object type, and autoindex settings. Any resolution failure returns an appropriate ErrorHandler.

**Path Resolution Process**:
Resolution begins by URL decoding the request path and removing the location prefix for CGI-enabled locations. The method combines the remaining path with the configured document root, converts to absolute path, and validates filesystem safety. For directories, it attempts to locate index files from the location configuration. If no index exists and autoindex is disabled, it rejects the request. All successful resolutions are stored in the request object for subsequent handler use.

**Security Validation**:
Path safety validation ensures the resolved path starts with the document root, prevents parent directory traversal via `../` sequences, blocks partial path matches, and constrains symbolic links within allowed boundaries. This multi-layer approach prevents directory traversal attacks while allowing legitimate path resolution.

### StaticFileHandler

**Purpose**: Serves static files from the filesystem with proper MIME types, binary support, and HTTP caching headers.

**Key Features**:
- **Binary Support**: Opens files in binary mode for images, PDFs, executables, and other non-text content
- **MIME Detection**: Automatically determines Content-Type from file extension
- **Conditional Serving**: Supports both GET (with body) and HEAD (without body) methods
- **Error Handling**: Returns 404 for missing files, 403 for inaccessible files, 500 for system errors
- **Path Reuse**: Uses the pre-resolved path from the request object

**File Serving Process**:
The handler first validates the resolved path exists and is a regular file. It checks read permissions without relying on errno. The file size is determined via filesystem operations, and appropriate headers are set including Content-Type from extension mapping and Content-Length from file size. For GET requests, the file content is read into the response body. HEAD requests receive only headers.

**MIME Type Mapping**:
The handler maps common extensions to MIME types: `.html` → `text/html`, `.css` → `text/css`, `.js` → `application/javascript`, `.jpg` → `image/jpeg`, `.png` → `image/png`, `.pdf` → `application/pdf`. Unknown extensions default to `application/octet-stream`.

### AutoIndexHandler

**Purpose**: Generates modern, visually appealing HTML directory listings when `autoindex on` is configured and no index file exists.

**Key Features**:
- **Modern UI**: Glassmorphism design with gradient backgrounds and adaptive dark/light mode
- **Responsive Layout**: Centers content, works on mobile and desktop
- **File Information**: Shows file sizes (B, KB, MB, GB), types (directory/file), and icons
- **Navigation**: Provides parent directory link and clickable directory entries
- **Security**: Filters hidden files (starting with `.`) and validates all paths
- **Performance**: Caches directory listings in memory, sorts entries alphabetically

**Directory Listing Generation**:
The handler reads directory contents using system directory APIs, collects entries while filtering hidden files, sorts alphabetically, and generates HTML with embedded CSS. Each entry displays an icon (📁 for directories, 📄 for files), name, and formatted size. The design includes a status badge, current path display, and footer with item count.

**File Size Formatting**:
Sizes are formatted with appropriate units: bytes for < 1KB, kilobytes for < 1MB, megabytes for < 1GB, gigabytes for larger files. Values use one decimal place when appropriate.

### UploadHandler

**Purpose**: Handles file uploads via `multipart/form-data` encoding, validating and saving uploaded files to the configured directory.

**Key Features**:
- **Multipart Parsing**: Extracts files from multipart form data with boundary detection
- **File Validation**: Checks filename format, size limits, and required extensions
- **Duplicate Detection**: Skips saving identical files (same size) to prevent duplicates
- **Unique Naming**: Generates unique filenames when conflicts occur
- **Size Limits**: Enforces `client_max_body_size` from location configuration
- **Security**: Sanitizes filenames, blocks path traversal in uploaded names

**Upload Process**:
The handler extracts the boundary marker from Content-Type, splits the request body into parts, and parses each part's headers to extract filename and content type. Each file is validated for name safety (no `..` or path separators), size compliance, and required extension. Valid files are saved with unique names; duplicates are detected by size comparison and skipped. After processing, the handler generates an HTML response listing successfully uploaded files with download links. The connection is closed after upload to prevent multipart boundary corruption in keep-alive scenarios.

**Validation Rules**:
Filenames must not contain `..`, `/`, or `\` sequences. Files must have extensions. Size must not exceed location's `client_max_body_size`. Content type is determined from filename extension if not provided in multipart headers.

### DeleteHandler

**Purpose**: Safely handles DELETE requests for file removal with multiple security layers.

**Key Features**:
- **Multi-Layer Safety**: Validates deletion through several independent checks
- **Path Validation**: Ensures target is a regular file within document root
- **System Protection**: Blocks deletion from critical system directories
- **Web Protection**: Prevents deletion of important web files (index.*)
- **Permission Check**: Validates write access before attempting deletion

**Deletion Process**:
The handler verifies the file exists and is a regular file (not directory). It performs safety checks ensuring the path is within server root and not in protected locations (system directories, error pages). Write permission is validated. If all checks pass, the file is deleted via system `remove()`. Success returns 204 No Content; failures return appropriate error codes (404 for not found, 403 for forbidden, 500 for system errors).

**Safety Layers**:
1. **Path Safety**: Validates against traversal attacks using `isPathSafe()`
2. **System Protection**: Blocks `/etc/`, `/bin/`, `/usr/` directories
3. **Web Protection**: Prevents deletion of files matching `index.*` patterns
4. **Type Validation**: Ensures target is a regular file, not directory or special file
5. **Permission Check**: Validates write access before deletion attempt

### ErrorHandler

**Purpose**: Generates appropriate HTTP error responses with configurable custom pages or auto-generated HTML.

**Key Features**:
- **Custom Pages**: Supports server-configured error pages via `error_pages` directive
- **Default Fallback**: Uses `assets/error_pages/{code}.html` if configured page missing
- **Auto-Generation**: Creates minimal HTML error pages for unconfigured codes
- **Location Support**: Handles redirects via 301/302 status codes with Location header
- **Status Validation**: Only generates responses for supported status codes

**Error Page Resolution**:
The handler first checks the server configuration's `error_pages` map for a custom page path. If configured and the file exists, it serves that page. Otherwise, it attempts to load from `assets/error_pages/{status}.html`. If no default page exists, it generates a minimal HTML page with the status code, message, and a "Return Home" link.

**Redirect Handling**:
For redirect scenarios (e.g., `return 301 /new-location`), the handler sets the Location header with the target URL and returns an empty body. The status code determines whether it's a permanent (301) or temporary (302) redirect.

---

## Path Resolution System

### Centralized Resolution Strategy

The module resolves filesystem paths exactly once during handler creation, storing the result in the request object. This approach eliminates redundant filesystem operations, ensures consistency across handlers, and provides a single point for security validation.

**Resolution Steps**:
1. Extract path from request URI, removing query string
2. URL decode percent-encoded characters
3. For CGI locations, strip the location prefix from the path
4. Combine with configured document root
5. Convert to absolute filesystem path
6. Verify file/directory existence and type
7. For directories, attempt to locate index files
8. Validate path safety against traversal attacks
9. Store final resolved path in request object

### Security Validation

The `isPathSafe()` method validates resolved paths against the document root boundary. It normalizes both paths, verifies the resolved path starts with the root directory, and ensures the character following the root prefix is a path separator. This prevents partial path matches and traversal attempts.

**Example Protection**:
```
Request: GET /static/../../../etc/passwd
Decoded: /static/../../../etc/passwd
After root combination: /var/www/../../../etc/passwd
Normalized: /etc/passwd
Safety Check: FAIL (does not start with /var/www)
Result: 403 Forbidden
```

---

## Handler Selection Flow

### Factory Decision Tree

The factory method evaluates the request context through a hierarchical decision process:

1. **Special Routes**: Check for `/session*` paths and delegate to SessionDemoHandler
2. **Location Validation**: Verify location exists; return 404 if not found
3. **Method Validation**: Check if method is in location's `allowed_methods`; return 405 if not allowed
4. **Access Control**: Process `deny_all`, `denied_ips`, `return`, and `redirect_url` directives
5. **Body Size Check**: Validate Content-Length against `client_max_body_size` for POST/PUT
6. **Path Resolution**: Resolve filesystem path once, store in request object
7. **CGI Detection**: Check file extension against `cgi_extensions`; delegate to CGIHandler if matched
8. **Upload Detection**: For POST with `upload_enable`, create UploadHandler
9. **Filesystem Type Check**: 
   - Directory: Return AutoIndexHandler if enabled, otherwise check for index files
   - File: Return StaticFileHandler for GET/HEAD, DeleteHandler for DELETE
10. **Fallback**: Return 404 ErrorHandler if no handler matches

---

## Integration with Other Modules

### With 02_http/ (HTTP Layer)

**Request Object**: Handlers receive a mutable Request reference to retrieve headers, body, cookies, and path information. The path resolution system stores resolved paths via `setResolvedPath()` for downstream handlers.

**Response Object**: Handlers build responses by setting status codes, headers, and body content. The Response object supports automatic header generation and cookie serialization.

**HttpUtils**: Handlers use utility methods for method conversion, URL decoding, MIME type detection, and status message lookup.

### With 01_config/ (Configuration)

**Location Configuration**: Each location block provides:
- `root`: Document root directory
- `allowed_methods`: HTTP method whitelist
- `index_files`: Default files for directories
- `autoindex`: Directory listing enable/disable
- `upload_enable`: Upload handling activation
- `upload_dir`: Upload destination path
- `client_max_body_size`: Maximum request body size
- `cgi_enable`: CGI processing activation
- `cgi_extensions`: Recognized CGI file types
- `error_pages`: Custom error page mappings
- `return`/`redirect_url`: Access control directives

### With 04_cgi/ (CGI Module)

**CGIHandler Instantiation**: The factory creates CGIHandler when:
- Requested file extension matches `cgi_extensions`
- File exists and is executable
- Location has `cgi_enable` set to true
- Path resolution succeeds

**CGI Context**: The HandlerContext includes a CGI manager pointer and connection pointer for asynchronous execution management.

### With 05_session/ (Session Management)

**SessionDemoHandler**: Demonstrates session functionality via `/session*` routes. The base Handler class provides session utilities:
- `getSessionFromRequest()`: Retrieve existing session from cookies
- `getOrCreateSession()`: Retrieve or create new session and set cookie
- `createSessionCookie()`: Generate properly formatted session cookie
- `destroySession()`: Remove session from manager

### With 00_core/ (Connection Management)

**Connection State**: Handlers for CGI requests work with the WAITING_FOR_CGI connection state. The HandlerContext provides direct access to the Connection object for state transitions and timeout management.

---

## Security Considerations

### Path Traversal Protection

The path resolution system implements multiple security layers:
- **URL Decoding**: Handles percent-encoded sequences before validation
- **Root Boundary Enforcement**: Ensures resolved path starts with document root
- **Parent Directory Detection**: Blocks `../` sequences that escape root
- **Partial Path Protection**: Validates the character after root prefix is a separator
- **Symbolic Link Constraints**: Prevents symlink exploitation within allowed boundaries

### Upload Security

UploadHandler implements comprehensive validation:
- **Filename Sanitization**: Removes path separators and traversal sequences from uploaded filenames
- **Size Enforcement**: Compares file size against location's `client_max_body_size`
- **Extension Requirement**: Rejects files without extensions
- **Duplicate Detection**: Skips identical files to prevent overwrite attacks
- **MIME Type Validation**: Determines content type from extension if not provided
- **Connection Close**: Forces connection close after upload to prevent buffer corruption

### Delete Security

DeleteHandler uses defense-in-depth with multiple independent checks:
- **Path Safety Validation**: Reuses `isPathSafe()` to ensure deletion target is within document root
- **System Directory Protection**: Explicitly blocks deletion from `/etc/`, `/bin/`, `/usr/`
- **Web File Protection**: Prevents deletion of `index.*` files and error page directories
- **Type Validation**: Verifies target is a regular file (not directory, symlink, or special file)
- **Write Permission Check**: Validates filesystem permissions before deletion attempt
- **Return Code Validation**: Uses 404 for not found, 403 for forbidden, 500 for system errors

### Access Control Execution

The factory processes security directives in strict order:
1. **IP Denial**: Checks client IP against `denied_ips` list first
2. **Global Deny**: Respects `deny_all` flag to block entire location
3. **Redirects**: Processes `redirect_url` for HTTP redirects
4. **Return Codes**: Enforces `return` directives for HTTP responses
5. **Method Validation**: Verifies method is in `allowed_methods` whitelist

This ordering ensures security policies take precedence over content serving.

### Method Whitelisting

Each location explicitly defines allowed methods. The factory rejects requests with methods not in the whitelist before any handler creation, preventing unintended access patterns.

---

## Key Design Decisions

### Why Centralized Path Resolution?

**Decision**: Resolve filesystem paths exactly once in the factory method and store in the request object.

**Rationale**:
- **Performance**: Eliminates redundant filesystem `stat()` calls across handlers
- **Consistency**: All handlers use identical path information
- **Security**: Single validation point prevents bypass attempts
- **Debugging**: Simplifies path-related issue diagnosis
- **Maintainability**: Path logic changes affect only one location

**Trade-off**: Slightly increases factory complexity, but significantly simplifies individual handlers and improves overall system reliability.

### Why Mutable Request Reference?

**Decision**: Pass mutable Request reference in HandlerContext to store resolved path.

**Rationale**: Request is the natural container for request-related data. Adding resolved path there maintains logical data grouping. Alternatives (separate context field) would fragment request information.

### Why Close Connection After Upload?

**Problem**: Multipart boundaries can leave residual data in the connection buffer, corrupting subsequent requests on keep-alive connections.

**Decision**: Force `Connection: close` after processing uploads.

**Trade-off**: Loses keep-alive efficiency for upload endpoints, but guarantees connection state integrity and prevents hard-to-debug multipart parsing errors.

### Why Pre-Validate Before CGIHandler?

**Decision**: Factory validates CGI script existence and executability before creating CGIHandler.

**Rationale**:
- **Early Error Detection**: Returns 404 immediately rather than during CGI execution
- **Resource Efficiency**: Avoids spawning handler objects for invalid requests
- **Clear Separation**: CGI module focuses on execution; factory handles routing logic
- **Better Error Messages**: File existence errors are clearer than CGI execution failures

### Why Size-Based Duplicate Detection?

**Decision**: Detect duplicate uploads by comparing file sizes rather than content hashes.

**Rationale**:
- **Performance**: Size check is O(1) vs O(n) for hash computation
- **Effectiveness**: Size collisions are rare for user-uploaded content
- **Simplicity**: Avoids cryptographic hash dependencies
- **Practicality**: Balances accuracy with performance for typical use cases

**Limitation**: Files with identical sizes but different content will be treated as duplicates. Acceptable trade-off for file upload scenarios.

---

## Testing Considerations

### Path Resolution Tests
- URL encoding scenarios (`%20`, `%2F`, `%2E%2E`)
- Path traversal attempts (`../`, `../../`, mixed encodings)
- Symbolic link resolution within and outside root
- Root boundary edge cases (root itself, immediate subdirectories)
- Index file fallback behavior
- CGI location prefix stripping

### Upload Tests
- Single and multiple file uploads in one request
- Binary files (images, PDFs, executables)
- Large files near `client_max_body_size` limit
- Invalid filenames (`../file.txt`, absolute paths)
- Missing or malformed multipart boundaries
- Duplicate upload detection
- Content-Type with and without boundary parameter

### Delete Tests
- Existing file deletion success cases
- Non-existent file attempts (404)
- Directory deletion attempts (must fail)
- Protected path attempts (403)
- Symbolic link deletion
- Permission denied scenarios
- Concurrent deletion attempts

### Error Page Tests
- Configured custom error pages (200-level success)
- Missing configured pages (fallback to default)
- Missing default pages (auto-generation)
- Redirect responses (301/302 with Location header)
- All supported HTTP status codes

### Static File Tests
- Text files (HTML, CSS, JS)
- Binary files (images, videos, PDFs)
- GET vs HEAD method differences
- MIME type detection accuracy
- Large file performance and memory usage
- Non-existent files (404)
- Inaccessible files (403)

### Handler Factory Tests
- Session route detection
- Location matching
- Method validation (405 scenarios)
- Access control (deny_all, denied_ips)
- Redirect and return directive processing
- Handler type selection for all combinations

---

## Summary

The `03_handlers/` module provides a robust, secure, and efficient request handling system through:

✅ **Centralized path resolution** for consistency and performance  
✅ **Factory pattern** for flexible, maintainable handler selection  
✅ **Multi-layer security** for file operations and path access  
✅ **Modern UI** for directory listings with adaptive theming  
✅ **Comprehensive error handling** with configurable pages  
✅ **Binary-safe file operations** for all content types  
✅ **Session management integration** for stateful applications  
✅ **Protocol compliance** with proper HTTP semantics  

**Key Strengths**:
- **Single Path Resolution**: Eliminates redundancy and ensures consistency
- **Security-First Design**: Defense-in-depth for all file operations
- **Extensible Architecture**: Clean factory pattern for new handler types
- **Integration Excellence**: Seamless connection with all server components

**Integration Points**:
- HTTP layer for request/response handling
- Configuration system for behavior control
- CGI module for dynamic content execution
- Session management for stateful operations
- Filesystem for static content serving

This handler system forms the core business logic of the web server, providing a solid foundation for web application processing while maintaining the security and performance requirements of a production environment.