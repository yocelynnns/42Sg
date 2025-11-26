# Web Server Project - 02_http Module Documentation

## Overview

The `02_http/` module implements the **HTTP/1.1 protocol layer** for the webserver, providing robust request parsing, response generation, and protocol utilities. It serves as the critical translation layer between raw TCP data from the core networking module and structured HTTP messages consumed by request handlers. The module handles all HTTP semantics including incremental parsing, chunked transfer encoding, connection management, header normalization, and cookie support.

**Design Philosophy**: RFC 7230/7231 compliant implementation with incremental parsing for real-world network conditions, comprehensive error handling, and strict security boundaries between client input and server operations.

---

## Module Structure

```
02_http/
├── Request.hpp/cpp          # HTTP request representation
├── Response.hpp/cpp         # HTTP response builder  
├── RequestParser.hpp/cpp    # Stateful incremental parser
└── HttpUtils.hpp/cpp        # Protocol utilities and helpers
```

---

## Core Responsibilities

| Responsibility | Description |
|----------------|-------------|
| **Incremental Request Parsing** | Handle arbitrary TCP fragmentation with stateful parser that processes data as it arrives |
| **HTTP/1.1 Compliance** | Implement RFC 7230/7231 including chunked encoding, persistent connections, and header semantics |
| **Response Generation** | Build valid HTTP responses with automatic header management and cookie serialization |
| **Header Normalization** | Provide case-insensitive header operations throughout the stack |
| **URL Processing** | URL decoding for forms/query parameters and MIME type detection for responses |
| **Connection Management** | Detect and implement HTTP keep-alive semantics based on version and headers |
| **Cookie Support** | Parse request cookies and generate response cookies for session management |
| **Security Boundaries** | Validate protocol syntax, enforce size limits, and prevent malformed input from crashing the server |
| **Buffer Management** | Track bytes consumed to enable efficient buffer cleanup and keep-alive support |

---

## Key Data Structures

### HttpMethod & HttpVersion

Protocol enumerations for HTTP methods and versions.

```cpp
enum HttpMethod { 
    GET, POST, DELETE, HEAD, PUT, OPTIONS, UNKNOWN 
};

enum HttpVersion { 
    HTTP_1_0, HTTP_1_1, HTTP_UNKNOWN_VERSION 
};
```

### HttpRequest (Low-Level Protocol Representation)

Raw parsed HTTP request data structure used internally by the parser.

```cpp
struct HttpRequest {
    // Core request line
    HttpMethod method;
    std::string uri;                    // Full URI with query string
    HttpVersion version;
    
    // Headers and body
    std::map<std::string, std::string> headers;
    std::string body;

    // Parsed metadata
    std::string path;                   // URI path without query string
    bool keep_alive;                    // Connection persistence flag
    size_t content_length;              // Length from Content-Length header
    bool is_chunked;                    // Transfer-Encoding: chunked

    // Client and server context
    std::string host;                   // Hostname from Host header
    int port;                           // Server port number
    std::string client_ip;              // Client IP address  
    int client_port;                    // Client port number

    // Path resolution tracking
    std::string resolved_path;          // Absolute filesystem path
    std::string request_path;           // Original client request path

    // Cookies
    std::map<std::string, std::string> cookies;

    HttpRequest();                      // Constructor with safe defaults
};
```

### Request (High-Level Wrapper)

Safe, read-only wrapper providing convenient access to parsed request data with path resolution and client context.

