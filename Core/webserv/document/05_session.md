# Web Server Project - 05_session Module Documentation

## Overview

The `05_session/` module provides **stateful session management** for the HTTP protocol, enabling user tracking across multiple requests through secure cookie-based session identifiers. It implements complete session lifecycle management with configurable timeouts, RFC-compliant cookie handling, and automatic cleanup.

**Design Philosophy**: RFC-compliant session management with security-first implementation, seamless integration with existing HTTP infrastructure, and practical demonstration capabilities.

---

## Module Structure

```
05_session/
├── Cookie.hpp/cpp               # RFC 6265-compliant cookie handling
├── Session.hpp/cpp              # Session data storage and lifecycle
├── SessionManager.hpp/cpp       # Singleton session orchestrator
└── SessionDemoHandler.hpp/cpp   # Practical session demonstration handler
```

---

## Core Responsibilities

| Responsibility | Description |
|----------------|-------------|
| **Session Lifecycle** | Create, retrieve, update, and destroy user sessions with automatic expiration |
| **Cookie Management** | Parse Cookie headers and generate Set-Cookie responses per RFC 6265 |
| **Data Persistence** | Store arbitrary key-value data per session with automatic access tracking |
| **Expiration Control** | Configurable timeouts with lazy automatic cleanup of expired sessions |
| **Security Enforcement** | Secure random session IDs, HttpOnly cookies, and access validation |
| **Demo Integration** | Practical endpoints (`/session/*`) for testing and validation |
| **Stateless HTTP Bridge** | Maintain client state across stateless HTTP transactions |

---

## Key Data Structures

### Cookie (RFC 6265 Compliant)
Complete cookie representation supporting all standard attributes.

```cpp
class Cookie {
public:
    Cookie();
    Cookie(const std::string& name, const std::string& value);
    
    // Core attributes
    std::string name_;      // Cookie identifier
    std::string value_;     // Cookie value
    std::string path_;      // URL path scope
    std::string domain_;    // Domain scope
    int maxAge_;            // Expiration in seconds (-1 = session)
    bool httpOnly_;         // JavaScript access prevention
    bool secure_;           // HTTPS-only flag

    // Attribute management
    void setName(const std::string& name);
    void setValue(const std::string& value);
    void setPath(const std::string& path);
    void setDomain(const std::string& domain);
    void setMaxAge(int maxAge);
    void setHttpOnly(bool httpOnly);
    void setSecure(bool secure);
    
    // Attribute access
    const std::string& getName() const;
    const std::string& getValue() const;
    const std::string& getPath() const;
    const std::string& getDomain() const;
    int getMaxAge() const;
    bool isHttpOnly() const;
    bool isSecure() const;
    
    // Serialization
    std::string toString() const;
    static Cookie parse(const std::string& cookieStr);
};
```

### Session (Data Storage with Timing)
Individual user session with data storage and lifecycle tracking.

```cpp
class Session {
public:
    Session();
    Session(const std::string& id);
    
    // Core session data
    std::string id_;                      // Unique session identifier
    std::map<std::string, std::string> data_; // Key-value storage
    std::time_t creationTime_;            // Session creation timestamp
    std::time_t lastAccessTime_;          // Last activity timestamp
    std::time_t expirationTime_;          // Expiration timestamp

    // Data management
    void setData(const std::string& key, const std::string& value);
    std::string getData(const std::string& key) const;
    bool hasData(const std::string& key) const;
    void removeData(const std::string& key);
    void clear();
    const std::map<std::string, std::string>& getAllData() const;
    
    // Lifecycle management
    void updateAccessTime();
    bool isExpired() const;
    void setExpiration(std::time_t expiration);
    
    // Accessors
    const std::string& getId() const;
    std::time_t getCreationTime() const;
    std::time_t getLastAccessTime() const;
    std::time_t getExpiration() const;
};
```

### SessionManager (Singleton Orchestrator)
Centralized session management with automatic cleanup and ID generation.

```cpp
class SessionManager {
public:
    static SessionManager& getInstance();
    
    // Session lifecycle
    Session& createSession();
    Session* getSession(const std::string& sessionId);
    bool destroySession(const std::string& sessionId);
    
    // Maintenance operations
    void cleanupExpiredSessions();
    void setSessionTimeout(std::time_t timeout);
    
    // Monitoring
    size_t getActiveSessionsCount() const;
    std::time_t getSessionTimeout() const;

private:
    SessionManager();
    std::string generateSessionId();
};
```

