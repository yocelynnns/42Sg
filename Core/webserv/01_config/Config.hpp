#ifndef WEBSERV_01_CONFIG_CONFIG_HPP
#define WEBSERV_01_CONFIG_CONFIG_HPP

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <sstream>
#include <algorithm> 

// Default configuration values
const size_t DEFAULT_CLIENT_MAX_BODY_SIZE = 1024 * 1024; // 1MB default for client request body
const int DEFAULT_CONNECTION_TIMEOUT = 60;              // Default connection timeout in seconds
const size_t DEFAULT_MAX_CONNECTIONS = 1024;           // Maximum simultaneous connections
const int DEFAULT_CGI_TIMEOUT = 30;                    // CGI script execution timeout in seconds
const int DEFAULT_MAX_CGI_PROCESSES = 10;                 // Maximum concurrent CGI processes
const std::string DEFAULT_UPLOAD_DIR = "./assets/upload"; // Default upload directory

// ------------------- Location -------------------
// Represents a "location" block inside a server configuration.
// Locations define routing rules for specific paths (e.g., "/images", "/upload").
struct Location {
	std::string path;							// URL path for this location (e.g., "/upload")
	std::vector<std::string> allowed_methods;	// Allowed HTTP methods: ["GET", "POST", "DELETE"]
	std::string root;							// Document root directory for this location
	std::string redirect_url;					// Optional redirect target (HTTP 3xx)
	bool autoindex;								// Enable/disable directory listing
	std::string upload_dir;						// Target directory for uploaded files
	std::vector<std::string> index_files;		// Default index files (e.g., ["index.html"])
	bool upload_enable;

	// CGI configuration
	std::vector<std::string> cgi_extensions;              // List of CGI extensions (.php, .py, etc.)
	std::map<std::string, std::string> cgi_interpreters;  // Extension -> interpreter path mapping
	std::string default_cgi_interpreter;                  // Default interpreter if not in map
	int cgi_timeout;                                      // Timeout for CGI execution (seconds)
	size_t cgi_max_processes;                             // Max concurrent CGI processes
	bool cgi_enable;                                      // Enable CGI processing for this location
	std::string cgi_path;                                 // directory path for CGI scripts


	// Return and access control directives
	int return_code;                       // For "return <code> <url>;"
	std::string return_url;                // Redirect target for return directive
	bool deny_all;                         // "deny all;" flag
	std::vector<std::string> denied_ips;   // Specific denied IPs

	// Support for body size override in location
	size_t client_max_body_size;           // Optional override of server-level limit

	Location(); // Constructor: sets default values
};

// ------------------- ServerConfig -------------------
// Represents a "server" block in the configuration.
// Contains host/port info, root paths, locations, and session/connection settings.
struct ServerConfig {
	std::string host;						// IP address or hostname (e.g., "127.0.0.1")
	int port;								// Port number (e.g., 8080)
	std::vector<std::string> server_names;	// Virtual host name (e.g., "localhost")
	size_t client_max_body_size;			// Maximum allowed request body size
	std::map<int, std::string> error_pages;	// Custom error pages (status_code -> file path)
	std::vector<Location> locations;		// All location blocks under this server
	std::string default_root;				// Default root directory for server
	std::vector<std::string> default_index;	// Default index files list
	std::string upload_dir;					// NEW: Server level upload directory

	// Session management
	bool sessions_enabled;					// Enable session support
	int session_timeout;					// Session expiration time in seconds
	std::string session_cookie_name;		// Cookie name to identify sessions

	// Connection management
	int connection_timeout;					// Connection idle timeout in seconds
	size_t max_connections;					// Maximum concurrent connections
	int cgi_timeout;						// Default CGI timeout for this server
	int cgi_max_processes;					// Max concurrent CGI processes for this server

	int client_header_timeout;
	int client_body_timeout;

	// Return and access control directives
	int return_code;                        // For "return <code> <url>;"
	std::string return_url;
	bool deny_all;                          // "deny all;"
	std::vector<std::string> denied_ips;    // "deny <ip> <ip2>;"

	ServerConfig(); // Constructor: sets default values
};

// ------------------- EventsConfig -------------------
// Represents global "events" settings.
// Manages global connection limits and timeouts.
struct EventsConfig {
	int connection_timeout; // Default connection timeout
	size_t max_connections; // Maximum simultaneous connections
	int cgi_timeout;        // Default timeout for CGI scripts
	int cgi_max_processes;

	EventsConfig(); // Constructor: sets default values
};

// ------------------- HttpConfig -------------------
// Represents the "http" block in configuration.
// Contains all defined server blocks.
struct HttpConfig {
	std::vector<ServerConfig> servers; // List of servers

	HttpConfig(); // Constructor: initializes empty server list
};

// ------------------- GlobalConfig -------------------
// Represents the root configuration object.
// Contains events and http blocks along with flags indicating their presence.
struct GlobalConfig {
	EventsConfig events;  // Global events configuration
	HttpConfig http;      // HTTP configuration

	bool has_events;      // True if "events" block was defined
	bool has_http;        // True if "http" block was defined

	GlobalConfig(); // Constructor: initializes flags
};

// ------------------- Config Class -------------------
// Main configuration manager.
// Loads, validates, and provides access to configuration data.
class Config {
private:
	GlobalConfig global_config; // Stores entire parsed configuration

public:
	Config(); // Constructor
	Config(const Config& other); // Copy Constructor
	Config& operator=(const Config& other); // Copy Assignment

	// Load configuration from file
	// Returns true if parsing and validation succeed, false otherwise
	bool load(const std::string& filename);

	// Perform semantic validation on the configuration
	// Returns false if errors are found
	bool validateConfig() const;

	// Set default values for missing configuration parameters
	void setDefaults();

	// ------------------- Accessors -------------------
	const std::vector<ServerConfig>& getServers() const; // Access all servers
	const GlobalConfig& getGlobalConfig() const;        // Access global config
	const ServerConfig* findServer(const std::string& host, int port) const; // Find server by host/port
	const Location* findLocation(const ServerConfig& server, const std::string& path) const; // Find location by path

private:
	// Internal validation helpers
	bool validateServer(const ServerConfig& server) const;
	bool validateLocation(const Location& location) const;
};

#endif
