#include "Config.hpp"
#include "ConfigParser.hpp"
#include "../06_utils/Logger.hpp"

// Default configuration values
const std::string DEFAULT_ROOT = "/var/www/html";       // Default root directory for servers
const std::vector<std::string> DEFAULT_INDEX = std::vector<std::string>(1, "index.html"); // Default index file

// ------------------- Location -------------------
// Constructor for Location struct
// Initializes default values for Location settings
Location::Location() 
	: path(""),                          // Empty path (will be set by parser)
	allowed_methods(),                   // Empty vector
	root(""),                            // Empty root (will be set by parser)
	redirect_url(""),                    // No redirect by default
	autoindex(false),                    // Autoindex disabled by default
	upload_dir(""),                      // Default upload directory
	index_files(),                       // Empty vector (will be populated by parser)
	upload_enable(false),                // Upload disabled by default
	cgi_extensions(),                    // Empty vector
	cgi_interpreters(),                  // Empty map
	cgi_timeout(0),                      // CTY: Changed, so that it's possible to have assigned value of 0
	cgi_max_processes(0),                // 0 = inherit from parent?
	cgi_enable(false),                   // CGI arguments disabled by default
	cgi_path(""),                        // Empty CGI path
	return_code(0),
	deny_all(false),
	client_max_body_size(0)	{}

// ------------------- ServerConfig -------------------
// Constructor for ServerConfig struct
// Initializes default values for a server block
ServerConfig::ServerConfig()
	: host(""),
	port(0),                          // Default port 0 (invalid, must be set)
	server_names(),
	client_max_body_size(DEFAULT_CLIENT_MAX_BODY_SIZE), // Safe default
	default_root(""),                 // Will inherit global root if empty
	default_index(),                  // Will inherit global default index
	upload_dir(""),                   // NEW: Server level default upload location
	sessions_enabled(false),          // Sessions disabled by default
	session_timeout(3600),            // Default session timeout 1 hour
	session_cookie_name("SESSIONID"), // Default cookie name
	connection_timeout(0),            // No connection timeout by default
	max_connections(0),               // No limit on max connections by default
	cgi_timeout(0),                   // No CGI timeout by default
	cgi_max_processes(0),                // 0 = inherit from parent?
	client_header_timeout(0),
	client_body_timeout(0),
	return_code(0),
	deny_all(false) {}

// ------------------- EventsConfig -------------------
// Constructor for EventsConfig struct
// Initializes default event-related configuration
EventsConfig::EventsConfig()
	: connection_timeout(0),         // Default no connection timeout
	max_connections(0),            // Default no max connections
	cgi_timeout(0),
	cgi_max_processes(0)
	{}              // Default no CGI timeout

// ------------------- HttpConfig -------------------
// Constructor for HttpConfig struct
// Empty by default, will be populated by parser
HttpConfig::HttpConfig() {}

// ------------------- GlobalConfig -------------------
// Constructor for GlobalConfig struct
// Keeps track of which global blocks are defined (events, http)
GlobalConfig::GlobalConfig() : has_events(false), has_http(false) {}

// ------------------- Config -------------------
// Constructor for Config class
Config::Config() {}

// Copy Constructor
Config::Config(const Config& other)
	: global_config(other.global_config)
{}

// Copy Assignment
Config& Config::operator=(const Config& other) {
	if (this != &other) {
		global_config = other.global_config;
	}
	return *this;
}

// Load configuration from a file
// Uses ConfigParser to parse the configuration file
// Sets default values and validates configuration
bool Config::load(const std::string& filename) {
	ConfigParser parser;
	if (!parser.parseFile(filename, global_config)) { // Parse config file
		Logger::error("Config::load - Configuration loading failed for: " + filename);
		return false;
	}
	
	setDefaults();  // Fill in missing default values
	
	if (!validateConfig()) { // Validate parsed configuration
		Logger::error("Config::load - Configuration validation failed for: " + filename);
		return false;
	}
	
	Logger::info("Config::load - Configuration loaded successfully from: " + filename);
	return true;
}

