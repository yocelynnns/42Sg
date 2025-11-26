#include "ConfigParser.hpp"
#include "../06_utils/Logger.hpp"
#include "../06_utils/configUtils.hpp"

// ------------------- Token -------------------
// Represents a single token extracted from the configuration file.
// Each token has a string value and the line number where it appears.
Token::Token() : value(""), line(0) {} // Default constructor
Token::Token(const std::string& v, int l) : value(v), line(l) {} // Constructor with value and line

// ------------------- ConfigParser -------------------
// Parses configuration files into structured objects (GlobalConfig, ServerConfig, etc.)
ConfigParser::ConfigParser() {}

// ------------------- Tokenization -------------------
// Converts a configuration file input stream into a list of tokens.
// Tokens are strings representing keywords, symbols, and values.
// Comments (lines starting with '#') are ignored.
// Handles special characters: { } ;
std::vector<Token> ConfigParser::tokenize(std::istream& input) {
	std::vector<Token> tokens;
	std::string line;
	int line_number = 0;

	while (std::getline(input, line)) {
		line_number++;
		size_t i = 0;
		while (i < line.size()) {
			if (std::isspace(static_cast<unsigned char>(line[i]))) { // Skip whitespace
				i++;
				continue;
			}
			if (line[i] == '#') break; // Skip comments

			// Handle single-character tokens
			if (line[i] == '{' || line[i] == '}' || line[i] == ';') {
				tokens.push_back(Token(std::string(1, line[i]), line_number));
				i++;
				continue;
			}

			// Handle multi-character tokens
			size_t start = i;
			while (i < line.size() &&
				!std::isspace(static_cast<unsigned char>(line[i])) &&
				line[i] != '{' && line[i] != '}' && line[i] != ';' && line[i] != '#') {
				i++;
			}
			tokens.push_back(Token(line.substr(start, i - start), line_number));
		}
	}
	return tokens;
}

// ------------------- Parse File -------------------
// Parses the entire configuration file and fills the GlobalConfig structure.
// Returns true on success, false if any error occurs.
bool ConfigParser::parseFile(const std::string& filename, GlobalConfig& global_config) {
	std::ifstream file(filename.c_str());
	if (!file.is_open()) { // Check if file exists
		Logger::error("Cannot open config file: " + filename);
		return false;
	}

	// Tokenize the file
	std::vector<Token> tokens = tokenize(file);
	size_t index = 0;
	
	// Parse tokens sequentially
	while (index < tokens.size()) {
		if (tokens[index].value == "events") {
			// Parse the global events block
			if (!parseEventsBlock(tokens, index, global_config)) {
				return false;
			}
		}
		else if (tokens[index].value == "http") {
			// Parse the http block
			if (!parseHttpBlock(tokens, index, global_config.http, global_config)) {
				return false;
			}
		}
		else if (tokens[index].value == "server") {
			// Parse server block at global level (legacy support)
			ServerConfig server;
			if (parseServerBlock(tokens, index, server)) {
				global_config.http.servers.push_back(server);
			} else {
				return false;
			}
		}
		else {
			// Unexpected token
			Logger::error("Unexpected token '" + tokens[index].value + "' at line " + 
						Utils::toString(tokens[index].line));
			return false;
		}
	}
	
	Logger::info("Configuration file parsed successfully: " + filename);
	return true;
}

// ------------------- Parse Events Block -------------------
// Parses a "events" block from tokens, updating the GlobalConfig object.
// Example syntax:
// events {
//     connection_timeout 60;
//     max_connections 1024;
//     cgi_timeout 30;
// }
bool ConfigParser::parseEventsBlock(std::vector<Token>& tokens, size_t& index, GlobalConfig& global_config) {
	EventsConfig& events = global_config.events; // Reference to global events config

	// Ensure token is "events"
	if (index >= tokens.size() || tokens[index].value != "events") {
		Logger::error("Expected 'events' at line " + Utils::toString(tokens[index].line));
		return false;
	}
	index++;
	
	// Expect opening '{'
	if (index >= tokens.size() || tokens[index].value != "{") {
		Logger::error("Expected '{' after events at line " + Utils::toString(tokens[index-1].line));
		return false;
	}
	index++;
	
	// Parse directives inside the block
	while (index < tokens.size() && tokens[index].value != "}") {
		if (!parseDirective(tokens, index, NULL, NULL, &events)) {
			return false; // Directive parsing failed
		}
	}
	
	// Ensure closing '}'
	if (index >= tokens.size() || tokens[index].value != "}") {
		Logger::error("Unclosed events block");
		return false;
	}
	index++;
	
	global_config.has_events = true;  // ✅ Mark events block as defined
	return true;
}