```cpp
class Request {
public:
    explicit Request(const HttpRequest& req);

    // Core request access
    HttpMethod getMethod() const;
    const std::string& getPath() const;
    const std::string& getBody() const;
    std::string getUri() const;

    // Header management (case-insensitive)
    std::string getHeader(const std::string& name) const;
    bool hasHeader(const std::string& name) const;
    const std::map<std::string, std::string>& getAllHeaders() const;

    // Client context
    std::string getHost() const;           // Hostname only from Host header
    int getPort() const;                   // Server port number
    const std::string& getRemoteAddr() const; // Client IP address
    int getRemotePort() const;             // Client port number

    // Path resolution accessors
    void setReqPath(const std::string& path);
    const std::string& getReqPath() const;
    void setResolvedPath(const std::string& path);
    const std::string& getResolvedPath() const;
    bool hasResolvedPath() const;

    // Utilities
    std::string getCookie(const std::string& name) const;
    std::map<std::string, std::string> parseQueryString() const;

private:
    HttpRequest raw; // Underlying parsed request data
};
```

### ParseState (Parser State Machine)

Enumeration of parser states for incremental request processing.

```cpp
enum ParseState {
    PARSING_REQUEST_LINE,    // Reading and parsing request line
    PARSING_HEADERS,         // Reading headers until empty line
    PARSING_BODY,            // Reading body with Content-Length
    PARSING_CHUNKED_BODY,    // Reading chunked transfer-encoded body
    COMPLETE,                // Request fully parsed and ready
    ERROR,                   // Parse error occurred
    UNKNOWN_VERSION          // Unsupported HTTP version detected
};
```

### RequestParser (Incremental Parser)

Stateful parser that processes HTTP requests incrementally from arbitrary TCP fragments.

```cpp
class RequestParser {
public:
    RequestParser();

    // Incremental parsing - feed data and get current state
    ParseState parse(const std::string& data, HttpRequest& request);
    
    // State and error management
    ParseState getState() const;
    std::string getError() const;
    void reset();                          // Reset for new request

    // Consumption tracking for buffer management
    size_t getBytesConsumed() const;
    void resetBytesConsumed();

private:
    ParseState state;                      // Current parser state
    size_t content_length;                 // Expected body length from header
    size_t bytes_read;                     // Bytes read for current body
    std::string error_message;             // Detailed error description
    std::string buffer;                    // Internal buffer for partial data
    size_t bytes_consumed_;                // Total bytes consumed from input

    // Parsing phase implementations
    bool parseRequestLine(const std::string& line, HttpRequest& request);
    bool parseHeader(const std::string& line, HttpRequest& request);
    void parseCookies(HttpRequest& request);
    bool parseChunkedBody(HttpRequest& request);
    static bool shouldKeepAlive(const HttpRequest& req);
};
```

### Response (HTTP Response Builder)

Comprehensive HTTP response construction with automatic headers and cookie support.

```cpp
class Response {
public:
    Response();

    // Core response configuration
    void setStatus(int code);                    // Set status code (validated)
    void setHeader(const std::string& name, const std::string& value);
    void setBody(const std::string& content);
    void setContentType(const std::string& type);
    void setContentLength(size_t length);
    void setKeepAlive(bool status);
    void addDateHeader();

    // Cookie management
    void addCookie(const Cookie& cookie);
    const std::vector<Cookie>& getCookies() const;
    void clearCookies();

    // Header access (case-insensitive)
    const std::string& getHeader(const std::string& name) const;
    bool hasHeader(const std::string& header) const;
    const std::map<std::string, std::string>& getAllHeaders() const;

    // Status and metadata
    int getStatus() const;
    const std::string& getReasonPhrase() const;
    HttpVersion getVersion() const;
    bool isHeadersSent() const;

    // Serialization
    std::string toString() const;               // Complete HTTP response string

private:
    HttpVersion version;
    int status_code;
    std::string reason_phrase;
    std::map<std::string, std::string> headers;
    std::string body;
    bool headers_sent;
    std::vector<Cookie> cookies_;

    // Internal header lookup with normalization
    std::map<std::string, std::string>::const_iterator 
    findHeader(const std::string& name) const;
};
```

### HttpUtils (Protocol Utilities)

Static utility class for HTTP protocol operations, URL handling, and MIME type detection.