// Validate the entire configuration
// Ensures required blocks exist and each server is valid
bool Config::validateConfig() const {
	if (!global_config.has_events && global_config.has_http) {
		Logger::error("Missing 'events' block");
		return false;
	}

	if (global_config.http.servers.empty()) {
		Logger::error("No server blocks defined");
		return false;
	}
	
	// Validate each server block individually
	for (size_t i = 0; i < global_config.http.servers.size(); ++i) {
		if (!validateServer(global_config.http.servers[i])) {
			return false;
		}
	}
	return true;
}

// Validate an individual server configuration
// Checks port, root directory, and validates all locations
bool Config::validateServer(const ServerConfig& server) const {
	if (server.port <= 0 || server.port > 65535) {
		Logger::error("Config::validateServer - Invalid port number: " + Utils::toString(server.port));
		return false;
	}
	if (server.default_root.empty()) {
		Logger::error("Config::validateServer - Server missing root directory");
		return false;
	}
	
	// Validate each location block
	for (size_t i = 0; i < server.locations.size(); ++i) {
		if (!validateLocation(server.locations[i])) {
			return false;
		}
	}
	
	return true;
}

// Validate an individual location configuration
// Ensures path is set and either root or redirect URL is defined
bool Config::validateLocation(const Location& location) const {
	if (location.path.empty()) {
		Logger::error("Location missing path");
		return false;
	}

	// Must have at least one of: root, redirect, or return
	if (location.root.empty() && location.redirect_url.empty() && location.return_code == 0) {
		Logger::error("Location missing root, redirect, or return directive");
		return false;
	}

	// If deny_all, skip other checks
	return true;
}

// ------------------- Set Default Values -------------------
// Fills in missing configuration values with predefined defaults
// Ensures that servers, events, and locations have sensible fallback values
void Config::setDefaults() {
	// Set defaults for the global events block
	if (global_config.events.connection_timeout == 0) {
		global_config.events.connection_timeout = DEFAULT_CONNECTION_TIMEOUT;
	}
	if (global_config.events.max_connections == 0) {
		global_config.events.max_connections = DEFAULT_MAX_CONNECTIONS;
	}
	if (global_config.events.cgi_timeout == 0) {
		global_config.events.cgi_timeout = DEFAULT_CGI_TIMEOUT;
	}
	if (global_config.events.cgi_max_processes == 0){
		global_config.events.cgi_max_processes = DEFAULT_MAX_CGI_PROCESSES;
	}
	
	// Iterate through all servers to set default values
	for (size_t i = 0; i < global_config.http.servers.size(); ++i) {
		ServerConfig& server = global_config.http.servers[i];
		
		// // Set default max body size if not specified
		// if (server.client_max_body_size == 0) {
		// 	server.client_max_body_size = DEFAULT_CLIENT_MAX_BODY_SIZE;
		// }
		// Set default root directory
		if (server.default_root.empty()) {
			server.default_root = DEFAULT_ROOT;
		}
		// Set default index files
		if (server.default_index.empty()) {
			server.default_index = DEFAULT_INDEX;
		}
		// Use event defaults for connection timeout and max connections
		if (server.connection_timeout == 0) {
			server.connection_timeout = global_config.events.connection_timeout;
		}
		if (server.max_connections == 0) {
			server.max_connections = global_config.events.max_connections;
		}
		if (server.cgi_timeout == 0) {
			server.cgi_timeout = global_config.events.cgi_timeout;
		}
		if (server.cgi_max_processes == 0) {
			server.cgi_max_processes = global_config.events.cgi_max_processes;
		}
		if (server.return_code == 0)
			server.return_code = 0;   // 0 = no return by default
		if (server.return_url.empty())
			server.return_url = "";
		if (!server.deny_all)
			server.deny_all = false;
		if (server.denied_ips.empty())
			server.denied_ips.clear();
		
		// Iterate through all location blocks within the server
		for (size_t j = 0; j < server.locations.size(); ++j) {
			Location& location = server.locations[j];
			
			// If location has neither root nor redirect, inherit server's root
			if (location.root.empty() && location.redirect_url.empty()) {
				location.root = server.default_root;
			}
			// Inherit default index files if none defined
			if (location.index_files.empty()) {
				location.index_files = server.default_index;
			}
			// Set default allowed HTTP methods if not specified
			if (location.allowed_methods.empty()) {
				location.allowed_methods.push_back("GET");
				location.allowed_methods.push_back("POST");
				location.allowed_methods.push_back("DELETE");
			}
			// Inherit CGI timeout from server if not set
			if (location.cgi_timeout == 0) {
				location.cgi_timeout = server.cgi_timeout;
			}
			if (location.cgi_max_processes == 0) {
				location.cgi_max_processes = server.cgi_max_processes;
			}
			// Inherit client_max_body_size if not set
			if (location.client_max_body_size == 0) {
				location.client_max_body_size = server.client_max_body_size;
			}
			if (location.return_code == 0) {
				location.return_code = server.return_code;  // inherit server-level return
			}
			if (location.return_url.empty()) {
				location.return_url = server.return_url;    // inherit server-level return URL
			}
			if (!location.deny_all) {
				location.deny_all = server.deny_all;        // inherit server-level deny_all
			}
			if (location.denied_ips.empty()) {
				location.denied_ips = server.denied_ips;    // inherit server-level denied IPs
			}
			// Location-level upload_dir inheritance
			if (location.upload_dir.empty()) {
			if (!server.upload_dir.empty()) {
				location.upload_dir = server.upload_dir;
			} else {
				location.upload_dir = DEFAULT_UPLOAD_DIR;  // Global default
			}
			}
		}
	}
}