// ------------------- Parse HTTP Block -------------------
// Parses an "http" block from tokens and updates HttpConfig and GlobalConfig.
// Example syntax:
// http {
//     server { ... }
//     server { ... }
//     ...
// }
bool ConfigParser::parseHttpBlock(std::vector<Token>& tokens, size_t& index, HttpConfig& http, GlobalConfig& global_config) {
	// Ensure current token is "http"
	if (index >= tokens.size() || tokens[index].value != "http") {
		Logger::error("Expected 'http' at line " + Utils::toString(tokens[index].line));
		return false;
	}
	index++;

	// Expect opening '{'
	if (index >= tokens.size() || tokens[index].value != "{") {
		Logger::error("Expected '{' after http at line " + Utils::toString(tokens[index-1].line));
		return false;
	}
	index++;

	global_config.has_http = true;  // ✅ Mark HTTP block as defined

	// Parse all directives and server blocks inside http
	while (index < tokens.size() && tokens[index].value != "}") {
		if (tokens[index].value == "server") {
			// Parse a server block
			ServerConfig server;
			if (parseServerBlock(tokens, index, server)) {
				http.servers.push_back(server);
			} else {
				return false; // Server parsing failed
			}
		} else {
			// Parse other directives inside http (if any)
			if (!parseDirective(tokens, index, NULL, NULL, NULL)) {
				return false;
			}
		}
	}

	// Expect closing '}'
	if (index >= tokens.size() || tokens[index].value != "}") {
		Logger::error("Unclosed http block");
		return false;
	}
	index++;

	return true;
}

// ------------------- Parse Server Block -------------------
// Parses a "server" block and fills a ServerConfig object.
// Example syntax:
// server {
//     listen 8080;
//     server_name localhost;
//     location / { ... }
// }
bool ConfigParser::parseServerBlock(std::vector<Token>& tokens, size_t& index, ServerConfig& server) {
	// Ensure current token is "server"
	if (index >= tokens.size() || tokens[index].value != "server") {
		Logger::error("Expected 'server' at line " + Utils::toString(tokens[index].line));
		return false;
	}
	index++;
	
	// Expect opening '{'
	if (index >= tokens.size() || tokens[index].value != "{") {
		Logger::error("Expected '{' after server at line " + Utils::toString(tokens[index-1].line));
		return false;
	}
	index++;
	
	// Parse all directives and location blocks inside server
	while (index < tokens.size() && tokens[index].value != "}") {
		if (tokens[index].value == "location") {
			// Parse a location block
			Location location;
			if (parseLocationBlock(tokens, index, location)) {
				server.locations.push_back(location);
			} else {
				return false;
			}
		} else {
			// Parse server-specific directives
			if (!parseDirective(tokens, index, &server, NULL, NULL)) {
				return false;
			}
		}
	}
	
	// Expect closing '}'
	if (index >= tokens.size() || tokens[index].value != "}") {
		Logger::error("Unclosed server block");
		return false;
	}
	index++;
	
	return true;
}

// ------------------- Parse Location Block -------------------
// Parses a "location" block and fills a Location object.
// Example syntax:
// location /upload {
//     root /var/www/uploads;
//     allow_methods GET POST;
// }
bool ConfigParser::parseLocationBlock(std::vector<Token>& tokens, size_t& index, Location& location) {
	// Ensure current token is "location"
	if (index >= tokens.size() || tokens[index].value != "location") {
		Logger::error("ConfigParser::parseLocationBlock - Expected 'location' at line " + Utils::toString(tokens[index].line));
		return false;
	}
	index++;
	
	// Expect location path (e.g., "/")
	if (index >= tokens.size()) {
		Logger::error("ConfigParser::parseLocationBlock - Expected location path");
		return false;
	}
	
	location.path = tokens[index].value;
	index++;
	
	// Expect opening '{'
	if (index >= tokens.size() || tokens[index].value != "{") {
		Logger::error("ConfigParser::parseLocationBlock - Expected '{' after location at line " + Utils::toString(tokens[index-1].line));
		return false;
	}
	index++;
	
	// Parse all directives inside location
	while (index < tokens.size() && tokens[index].value != "}") {
		if (!parseDirective(tokens, index, NULL, &location, NULL)) {
			return false;
		}
	}
	
	// Expect closing '}'
	if (index >= tokens.size() || tokens[index].value != "}") {
		Logger::error("Unclosed location block");
		return false;
	}
	index++;
	
	return true;
}

