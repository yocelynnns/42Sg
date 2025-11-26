Excellent point! This is a crucial Nginx-like behavior that must be accurately documented. The virtual host (`server_name`) matching on shared IP:port is a sophisticated feature. Let me update the file structure document to reflect this properly.

# Webserv Project File Structure (Actual Implementation)

## Core Source Code Structure

### Root Directory Files
```
./
├── 00_core/                  # Core server infrastructure  
├── 01_config/                # Configuration management
├── 02_http/                  # HTTP protocol implementation
├── 03_handlers/              # Request processing logic
├── 04_cgi/                   # CGI support (Bonus)
├── 05_session/               # Session management (Bonus)
├── 06_utils/                 # Essential utilities
├── assets/                   # Static resources & test files
├── document/                 # Comprehensive documentation
├── main.cpp                  # Entry point, server initialization
├── Makefile                  # Build system
├── README.md                 # Project documentation
├── structure.txt             # Current file structure listing
├── var/                      # Runtime directories
├── webserv.conf              # Default configuration file
├── tests.conf                # Comprehensive test configuration
├── webserve.en.subject.pdf   # Project subject (PDF)
└── WEBSERV EVAL.pdf          # Evaluation criteria (PDF)
```

### 00_core/ - Core Server Infrastructure
```
00_core/
├── Connection.cpp            # Individual client connection (with CGI states)
├── Connection.hpp            # Connection state machine & lifecycle
├── ConnectionPool.cpp        # Connection collection manager
├── ConnectionPool.hpp        # Thread-safe connection management
├── EventLoop.cpp             # **epoll**-based event multiplexer
├── EventLoop.hpp             # Event polling & dispatch
├── NonBlockingIO.cpp         # Poll-compliant I/O wrappers
├── NonBlockingIO.hpp         # Non-blocking I/O primitives
├── Server.cpp                # Main server orchestrator
├── Server.hpp                # Signal handling & configuration reload
├── Socket.cpp                # Low-level socket operations
└── Socket.hpp                # Socket utilities & listening sockets
```

### 01_config/ - Configuration Management
```
01_config/
├── Config.cpp                # Configuration storage & validation
├── Config.hpp                # Global config hierarchy
├── ConfigParser.cpp          # Nginx-style configuration parser
└── ConfigParser.hpp          # Tokenizer & directive processing
```

### 02_http/ - HTTP Protocol Implementation
```
02_http/
├── HttpUtils.cpp             # Protocol utilities & MIME types
├── HttpUtils.hpp             # Header normalization helpers
├── Request.cpp               # HTTP request representation
├── Request.hpp               # Parsed request data structure
├── RequestParser.cpp         # Incremental HTTP parser
├── RequestParser.hpp         # State machine & buffer management
├── Response.cpp              # HTTP response builder
└── Response.hpp              # Response serialization & cookies
```

### 03_handlers/ - Request Processing Logic
```
03_handlers/
├── AutoIndexHandler.cpp      # Modern HTML directory listings
├── AutoIndexHandler.hpp      # Glassmorphism UI generator
├── DeleteHandler.cpp         # Secure file deletion with validation
├── DeleteHandler.hpp         # Multi-layer safety checks
├── ErrorHandler.cpp          # Custom error page handling
├── ErrorHandler.hpp          # Status code mapping
├── Handler.cpp               # Factory method & path resolution
├── Handler.hpp               # Base class & session utilities
├── StaticFileHandler.cpp     # Binary-safe file serving
├── StaticFileHandler.hpp     # MIME detection & caching
├── UploadHandler.cpp         # Multipart/form-data parser
├── UploadHandler.hpp         # File validation & duplicate detection
├── SessionDemoHandler.hpp    # Session demonstration (from 05_session)
└── SessionDemoHandler.cpp    #
```

### 04_cgi/ - CGI Support (Bonus)
```
04_cgi/
├── CGI.cpp                   # Process management & timeout enforcement
├── CGI.hpp                   # Interpreter registry & statistics
├── CGIHandler.cpp            # HTTP handler integration
└── CGIHandler.hpp            # Async execution coordination
```

### 05_session/ - Session Management (Bonus)
```
05_session/
├── Cookie.cpp                # RFC 6265-compliant cookie handling
├── Cookie.hpp                # Set-Cookie generation & parsing
├── Session.cpp               # Session data storage & lifecycle
├── Session.hpp               # Key-value data management
├── SessionManager.cpp        # Singleton session orchestrator
└── SessionManager.hpp        #
```

### 06_utils/ - Essential Utilities
```
06_utils/
├── cgiUtils.hpp              # CGI output parsing & debugging
├── configUtils.hpp           # Size (K/M/G) & time (s/m/h) parsers
├── Logger.cpp                # Multi-level logging with colors
├── Logger.hpp                # File & console output
├── Utils.cpp                 # String manipulation functions
└── Utils.hpp                 # Type conversion & validation
```