```cpp
class HttpUtils {
public:
    // Method conversions
    static HttpMethod stringToMethod(const std::string& str);
    static std::string methodToString(HttpMethod method);
    
    // Header utilities
    static std::string normalizeHeaderName(const std::string& name);
    static std::string getCurrentDate();
    
    // Status and content handling
    static std::string getStatusMessage(int status_code);
    static std::string getMimeType(const std::string& extension);
    
    // URL decoding for forms and query parameters
    static std::string urlDecode(const std::string& str);
};
```

---

## Component Details

### Request (High-Level Wrapper)

**Purpose**: Provide a safe, convenient interface to parsed HTTP request data for handlers while maintaining security boundaries between client input and server operations.

**Key Features**:
- **Read-only access** to underlying HttpRequest data
- **Case-insensitive header lookup** via normalization
- **Path resolution tracking** separating client request from resolved filesystem path
- **Client context preservation** including IP, port, and Host header extraction
- **Query string parsing** into structured key-value pairs

**Header Normalization Strategy**:
- Converts all header names to lowercase for consistent lookup
- Prevents client bypass attempts through case variation
- Applied transparently in `getHeader()` and `hasHeader()` methods

**Path Resolution Security**:
- `request_path`: Original client-specified path (may contain malicious traversal attempts)
- `resolved_path`: Safe, validated filesystem path after handler processing
- Handlers must populate `resolved_path` after validating and sanitizing the request path
- Prevents directory traversal attacks when used correctly

**Query String Parsing**:
- Extracts parameters from URI after `?` character
- Handles `key=value&key2=value2` format
- Does **not** perform URL decoding (use HttpUtils::urlDecode on values if needed)
- Returns empty map if no query string present

### Response (HTTP Response Builder)

**Purpose**: Provide a fluent, comprehensive interface for constructing HTTP responses with automatic header management and cookie serialization.

**Key Features**:
- **Status code validation** against supported codes (200, 201, 204, 301, 302, 304, 400, 403, 404, 405, 413, 500, 501, 502, 503, 504)
- **Automatic header generation** for Date and Content-Length if not explicitly set
- **Case-insensitive header operations** matching request behavior
- **Cookie serialization** to Set-Cookie headers with proper formatting

**Automatic Headers**:
- `Date`: Added by `toString()` if not present (RFC requirement)
- `Content-Length`: Added by `toString()` if body present and header not set
- `Connection`: Set by `setKeepAlive()` based on HTTP version and client capabilities

**Cookie Management**:
- Cookies stored as Cookie objects with name, value, and attributes
- Serialized to Set-Cookie headers during `toString()` conversion
- Supports multiple cookies per response
- Cleared automatically between responses for keep-alive connections

**Header Operations**:
- `setHeader()`: Overwrites existing header or adds new one
- `getHeader()`: Case-insensitive lookup with empty string return if not found
- `hasHeader()`: Case-insensitive existence check
- `findHeader()`: Returns iterator for efficient lookup operations

### RequestParser (Incremental Parser)

**Purpose**: Implement a robust, stateful HTTP parser that handles real-world network fragmentation, chunked encoding, and provides precise consumption tracking for buffer management.

**Key Features**:
- **Incremental processing** works with any TCP fragment size
- **Full chunked transfer encoding** support per RFC 7230
- **Precise consumption tracking** enables efficient buffer cleanup
- **Keep-alive detection** based on HTTP version and Connection header
- **Comprehensive error messages** with context for debugging

**State Machine Operation**:
- Maintains current state across multiple `parse()` calls
- Processes data only when complete lines or chunks available
- Returns current state after each call (may be same state if more data needed)
- `COMPLETE` state indicates request ready for handler processing
- `ERROR` state provides error message via `getError()`

**Chunked Encoding Implementation**:
- Parses chunk size lines in hexadecimal format
- Accumulates chunk data until complete chunk received
- Handles trailing `\r\n` after each chunk
- Terminates on zero-size chunk with optional trailing headers
- Validates chunk sizes against available data to prevent over-read