// ------------------- Parse Directive -------------------
// Parses a single configuration directive (key-value statement) and applies it
// to the appropriate context: ServerConfig, Location, or EventsConfig.
// Example syntax: 
//    listen 127.0.0.1:8080;
//    root /var/www/html;
//    connection_timeout 60;
bool ConfigParser::parseDirective(const std::vector<Token>& tokens, size_t& index, 
								ServerConfig* server, Location* location, EventsConfig* events) {
	std::string directive = tokens[index].value; // The directive name (e.g., "listen")
	int line = tokens[index].line;               // Line number for error reporting
	index++;

	std::vector<std::string> values; // Store directive values (e.g., "127.0.0.1", "8080")
	int current_line = line;

	// Collect all tokens until ';' or '}' (directive values)
	while (index < tokens.size() && tokens[index].value != ";" && tokens[index].value != "}") {
		if (tokens[index].line > current_line) {
			Logger::error("ConfigParser::parseDirective - Missing ';' at the end of line " + Utils::toString(current_line));
			return false;
		}
		values.push_back(tokens[index].value);
		index++;
	}

	// Check for unexpected end-of-file
	if (index >= tokens.size()) {
		Logger::error("ConfigParser::parseDirective - Unexpected end of file, expected ';' after directive at line " + Utils::toString(line));
		return false;
	}

	// Check for missing semicolon
	if (tokens[index].value == "}") {
		Logger::error("ConfigParser::parseDirective - Missing ';' before '}' at line " + Utils::toString(tokens[index].line));
		return false;
	}
	if (tokens[index].value != ";") {
		Logger::error("ConfigParser::parseDirective - Expected ';' after directive at line " + Utils::toString(line));
		return false;
	}

	index++; // Skip the ';' token

	try {
		// Determine context (events, location, or server)
		std::string context;
		if (events) context = "events";
		else if (location) context = "location";
		else context = "server";

		// Validate the directive based on context
		validateDirective(directive, values, context, line);

		// ------------------- Apply directive based on context -------------------
		if (events) {
			// Events block directives
			if (directive == "connection_timeout" && !values.empty())
				events->connection_timeout = ConfigUtils::parseTimeWithUnit(values[0], line);
			else if (directive == "max_connections" && !values.empty())
				events->max_connections = ConfigUtils::parseSizeWithUnit(values[0], line);
			else if (directive == "cgi_timeout" && !values.empty())
				events->cgi_timeout = ConfigUtils::parseTimeWithUnit(values[0], line);
			else if (directive == "cgi_max_processes" && !values.empty())
				events->cgi_max_processes = ConfigUtils::parseSizeWithUnit(values[0], line);
		}
		else if (location) {
			if (directive == "root") location->root = values[0];
			else if (directive == "autoindex") location->autoindex = (values[0] == "on");
			else if (directive == "upload_dir") location->upload_dir = values[0];
			else if (directive == "upload_enable") {
				location->upload_enable = (values[0] == "on");
				// Inherit server upload_dir if location enables uploads but doesn't specify a directory
				if (location->upload_enable && location->upload_dir.empty() && server != NULL)
					location->upload_dir = server->default_root + "/upload"; // or server->upload_dir if defined
			}
			else if (directive == "index") location->index_files = values;
			else if (directive == "allowed_methods") {
				static std::vector<std::string> valid_methods;
				if (valid_methods.empty()) {
					valid_methods.push_back("GET");
					valid_methods.push_back("POST");
					valid_methods.push_back("DELETE");
				}

				for (size_t i = 0; i < values.size(); ++i) {
					if (std::find(valid_methods.begin(), valid_methods.end(), values[i]) == valid_methods.end()) {
						throw std::runtime_error(
							std::string("Invalid HTTP method '") + values[i] +
							"' at line " + Utils::toString(line) +
							". Allowed: GET, POST, DELETE"
						);
					}
				}

				location->allowed_methods = values;
			}
			else if (directive == "cgi_enable") {
				location->cgi_enable = (values[0] == "on");  // NEW
			}
			else if (directive == "cgi_ext" && !values.empty()) {
				location->cgi_extensions = values;
			}
			else if (directive == "cgi_pass" && !values.empty()) {
				// Handle different formats:
				// cgi_pass /usr/bin/perl;                    -> set as default interpreter
				// cgi_pass .pl /usr/bin/perl;                -> set for specific extension
				// cgi_pass .py /usr/bin/python3;             -> set for specific extension
				
				if (values.size() == 1) {
					// Single value: set as default interpreter
					location->default_cgi_interpreter = values[0];
					Logger::debug("ConfigParser::parseDirective - Set default CGI interpreter: " + values[0]);
				} else if (values.size() >= 2) {
					// Two values: extension -> interpreter mapping
					location->cgi_interpreters[values[0]] = values[1];
					Logger::debug("ConfigParser::parseDirective - Set CGI interpreter for " + values[0] + ": " + values[1]);
				}
			}
			else if (directive == "cgi_path" && !values.empty()) {
				location->cgi_path = values[0];
			}
			else if (directive == "cgi_timeout" && !values.empty()) {
				location->cgi_timeout = ConfigUtils::parseTimeWithUnit(values[0], line);
			}
			else if (directive == "cgi_max_processes" && !values.empty())
				location->cgi_max_processes = ConfigUtils::parseSizeWithUnit(values[0], line);
			else if (directive == "client_max_body_size" && !values.empty()) {
				location->client_max_body_size = ConfigUtils::parseSizeWithUnit(values[0], line);
			}
			else if (directive == "return") {
				if (values.size() == 1) {
					// Only return code (e.g., return 404;)
					location->return_code = std::atoi(values[0].c_str());
				} else if (values.size() >= 2) {
					location->return_code = std::atoi(values[0].c_str());
					location->return_url = values[1];
				} else {
					throw std::runtime_error("'return' directive requires a code or code+url at line " + Utils::toString(line));
				}
			}
			else if (directive == "deny") {
				if (values.size() == 1 && values[0] == "all") {
					location->deny_all = true;
				} else {
					location->denied_ips = values;
				}
			}
		} 
		else { // server block
			if (directive == "listen") {
				if (values.size() == 1) {
					std::string listen_value = values[0];
					size_t colon_pos = listen_value.find(':');
					if (colon_pos != std::string::npos) {
						server->host = listen_value.substr(0, colon_pos);
						std::string port_str = listen_value.substr(colon_pos + 1);
						std::istringstream iss(port_str);
						
						// VALIDATE PORT NUMBER
						if (!(iss >> server->port) || server->port <= 0 || server->port > 65535) {
							throw std::runtime_error("ConfigParser::parseDirective - Invalid port number '" + port_str + 
												"' at line " + Utils::toString(line) + 
												". Port must be between 1-65535.");
						}
					} else {
						server->host = "0.0.0.0";
						std::istringstream iss(listen_value);
						
						// VALIDATE PORT NUMBER
						if (!(iss >> server->port) || server->port <= 0 || server->port > 65535) {
							throw std::runtime_error("ConfigParser::parseDirective - Invalid port number '" + listen_value + 
												"' at line " + Utils::toString(line) + 
												". Port must be between 1-65535.");
						}
					}
				} else if (values.size() >= 2) {
					server->host = values[0];
					std::istringstream iss(values[1]);
					
					// VALIDATE PORT NUMBER
					if (!(iss >> server->port) || server->port <= 0 || server->port > 65535) {
						throw std::runtime_error("ConfigParser::parseDirective - Invalid port number '" + values[1] + 
											"' at line " + Utils::toString(line) + 
											". Port must be between 1-65535.");
					}
				}
			}
			else if (directive == "server_name") server->server_names = values;
			else if (directive == "root") server->default_root = values[0];
			else if (directive == "index") server->default_index = values;
			else if (directive == "upload_dir") server->upload_dir = values[0];
			else if (directive == "client_max_body_size" && !values.empty())
				server->client_max_body_size = ConfigUtils::parseSizeWithUnit(values[0], line);
			else if (directive == "error_page" && values.size() >= 2) {
				int code;
				std::istringstream iss(values[0]);
				if (iss >> code)
					server->error_pages[code] = values[1];
			}
			else if (directive == "connection_timeout" && !values.empty())
				server->connection_timeout = ConfigUtils::parseTimeWithUnit(values[0], line);
			else if (directive == "max_connections" && !values.empty())
				server->max_connections = ConfigUtils::parseSizeWithUnit(values[0], line);
			else if (directive == "cgi_timeout" && !values.empty())
				server->cgi_timeout = ConfigUtils::parseTimeWithUnit(values[0], line);
			else if (directive == "cgi_max_processes" && !values.empty())
				server->cgi_max_processes = ConfigUtils::parseSizeWithUnit(values[0], line);
			else if (directive == "client_header_timeout" && !values.empty())
				server->client_header_timeout = ConfigUtils::parseTimeWithUnit(values[0], line);
			else if (directive == "client_body_timeout" && !values.empty())
				server->client_body_timeout = ConfigUtils::parseTimeWithUnit(values[0], line);
			else if (directive == "return") {
				if (values.size() == 1) {
					server->return_code = std::atoi(values[0].c_str());
				} else if (values.size() >= 2) {
					server->return_code = std::atoi(values[0].c_str());
					server->return_url = values[1];
				} else {
					throw std::runtime_error("'return' directive requires a code or code+url at line " + Utils::toString(line));
				}
			}
			else if (directive == "deny") {
				if (values.size() == 1 && values[0] == "all") {
					server->deny_all = true;
				} else {
					server->denied_ips = values;
				}
			}
		}
	} catch (const std::exception& e) {
		Logger::error(e.what()); // Catch and report any parsing/validation errors
		return false;
	}

	return true;
}