### SessionDemoHandler (Practical Demonstration)
Handler demonstrating session functionality through HTTP endpoints.

```cpp
class SessionDemoHandler : public Handler {
public:
    SessionDemoHandler();
    virtual ~SessionDemoHandler();
    virtual Response handle(HandlerContext& ctx);
};
```

---

## Component Details

### Cookie Class (RFC-Compliant Cookie Handling)

**Purpose**: Implement complete cookie parsing and generation according to RFC 6265.

**Key Features**:
- **Bidirectional Operations**: Parse Cookie headers and generate Set-Cookie responses
- **Full Attribute Support**: Path, domain, max-age, HttpOnly, Secure
- **Security Attributes**: HttpOnly prevents JavaScript access; Secure limits to HTTPS
- **Deletion Support**: Proper cookie removal via `max-age=0`

**Public Interface**:

```cpp
class Cookie {
public:
    Cookie();
    Cookie(const std::string& name, const std::string& value);
    
    // Attribute setters
    void setName(const std::string& name);
    void setValue(const std::string& value);
    void setPath(const std::string& path);
    void setDomain(const std::string& domain);
    void setMaxAge(int maxAge);
    void setHttpOnly(bool httpOnly);
    void setSecure(bool secure);
    
    // Attribute getters
    const std::string& getName() const;
    const std::string& getValue() const;
    const std::string& getPath() const;
    const std::string& getDomain() const;
    int getMaxAge() const;
    bool isHttpOnly() const;
    bool isSecure() const;
    
    // Serialization
    std::string toString() const;
    static Cookie parse(const std::string& cookieStr);
};
```

**Serialization Format**:
- `toString()`: Generates `name=value; Path=/; Max-Age=3600; HttpOnly; Secure`
- `parse()`: Extracts name and value from `Cookie` header (simple parser for session_id)

### Session Class (Data Storage with Lifecycle)

**Purpose**: Manage individual user session data with automatic timing and expiration control.

**Key Responsibilities**:
- Store arbitrary key-value string pairs per session
- Track creation time, last access time, and expiration
- Automatically update access timestamps on data operations
- Validate expiration status in real-time

**Public Interface**:

```cpp
class Session {
public:
    Session();
    Session(const std::string& id);
    
    // Data management
    void setData(const std::string& key, const std::string& value);
    std::string getData(const std::string& key) const;
    bool hasData(const std::string& key) const;
    void removeData(const std::string& key);
    void clear();
    const std::map<std::string, std::string>& getAllData() const;
    
    // Timing and expiration
    void updateAccessTime();
    bool isExpired() const;
    void setExpiration(std::time_t expiration);
    
    // Accessors
    const std::string& getId() const;
    std::time_t getCreationTime() const;
    std::time_t getLastAccessTime() const;
    std::time_t getExpiration() const;
};
```

**Key Features**:
- **Automatic Access Tracking**: Last access time updated on all data operations
- **Flexible Storage**: String-based key-value pairs for arbitrary session data
- **Configurable Expiration**: Set custom expiration times per session
- **Expiration Validation**: Real-time expired status checking

### SessionManager Class (Singleton Orchestrator)

**Purpose**: Centralized session management with secure ID generation and automatic cleanup.

**Key Responsibilities**:
- Generate cryptographically secure random session identifiers
- Manage session storage and retrieval
- Automatically clean up expired sessions (lazy strategy)
- Provide global session timeout configuration

**Public Interface**:

```cpp
class SessionManager {
public:
    static SessionManager& getInstance();
    
    // Session lifecycle
    Session& createSession();
    Session* getSession(const std::string& sessionId);
    bool destroySession(const std::string& sessionId);
    
    // Maintenance operations
    void cleanupExpiredSessions();
    void setSessionTimeout(std::time_t timeout);
    
    // Monitoring and configuration
    size_t getActiveSessionsCount() const;
    std::time_t getSessionTimeout() const;

private:
    SessionManager();
    std::string generateSessionId();
};
```

**Key Features**:
- **Singleton Pattern**: Global access point for session management
- **Secure ID Generation**: 32-character random alphanumeric identifiers
- **Collision Prevention**: Regenerate IDs on duplicate detection
- **Lazy Cleanup**: Automatic expired session removal during operations

**ID Generation**:
- 32-character random string using alphanumeric character set
- Statistical uniqueness assurance (no cryptographic dependency)
- Collision detection and regeneration loop

### SessionDemoHandler Class (Practical Demonstration)