**Consumption Tracking**:
- `bytes_consumed_` accumulates total bytes processed from input
- Reset via `resetBytesConsumed()` after Connection removes processed data
- Critical for keep-alive to prevent data corruption between requests
- Enables Connection to safely remove only processed bytes from read buffer

**Keep-Alive Detection**:
- HTTP/1.1: Default keep-alive unless `Connection: close` present
- HTTP/1.0: Keep-alive only if `Connection: keep-alive` present
- Parsed during header processing, stored in HttpRequest::keep_alive
- Connection uses this to determine whether to close after response

### HttpUtils (Protocol Utilities)

**Purpose**: Centralize all HTTP protocol utility functions to prevent duplication and ensure consistent implementation across modules.

**Key Features**:
- **Method conversions** between string and enum with UNKNOWN fallback
- **Header normalization** to lowercase for case-insensitive operations
- **RFC-compliant date generation** in GMT format for Date header
- **MIME type detection** from file extensions for Content-Type
- **URL decoding** for percent-encoded data and `+` to space conversion

**Status Message Mapping**:
- Maps common status codes (200, 201, 204, 301, 302, 304, 400, 403, 404, 405, 413, 500, 501, 502, 503, 504) to standard reason phrases
- Returns "Unknown" for unmapped codes
- Used by Response to automatically set reason phrase

**MIME Type Detection**:
- Supports: html, css, js, json, png, jpg/jpeg, gif, txt
- Returns "application/octet-stream" for unknown extensions
- Enables automatic Content-Type setting in handlers

**URL Decoding**:
- Converts `%XX` hexadecimal sequences to characters
- Converts `+` to space (application/x-www-form-urlencoded format)
- Validates hex digits to prevent malformed sequences
- Preserves invalid `%` characters that cannot be decoded

---

## Parser State Machine

### State Transition Diagram

```
PARSING_REQUEST_LINE
    ↓
    [CRLF found, valid request line parsed]
    ↓
PARSING_HEADERS
    ↓
    [Empty line (CRLFCRLF) - end of headers]
    ↓
    ┌─────────────────────────────────────┐
    │ Decision based on transfer encoding │
    └─────────────────────────────────────┘
                    ↓
    ┌───────────────┼───────────────┬───────────────┐
    │               │               │               │
    │ Content-      │ Transfer-     │ No body       │
    │ Length        │ Encoding:     │ indicators    │
    │ present       │ chunked       │               │
    ↓               ↓               ↓               ↓
PARSING_BODY   PARSING_CHUNKED_BODY   → COMPLETE   COMPLETE
    ↓               ↓
    [content_length   [0-size chunk
     bytes read]      received]
    ↓               ↓
COMPLETE        COMPLETE
```

### Error Transitions

Any state → **ERROR**:
- Malformed request line format
- Invalid HTTP version
- Header line without colon separator
- Header line exceeding size limits
- Invalid Content-Length value (non-numeric)
- Malformed chunked encoding format

Any state → **UNKNOWN_VERSION**:
- HTTP version other than 1.0 or 1.1 detected
- Allows server to return 505 HTTP Version Not Supported

### State Persistence

**Between parse() calls**:
- State, buffer, content_length, bytes_read preserved
- Enables processing of partial TCP segments
- Parser only consumes complete, validated data

**Request completion**:
- Caller must call `reset()` before parsing next request on keep-alive connection
- Resets all internal state but preserves error message until reset
- Connection calls `reset()` after sending response and before next read

---

## Request Processing Flow

### Complete Request Lifecycle