## Assets Directory Structure

### assets/ - Static Resources & Test Files
```
assets/
├── cgi-bin/                  # CGI script examples
│   ├── mixed/                # Mixed interpreter directory
│   │   ├── calc.py          # Python calculator
│   │   ├── date.pl          # Perl date script
│   │   └── info.php         # PHP info script
│   ├── perl/                # Perl CGI scripts (Bonus)
│   │   ├── env.pl           # Environment dump
│   │   ├── form.pl          # Form processor
│   │   └── hello.pl         # Simple greeting
│   ├── php/                 # PHP CGI scripts (Bonus)
│   │   ├── env.php          # Environment dump
│   │   ├── form.php         # Form processor
│   │   ├── hello.php        # Simple greeting
│   │   └── xenv.php         # Extended environment
│   └── python/              # Python CGI scripts
│       ├── crash.py         # Crashes for testing
│       ├── env.py           # Environment dump
│       ├── error.py         # Malformed output
│       ├── errors/
│       │   └── trigger-413.py # Custom error triggers
│       ├── form.py          # Form processor
│       ├── get_test.py      # Query string tests
│       ├── hello.py         # Simple greeting
│       ├── import-error.py  # Missing module
│       ├── no-exec.py       # Permission test
│       ├── syntax-error.py  # Python syntax error
│       ├── timeout.py       # Long execution test
│       ├── upload.py        # File upload handler
│       └── uploads/         # Uploaded files directory
├── dupe/                    # Duplicate testing directory
│   ├── favicon.ico
│   └── index.html
├── error_pages/            # Custom HTTP error pages
│   ├── 301.html            # Moved permanently
│   ├── 302.html            # Found (temporary)
│   ├── 400.html            # Bad request
│   ├── 403.html            # Forbidden
│   ├── 404.html            # Not found
│   ├── 405.html            # Method not allowed
│   ├── 413.html            # Payload too large
│   ├── 500.html            # Internal server error
│   ├── 502.html            # Bad gateway
│   ├── 503.html            # Service unavailable
│   └── 504.html            # Gateway timeout
├── session/                # Session testing content
│   ├── favicon.ico
│   └── index.html
├── upload/                 # File upload directories
│   ├── 8010/              # Port 8010 uploads
│   ├── 8011/              # Port 8011 uploads
│   ├── filedump/          # Large file uploads
│   ├── index.html         # Upload test page
│   └── large/             # Large file storage
├── www/                    # Primary static website
│   ├── 301.html           # 301 redirect target
│   ├── 302.html           # 302 redirect target
│   ├── cgi.html           # CGI test suite page
│   ├── errors/            # Error page testing
│   │   └── test.html
│   ├── error-test.html    # Client-side error tests
│   ├── favicon.ico        # Site icon
│   ├── files/             # Directory listing test
│   │   ├── cgi/           # CGI examples
│   │   │   ├── calc.py
│   │   │   ├── date.pl
│   │   │   └── info.php
│   │   ├── css/           # Stylesheet storage
│   │   │   └── style.css
│   │   ├── forbiddendir/  # 403 test directory
│   │   │   └── empty.txt
│   │   ├── images/        # Image assets
│   │   │   ├── image.png
│   │   │   └── logo.jpg
│   │   ├── js/            # JavaScript files
│   │   │   └── script.js
│   │   ├── subdir/        # Nested directory
│   │   │   └── nested.txt
│   │   ├── zfile1.txt     # Test file 1
│   │   ├── zfile2.txt     # Test file 2
│   │   └── zfile3.txt     # Test file 3
│   ├── forbidden.html     # 403 test page
│   ├── index.html         # Homepage
│   ├── large/             # Large file tests
│   │   └── index.html
│   ├── large-form.html    # Large payload form
│   ├── methods-test.html  # HTTP methods tester
│   ├── minimal/           # Minimal test case
│   │   └── index.html
│   ├── script.js          # Site JavaScript
│   ├── style.css          # Site stylesheet
│   ├── test.html          # Test static file
│   └── upload-test/       # Upload directory
├── www2/                  # Secondary server content
│   ├── favicon.ico
│   ├── index.html
│   └── media/             # Media assets
│       └── images/
│           ├── img1.txt
│           └── img2.txt
└── www_cgi_test/          # CGI testing content
    ├── favicon.ico
    ├── forms/             # Form examples
    │   └── test.html
    ├── index.html         # CGI test portal
    └── test.html          # Additional test page
```

### var/ - Runtime Directories
```
var/
└── www/                   # Document root for default server
    ├── html/             # HTML files
    │   └── index.html    # Default page
    └── image/            # Image assets
        └── image.png
```

## Documentation Structure