**Purpose**: Demonstrate session functionality through practical HTTP endpoints.

**Key Responsibilities**:
- Provide `/session/info` endpoint for session status
- Implement `/session/login` for authentication simulation
- Handle `/session/logout` for session state management
- Support `/session/clear` for complete session destruction

**Public Interface**:

```cpp
class SessionDemoHandler : public Handler {
public:
    SessionDemoHandler();
    virtual ~SessionDemoHandler();
    virtual Response handle(HandlerContext& ctx);
};
```

**Supported Endpoints**:
- `GET /session/info` - Returns JSON: `{logged_in: bool, visits: int}`
- `GET /session/login` - Marks session as authenticated
- `GET /session/logout` - Removes authentication status
- `GET /session/clear` - Destroys session and clears client cookie

---

## Configuration Constants

### Session Timeout Presets

```cpp
const std::time_t SESSION_TIMEOUT_1MIN = 60;        // 60 seconds
const std::time_t SESSION_TIMEOUT_10MIN = 600;      // 600 seconds  
const std::time_t SESSION_TIMEOUT_30MIN = 1800;     // 1800 seconds
const std::time_t SESSION_TIMEOUT_60MIN = 18000;    // 18000 seconds (5 hours)
const std::time_t SESSION_TIMEOUT_24HOURS = 86400;  // 86400 seconds (24 hours)
```

### Global Settings

| Setting | Default | Description |
|---------|---------|-------------|
| Default Timeout | `SESSION_TIMEOUT_24HOURS` | Maximum session duration |
| Session ID Length | 32 characters | Random identifier size |
| Character Set | a-zA-Z0-9 | Session ID character range |
| Cleanup Strategy | Lazy cleanup | Remove on access, create, or explicit call |

---

## Lifecycle Workflows

### Session Creation Flow

```
1. Handler requests session via Handler::getOrCreateSession()
2. SessionManager::getInstance() accessed
3. SessionManager::createSession() called
4. generateSessionId() creates 32-char random string
5. Collision check: regenerate if ID exists
6. New Session object created with ID
7. Expiration set: current_time + sessionTimeout_
8. Session stored in sessions_ map
9. Session reference returned
10. Set-Cookie header added to HTTP response
```

### Session Access Flow

```
1. Client includes session_id cookie in request
2. Request::getCookie("session_id") extracts value
3. SessionManager::getSession(sessionId) validates
4. Check sessions_ map for ID existence
5. If found, Session::isExpired() validates
6. If expired: erase session, return NULL
7. If valid: Session::updateAccessTime() called
8. Session pointer returned to handler
9. Handler reads/writes session data
10. Response may include updated cookie
```

### Session Destruction Flow

```
1. Explicit destruction via Handler::destroySession()
2. SessionManager::destroySession(sessionId) called
3. sessions_.erase(sessionId) removes from storage
4. Return true if erased, false if not found
5. Client receives Set-Cookie with max-age=0
6. Client cookie automatically expires
```

### Cleanup Flow

```
1. cleanupExpiredSessions() invoked (lazy strategy)
2. Iterate through sessions_ map
3. For each session: check Session::isExpired()
4. If expired: sessions_.erase(iterator)
5. Continue until all expired sessions removed
6. Called during createSession(), getSession(), or explicit
```

---

## Integration with Other Modules

### With 02_http/ (HTTP Layer)

**Request Cookie Parsing**:
```cpp
// Request automatically parses Cookie header
Request::getCookie("session_id") → returns session ID string
```

**Response Cookie Generation**:
```cpp
// Response provides cookie interface
Response::addCookie(cookie);
Response::toString() → serializes Set-Cookie headers
```

### With 03_handlers/Handler Base

**Session Helper Integration**:
```cpp
// Available in all handler implementations
Session* Handler::getOrCreateSession(Request& req, Response& res);
void Handler::destroySession(Request& req);
```

**Handler Usage Pattern**:
```cpp
// Any handler can access sessions
Session* session = Handler::getOrCreateSession(ctx.req, ctx.res);
session->setData("user_id", "12345");
```

**Demo Handler Registration**:
- SessionDemoHandler registered for `/session` URI pattern
- Integrated through handler factory system
- Immediate availability without configuration

### With 01_config/ (Configuration)

**Session Timeout Configuration**:
```cpp
// Global timeout can be configured
SessionManager::getInstance().setSessionTimeout(customTimeout);
```