```
1. Client Connection
   ↓
   EventLoop detects EVENT_READ
   ↓
   Connection::readData() → read_buf_

2. Incremental Parsing
   ↓
   RequestParser::parse(read_buf_, http_req)
   ↓
   Parser processes complete lines/chunks
   ↓
   Returns current ParseState

3. Buffer Management
   ↓
   Connection consumes parser->getBytesConsumed() bytes
   ↓
   parser->resetBytesConsumed()
   ↓
   Unprocessed data remains for next parse() call

4. Header Processing (when state = PARSING_HEADERS)
   ↓
   Parse Host header → http_req.host and http_req.port
   ↓
   Detect Transfer-Encoding: chunked → http_req.is_chunked
   ↓
   Parse Content-Length → content_length and http_req.content_length
   ↓
   Call shouldKeepAlive() → http_req.keep_alive
   ↓
   Empty line triggers body decision

5. Body Processing
   ↓
   IF Content-Length:
        State = PARSING_BODY
        Read exactly content_length bytes
        ↓
        parseCookies() → http_req.cookies
        State = COMPLETE
   
   ELSE IF Chunked:
        State = PARSING_CHUNKED_BODY
        parseChunkedBody() until 0-size chunk
        ↓
        parseCookies() → http_req.cookies
        State = COMPLETE
   
   ELSE:
        parseCookies() → http_req.cookies
        State = COMPLETE

6. Request Ready
   ↓
   ParseState = COMPLETE
   ↓
   Server creates Request wrapper
   ↓
   Handler processes wrapped request
   ↓
   Handler generates Response

7. Response Generation
   ↓
   Response::toString() → formatted HTTP response
   ↓
   Connection::writeData(response_string)
   ↓
   State = WRITING_RESPONSE

8. Keep-Alive Decision
   ↓
   IF http_req.keep_alive == true:
        Connection::resetParserState()
        ↓
        State = READING_REQUEST
        ↓
        Prepare for next request on same connection
   ELSE:
        Connection::close()
        ↓
        State = CLOSING
```

### Keep-Alive Request Sequence

```
Request 1: GET /page1 HTTP/1.1
           Host: example.com
           ↓
           Parse → COMPLETE → Handler → Response
           ↓
           Keep-Alive: true
           ↓
           resetParserState()
           ↓
Request 2: POST /form HTTP/1.1
           Host: example.com
           Content-Length: 10
           ↓
           Parse → COMPLETE → Handler → Response
           ↓
           Connection: close
           ↓
           Close connection
```

---

## Error Handling

### Parse Error Conditions

| Error Type | Detection Point | Parser State | Error Message Example |
|------------|-----------------|--------------|------------------------|
| **Malformed Request Line** | parseRequestLine() | ERROR | "Invalid request line" |
| **Invalid HTTP Version** | parseRequestLine() | UNKNOWN_VERSION | (none, special state) |
| **Request Line Too Long** | parse() in READING_HEADERS | ERROR | "Request line too long" |
| **Missing Header Colon** | parseHeader() | ERROR | "Invalid header" |
| **Header Too Large** | parseHeader() | ERROR | "Header too large" |
| **Invalid Content-Length** | PARSING_HEADERS body setup | ERROR | (parser handles internally) |
| **Malformed Chunk Size** | parseChunkedBody() | ERROR | (incomplete data, no error yet) |
| **Chunk Size Mismatch** | parseChunkedBody() | ERROR | (waits for more data) |

### Connection-Level Error Responses

**Integration with 00_core error handling**:

```
Parse Error Detected → Parser State = ERROR
    ↓
Server::processReadEvent() detects ERROR state
    ↓
Extract error_message from parser
    ↓
Create ErrorHandler with status 400
    ↓
Handler generates Response with:
    - Status: 400 Bad Request
    - Body: Error details
    - Connection: close
    ↓
Send response
    ↓
Set state = CLOSING
```

**UNKNOWN_VERSION Handling**:
```
UNKNOWN_VERSION state detected
    ↓
Server creates ErrorHandler with status 505
    ↓
Response: 505 HTTP Version Not Supported
    ↓
Connection: close (never keep-alive)
```

### Timeout-Based Errors

**Header Timeout** (from 00_core):
```
State = READING_REQUEST
    ↓
Time elapsed > client_header_timeout
    ↓
Check has_received_data flag
    ↓
IF false: Silent close (no response)
IF true: Send 408 Request Timeout
```