// ------------------- Validate Directive -------------------
// Checks if a directive is allowed in the given context (events, server, or location).
// Also verifies that the directive has at least one value.
// Throws std::runtime_error if validation fails.
//
// Parameters:
//   directive - the directive name (e.g., "listen")
//   values    - vector of values assigned to the directive
//   context   - the context where directive appears ("events", "server", "location")
//   line      - line number in the config file (for error reporting)
void ConfigParser::validateDirective(const std::string& directive, 
									const std::vector<std::string>& values,
									const std::string& context, int line) {
	typedef std::map<std::string, std::vector<std::string> > DirectiveMap;
	DirectiveMap valid_directives;
	
	// Define allowed contexts for each directive
	valid_directives["cgi_timeout"] = ConfigUtils::makeVector("events", "server", "location");
	valid_directives["connection_timeout"] = ConfigUtils::makeVector("events", "server");
	valid_directives["max_connections"] = ConfigUtils::makeVector("events", "server");
	valid_directives["root"] = ConfigUtils::makeVector("server", "location");
	valid_directives["index"] = ConfigUtils::makeVector("server", "location");
	valid_directives["upload_dir"] = ConfigUtils::makeVector("server", "location");
	valid_directives["listen"] = std::vector<std::string>(1, "server");
	valid_directives["server_name"] = std::vector<std::string>(1, "server");
	valid_directives["client_max_body_size"] = ConfigUtils::makeVector("server", "location");
	valid_directives["return"] = ConfigUtils::makeVector("server", "location");
	valid_directives["deny"] = ConfigUtils::makeVector("server", "location");
	valid_directives["error_page"] = std::vector<std::string>(1, "server");
	valid_directives["autoindex"] = std::vector<std::string>(1, "location");
	valid_directives["allowed_methods"] = std::vector<std::string>(1, "location");
	valid_directives["cgi_pass"] = std::vector<std::string>(1, "location");
	valid_directives["client_header_timeout"] = std::vector<std::string>(1, "server");
	valid_directives["client_body_timeout"] = std::vector<std::string>(1, "server");
	valid_directives["upload_enable"] = std::vector<std::string>(1, "location");
	valid_directives["cgi_path"] = std::vector<std::string>(1, "location");
	valid_directives["cgi_ext"] = std::vector<std::string>(1, "location");
	valid_directives["cgi_enable"] = std::vector<std::string>(1, "location");
	valid_directives["cgi_max_processes"] = ConfigUtils::makeVector("events", "server", "location");

	// Check if the directive exists
	DirectiveMap::const_iterator it = valid_directives.find(directive);
	if (it == valid_directives.end()) {
		throw std::runtime_error("Unknown directive '" + directive + "' at line " + Utils::toString(line));
	}
	
	// Check if the directive is allowed in the current context
	const std::vector<std::string>& allowed_contexts = it->second;
	if (std::find(allowed_contexts.begin(), allowed_contexts.end(), context) == allowed_contexts.end()) {
		throw std::runtime_error("Directive '" + directive + "' not allowed in '" + context + 
								"' context at line " + Utils::toString(line));
	}
	
	// Ensure directive has at least one value
	if (values.empty()) {
		throw std::runtime_error("Directive '" + directive + "' requires values at line " + Utils::toString(line));
	}
}