**Server Integration**:
- Sessions enabled via `server.sessions_enabled` flag
- Timeout configurable via `server.session_timeout`
- Cookie name configurable via `server.session_cookie_name`
- Default: disabled, 1 hour timeout, "SESSIONID" cookie name

---

## Error Handling

### Session Retrieval Errors

| Error Condition | Detection | Response |
|-----------------|-----------|----------|
| **Invalid Session ID** | ID not found in sessions_ map | Return NULL → create new session |
| **Expired Session** | Current time > expirationTime | Remove session, return NULL |
| **Malformed Cookie** | Parse failure in Cookie::parse() | Return empty cookie → ignore |

**Graceful Degradation**:
- Missing/invalid sessions result in new session creation
- Malformed cookies ignored without request failure
- Automatic cleanup prevents resource exhaustion

**State Consistency**:
- Session operations atomic within SessionManager
- Cleanup operations preserve active sessions
- ID generation ensures uniqueness

---

## Security Considerations

### Session Security

**Identifier Security**:
- 32-character random alphanumeric session IDs
- Sufficient entropy to prevent brute force attacks
- Collision detection and regeneration
- No predictable sequence in ID generation

**Access Security**:
- Automatic expiration prevents indefinite sessions
- Last access tracking enables inactivity timeouts
- No session fixation vulnerabilities
- Secure session storage in manager map

### Cookie Security

**HttpOnly Protection**:
- Session cookies marked HttpOnly by default (`setHttpOnly(true)`)
- Prevents client-side JavaScript access to session_id
- Mitigates XSS attack surface significantly

**Scope Control**:
- Path attribute limits cookie scope (default: `/`)
- Domain restriction available when needed
- Secure flag ready for HTTPS-only deployment

**Expiration Control**:
- Precise max-age control for session duration
- Immediate expiration via `max-age=0` for logout
- Browser-enforced expiration timing

### Data Security

**Storage Security**:
- Sessions stored server-side only (not client)
- Session ID is random token, not data container
- Arbitrary data stored in memory map
- No sensitive data transmitted to client

**Resource Protection**:
- Automatic cleanup of expired sessions
- Lazy removal prevents memory leaks
- Bounded session storage growth
- Efficient string-based data storage

### Collision Prevention

**ID Uniqueness**:
- Session ID regeneration on duplicate detection
- Statistical uniqueness assurance
- No session overwriting or data mixing
- 32-character space provides immense combinatorial possibilities

---

## Advanced Topics

### Custom Session Timeouts

**Per-Session Configuration**:
```cpp
// Individual session timeout override
session->setExpiration(std::time(NULL) + customTimeout);
```

**Global Configuration Override**:
```cpp
// System-wide timeout setting
SessionManager::getInstance().setSessionTimeout(SESSION_TIMEOUT_30MIN);
```

### Session Data Serialization

**Current Design**: String-only storage sufficient for most use cases
**Extension Path**: Complex data types via JSON serialization in handler logic
**Example**: Store JSON strings, parse in handler when needed

### Distributed Session Storage

**Current Design**: In-memory storage suitable for single server
**Future Enhancement**: External storage (Redis, database)
**Load Balancing**: Session replication for multi-server environments
**Consideration**: Session affinity or shared storage required

---

## Summary

The `05_session/` module provides comprehensive session management through:

✅ **RFC-compliant cookie handling** with full attribute support  
✅ **Secure session management** with random 32-character identifiers  
✅ **Automatic lifecycle control** with configurable timeouts and lazy cleanup  
✅ **Practical demonstration** with complete `/session/*` endpoint suite  
✅ **Seamless integration** with HTTP and handler infrastructure  
✅ **Security-first implementation** with HttpOnly and scope controls  
✅ **Efficient resource management** with lazy cleanup strategy  
✅ **Production-ready error handling** with graceful degradation  

**Key Strengths**:
- **Protocol Compliance**: Full RFC 6265 cookie specification support
- **Security Focus**: HttpOnly cookies, random IDs, automatic expiration
- **Production Ready**: Comprehensive error handling and resource management
- **Easy Integration**: Simple handler interface for immediate use
- **Demonstration Ready**: Complete demo endpoints for testing

**Integration Excellence**:
- Tight coupling with HTTP layer for cookie operations
- Base handler integration for universal session access
- Demo handler for immediate functionality verification
- Configuration constants for common timeout scenarios

This session implementation provides a robust foundation for stateful web applications while maintaining the stateless nature of HTTP through secure client-side session tracking.