**Body Timeout** (from 00_core):
```
State = PARSING_BODY
    ↓
Time elapsed > client_body_timeout
    ↓
Send 408 Request Timeout
    ↓
Set Connection: close
```

---

## Security Considerations

### Input Validation and Size Limits

**Request Line Limits**:
- Maximum 8192 bytes for request line (`MAX_LINE_SIZE`)
- Prevents buffer overflow and memory exhaustion
- Exceeding limit returns 400 Bad Request

**Header Limits**:
- Individual header name: maximum 1024 bytes
- Individual header value: maximum 8192 bytes
- Total headers: maximum 8192 bytes (`MAX_HEADER_SIZE`)
- Prevents slowloris attacks and memory exhaustion

**Body Size Enforcement**:
- Content-Length validated against `client_max_body_size` from config
- Check performed **before** reading body
- 413 Payload Too Large returned immediately if exceeded
- Prevents resource exhaustion from large uploads

### Path Traversal Prevention

**Request Path vs Resolved Path**:
- `request_path`: Raw client input, potentially malicious (e.g., `/../../etc/passwd`)
- `resolved_path`: After handler validation and sanitization
- Handlers **must** validate paths before setting `resolved_path`
- Document root + path validation prevents filesystem access outside intended scope

**URL Decoding Security**:
- HttpUtils::urlDecode() validates hex digits (`[0-9a-fA-F]`)
- Invalid `%` sequences preserved as literal `%`
- Prevents decoding errors from being treated as successful parsing

### Protocol Compliance as Security

**Strict HTTP Version**:
- Only HTTP/1.0 and HTTP/1.1 supported
- UNKNOWN_VERSION state triggers 505 response
- Prevents protocol downgrade attacks

**Chunked Encoding Validation**:
- Chunk sizes parsed as hexadecimal
- Each chunk must be followed by `\r\n`
- Total body size implicitly limited by connection timeout
- Prevents infinite chunk attacks through timeout enforcement

**Header Name Normalization**:
- All header operations case-insensitive via `normalizeHeaderName()`
- Prevents duplicate header injection through case variation
- Consistent processing regardless of client casing

### Cookie Security

**Request Cookie Parsing**:
- `Cookie` header parsed into key-value map
- Duplicate cookie names preserve last value (browser behavior)
- No validation performed on cookie name/value format
- Handler must validate session IDs and sensitive cookie data

**Response Cookie Generation**:
- Cookie class (from 05_session) handles Set-Cookie formatting
- Supports HttpOnly, Secure, SameSite attributes
- Path and domain restrictions enforced by browser
- Server must set appropriate flags for sensitive cookies

---

## Integration with Other Modules

### With 00_core/Connection and Server

**Data Flow Integration**:
```
Connection::readData() → raw bytes
    ↓
RequestParser::parse() → HttpRequest
    ↓
Request wrapper → HandlerContext
    ↓
Handler::handle() → Response
    ↓
Response::toString() → raw bytes
    ↓
Connection::writeData() → Network
```

**Buffer Management**:
- Parser's `getBytesConsumed()` enables Connection to trim processed data
- Critical for keep-alive: prevents unprocessed data loss between requests
- Connection calls `parser.reset()` after each complete request

**Timeout Configuration**:
- 00_core applies timeouts from 01_config based on parsing state:
  - `client_header_timeout` during PARSING_REQUEST_LINE and PARSING_HEADERS
  - `client_body_timeout` during PARSING_BODY and PARSING_CHUNKED_BODY
- Parser state used by Connection to determine appropriate timeout

### With 01_config/Config

**Size Limit Enforcement**:
- `client_max_body_size` checked against HttpRequest::content_length
- Validation occurs in Server::processReadEvent() **before** reading body
- Prevents parser from consuming excessive memory