### document/ - Comprehensive Documentation
```
document/
├── 00_core.md            # Core module architecture (epoll, connections, timeouts)
├── 01_config.md          # Configuration system (Nginx syntax, validation)
├── 02_http.md            # HTTP/1.1 protocol implementation
├── 03_handlers.md        # Request handler system & path resolution
├── 04_cgi.md             # CGI/1.1 execution engine
├── 05_session.md         # Session management with cookies
├── 06_utils.md           # Utility services & logging
├── ws_dataflow.md        # Complete data flow documentation
├── ws_datastructure.md   # Enhanced data structures
└── ws_filestructure.md   # This file structure documentation
```

## Configuration Files

### webserv.conf - Primary Configuration (Nginx-style)
Features **virtual host matching** on shared IP:port combinations:

```nginx
# Port 8010: Main server (default for unmatched hosts)
server {
    listen 127.0.0.1:8010;
    server_name localhost;
    # ... full configuration
}

# Port 8011: Secondary server
server {
    listen 127.0.0.1:8011;
    server_name secondary.localhost localhost;
    # ... configuration
}

# Port 8012: Multi-interpreter CGI
server {
    listen 127.0.0.1:8012;
    server_name cgi-test.localhost localhost;
    # ... CGI configuration
}

# Port 8013: TWO servers sharing IP:port for virtual host testing
# First server = default (method.localhost)
server {
    listen 127.0.0.1:8013;
    server_name method.localhost localhost;  # Default for port 8013
    root assets/upload;
    # ... large file/upload configuration
}

# Second server on SAME IP:port = only served when Host = dupe.localhost
server {
    listen 127.0.0.1:8013;                     # Same IP:port as above
    server_name dupe.localhost dupp.localhost; # Virtual host match required
    root assets/dupe;                          # Different document root
    # ... duplicate testing configuration
}

# Port 8014: Session management
server {
    listen 127.0.0.1:8014;
    server_name session.localhost localhost;
    # ... session configuration
}

# Port 8015: Error condition testing
server {
    listen 127.0.0.1:8015;
    server_name error-test;
    # ... error page configuration
}
```

**Virtual Host Matching Behavior**:
- **Socket Deduplication**: Only **one** listening socket created for `127.0.0.1:8013`
- **Host Header Matching**: After `accept()`, server inspects `Host` header from HTTP request
- **Default Server**: First server block for IP:port (`method.localhost`) handles **all unmatched** `Host` values
- **Named Virtual Host**: Second server block (`dupe.localhost`) only served when `Host: dupe.localhost` or `Host: dupp.localhost`
- **Test Purpose**: The `dupe` server specifically tests this Nginx-compatible virtual host resolution

### tests.conf - Extended Test Configuration
- Additional virtual host combinations
- Alternative timeout settings
- Extended CGI interpreter configurations

## Key Implementation Features

### Virtual Host Architecture
- **IP:Port Deduplication**: `updateListeningSocketsFromConfig()` ensures one socket per unique `host:port`
- **HTTP/1.1 Host Header Processing**: Request parser extracts `Host` header for virtual host matching
- **Server Name Matching**: `Config::findServer()` performs **case-insensitive** matching against `server_name` lists
- **Default Server Fallback**: Unmatched `Host` headers route to first defined server for that IP:port
- **Multiple Server Names**: Single server block supports multiple `server_name` aliases (e.g., `dupe.localhost dupp.localhost`)

### Server Deployment by Virtual Host

| Port | Server Name(s) | Document Root | Purpose |
|------|----------------|---------------|---------|
| 8010 | `localhost` | `assets/www` | Main features |
| 8011 | `secondary.localhost`, `localhost` | `assets/www2` | Secondary server |
| 8012 | `cgi-test.localhost`, `localhost` | `assets/www_cgi_test` | Multi-CGI testing |
| **8013** | **`method.localhost`**, **`localhost`** | **`assets/upload`** | **Large file testing (default)** |
| **8013** | **`dupe.localhost`**, **`dupp.localhost`** | **`assets/dupe`** | **Duplicate testing (virtual host)** |
| 8014 | `session.localhost`, `localhost` | `assets/session` | Session management |
| 8015 | `error-test` | `assets/www` | Error condition testing |

**Critical Note**: Ports marked **8013** share the **same listening socket** but serve **different content** based on the `Host` header, implementing true HTTP/1.1 virtual host semantics.

### CGI Interpreter Support
- **Python**: `/usr/bin/python3` (mandatory)
- **PHP**: `/usr/bin/php-cgi` (bonus)
- **Perl**: `/usr/bin/perl` (bonus)
- **Mixed**: All three interpreters in `/cgi-bin/mixed/`
- **Extension Mapping**: Per-location `cgi_pass` directives map `.py`, `.php`, `.pl` to interpreters

### Test Coverage
- **Error Pages**: All HTTP status codes (301-505) with custom pages
- **CGI Scripts**: 20+ test scripts covering success, timeout, syntax errors
- **Static Files**: Binary, text, images for MIME type testing
- **Upload Areas**: Port-specific upload directories with size limits
- **Session Demo**: Complete `/session/*` endpoint suite with cookie management