// ------------------- Accessors -------------------

// Returns a reference to all configured servers
const std::vector<ServerConfig>& Config::getServers() const {
	return global_config.http.servers;
}

// Returns a reference to the global configuration
const GlobalConfig& Config::getGlobalConfig() const {
	return global_config;
}

// ------------------- Find Server -------------------
// Finds a server configuration by host and port
// Returns pointer to the ServerConfig if found, otherwise NULL
const ServerConfig* Config::findServer(const std::string& host, int port) const {
	// Convert input host to lowercase for case-insensitive comparison
	std::string host_lower = host;
	std::transform(host_lower.begin(), host_lower.end(), host_lower.begin(), ::tolower);
	
	for (size_t i = 0; i < global_config.http.servers.size(); ++i) {
		const ServerConfig& server = global_config.http.servers[i];
		
		// Check listen host (IP address) - also case-insensitive
		std::string server_host_lower = server.host;
		std::transform(server_host_lower.begin(), server_host_lower.end(), server_host_lower.begin(), ::tolower);
		if (server_host_lower == host_lower && server.port == port) {
			return &server;
		}
		
		// Check ALL server names
		for (size_t j = 0; j < server.server_names.size(); ++j) {
			std::string server_name_lower = server.server_names[j];
			std::transform(server_name_lower.begin(), server_name_lower.end(), server_name_lower.begin(), ::tolower);
			
			if (server_name_lower == host_lower && server.port == port) {
				return &server;
			}
		}
	}
	return NULL; // Not found
}

// ------------------- Find Location -------------------
// Finds the best matching location for a given path in a server
// Uses longest-prefix matching to select the most specific location
const Location* Config::findLocation(const ServerConfig& server, const std::string& path) const {
	const Location* best_match = NULL;
	size_t best_match_length = 0;
	
	for (size_t i = 0; i < server.locations.size(); ++i) {
		const Location& loc = server.locations[i];
		// Check if path starts with location path
		if (path.find(loc.path) == 0 && loc.path.length() > best_match_length) {
			best_match = &loc;           // Update best match
			best_match_length = loc.path.length();
		}
	}
	
	return best_match; // Returns NULL if no match found
}