**MIME Type Mapping**:
- HttpUtils::getMimeType() provides basic mapping
- Config can override via custom mappings (future enhancement)
- Current mapping covers common web file types

**Connection Timeouts**:
- `client_header_timeout` and `client_body_timeout` from Config
- Applied by Connection based on current parser state
- Enables per-phase timeout policies

### With 03_handlers/Handler System

**Handler Context Creation**:
```
Server::processReadEvent():
    ↓
    IF parser state == COMPLETE:
        Create Request wrapper(http_req)
        ↓
        Match ServerConfig by Host:port
        ↓
        Match Location by path
        ↓
        Create HandlerContext(req, response, config, location)
        ↓
        Handler::createHandler(context)
        ↓
        handler->handle() → modifies Response reference
```

**Path Resolution Handoff**:
- Handler receives Request with `request_path` set
- Handler validates path, checks filesystem, applies location.root
- Handler sets `resolved_path` for file operations
- Prevents handlers from needing to re-parse request line

**Error Handler Integration**:
- Parser errors (ERROR state) → Server creates ErrorHandler(400)
- UNKNOWN_VERSION state → Server creates ErrorHandler(505)
- Body size exceeded → Server creates ErrorHandler(413)
- Timeouts → Server creates ErrorHandler(408)

### With 04_cgi/CGI Module

**CGI Request Processing**:
```
Handler detects CGI script (by extension):
    ↓
Extract interpreter from location.cgi_interpreters
    ↓
Set environment variables from HttpRequest:
    - REQUEST_METHOD → methodToString(http_req.method)
    - QUERY_STRING → parsed from uri
    - CONTENT_LENGTH → http_req.content_length
    - HTTP headers → HTTP_HEADER_NAME format
    ↓
Pass http_req.body as stdin to CGI process
    ↓
CGI stdout becomes Response body
    ↓
Parse CGI-generated Status header for response code
```

**CGI Environment Population**:
- HttpUtils::methodToString() converts method enum to string for CGI
- HttpRequest::uri provides full URI for REQUEST_URI and QUERY_STRING
- HttpRequest::headers iterated and converted to HTTP_* environment variables
- HttpRequest::body passed directly as POST/PUT data

### With 05_session/Cookie

**Request Cookie Parsing**:
```
Request::getCookie():
    ↓
    Access raw.cookies map
    ↓
    Return value or empty string if not found
    ↓
    No validation - SessionManager must validate session IDs
```

**Response Cookie Generation**:
```
Response::addCookie():
    ↓
    Append Cookie object to cookies_ vector
    ↓
Response::toString():
    ↓
    For each cookie: oss << "Set-Cookie: " << cookie.toString() << "\r\n"
    ↓
    Cookie::toString() handles proper formatting and attributes
```

**Session Flow**:
```
Request arrives with Cookie: SESSIONID=abc123
    ↓
Handler calls request.getCookie("SESSIONID")
    ↓
SessionManager::getSession(session_id)
    ↓
If valid: retrieve session data
    ↓
If invalid/expired: create new session
    ↓
Handler adds Set-Cookie with new session ID
    ↓
Response includes session cookie for client
```

---

## Key Design Decisions

### Why Incremental Parsing with State Machine?

**Decision**: Implement stateful parser that processes data incrementally rather than requiring complete requests.

**Rationale**:
- **Network Reality**: TCP delivers data in arbitrary fragments, not message boundaries
- **Efficiency**: Process data as it arrives without blocking for complete request
- **Memory Usage**: Avoid buffering entire large requests before parsing
- **Scalability**: Enables handling many concurrent partially-received requests
- **Timeout Control**: Can enforce per-phase timeouts (headers vs body)

**Trade-offs**:
- More complex state management than line-oriented parser
- Requires careful buffer management in Connection
- Must handle state reset correctly for keep-alive

### Why Separate HttpRequest and Request?

**Decision**: Provide low-level struct (HttpRequest) for parser and high-level class (Request) for handlers.

**Rationale**:
- **Encapsulation**: Parser internals hidden from handlers
- **Immutability**: Request wrapper provides read-only access to prevent handler corruption
- **Convenience**: Wrapper layer adds helper methods without cluttering struct
- **Flexibility**: Can extend wrapper without modifying parser structure
- **Security**: Handlers cannot accidentally modify raw parsed data

**Implementation**:
- HttpRequest: Plain struct with public members, owned by Connection
- Request: Wrapper class with private `raw` member, passed to handlers by const reference

### Why Precise Consumption Tracking?

**Decision**: Track exactly how many bytes parser consumes to enable efficient buffer cleanup.

**Rationale**:
- **Keep-Alive Necessity**: Must remove processed data while preserving partial next request
- **Memory Efficiency**: Prevent read buffer from growing indefinitely with slow clients
- **Data Integrity**: Ensure no data loss or corruption between requests on same connection
- **Debugging**: Precise consumption tracking aids in diagnosing parsing issues

**Implementation**:
- `bytes_consumed_` accumulator in parser
- `getBytesConsumed()` retrieves and resets accumulator
- Connection calls `consumeReadBuffer(consumed_bytes)` after each parse call

### Why Built-in Chunked Encoding Support?

**Decision**: Implement full chunked transfer encoding parser rather than rejecting chunked requests.

**Rationale**:
- **HTTP/1.1 Compliance**: Required by RFC 7230, clients expect support
- **File Uploads**: Modern browsers use chunked for uploads without known size
- **Streaming**: Enables progressive request processing
- **Standards**: Cannot claim HTTP/1.1 support without chunked encoding

**Implementation**:
- Dedicated PARSING_CHUNKED_BODY state
- Hexadecimal chunk size parsing
- Strict CRLF validation after chunks
- Body accumulated in HttpRequest::body same as Content-Length

### Why Case-Insensitive Header Normalization?

**Decision**: Convert all header names to lowercase for storage and comparison.

**Rationale**:
- **RFC Compliance**: HTTP/1.1 states headers are case-insensitive
- **Client Variation**: Different clients (browsers, curl, custom) use different casings
- **Security**: Prevents duplicate header injection through case variation (e.g., `Host` vs `host`)
- **Consistency**: Guarantees predictable behavior regardless of client implementation

**Implementation**:
- HttpUtils::normalizeHeaderName() converts to lowercase
- Applied in Request::getHeader(), Request::hasHeader()
- Applied in Response for header lookups
- All header storage uses original casing (for response generation) but comparison uses normalized form

---

## Summary

The `02_http/` module provides a **robust, RFC-compliant HTTP/1.1 implementation** that serves as the critical translation layer between TCP data and application logic:

✅ **Incremental parsing** handles real-world network fragmentation gracefully  
✅ **State machine design** enables per-phase timeout enforcement  
✅ **Keep-alive support** with proper parser reset between requests  
✅ **Full chunked encoding** implementation for standards compliance  
✅ **Security boundaries** with path separation and input validation  
✅ **Precise buffer management** via consumption tracking  
✅ **Case-insensitive headers** for RFC compliance and security  
✅ **Automatic response headers** (Date, Content-Length) reduce handler complexity  
✅ **Cookie integration** for session management  
✅ **Comprehensive error handling** with proper HTTP status codes  

**Integration Strengths**:
- Seamless integration with 00_core's event-driven architecture
- Clean interface for 03_handlers to process requests
- Configurable limits from 01_config for resource control
- CGI environment population for 04_cgi module
- Cookie parsing/generation for 05_session management

**Production-Ready Features**:
- Memory-safe buffer management prevents leaks
- Size limits protect against DoS attacks
- Per-phase timeouts enable responsive server behavior
- Keep-alive connection reuse reduces overhead
- Standards compliance ensures broad client compatibility

This HTTP layer provides a **stable, efficient, and secure foundation** for building web applications on top of the core networking infrastructure.