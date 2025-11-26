#ifndef WEBSERV_01_CONFIG_CONFIGPARSER_HPP
#define WEBSERV_01_CONFIG_CONFIGPARSER_HPP

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "Config.hpp"

// ------------------- Token -------------------
// Represents a single token extracted from the configuration file.
// Each token has:
//  - value: the text of the token (e.g., "server", "{", "listen")
//  - line: the line number in the file (for error reporting)
struct Token {
	std::string value;
	int line;

	Token(); // Default constructor
	Token(const std::string& v, int l); // Constructor with value and line
};

// ------------------- ConfigParser -------------------
// Parses a web server configuration file and fills the GlobalConfig structure.
// Responsible for:
//  - Tokenizing the input file
//  - Parsing blocks: events, http, server, location
//  - Validating directives and applying them to the appropriate context
class ConfigParser {
public:
	ConfigParser(); // Constructor

	// Parses a configuration file and updates the given GlobalConfig object
	// Returns true on success, false on error
	bool parseFile(const std::string& filename, GlobalConfig& global_config);

private:
	// ------------------- Block Parsing Functions -------------------
	bool parseEventsBlock(std::vector<Token>& tokens, size_t& index, GlobalConfig& global_config);
	bool parseHttpBlock(std::vector<Token>& tokens, size_t& index, HttpConfig& http, GlobalConfig& global_config);
	bool parseServerBlock(std::vector<Token>& tokens, size_t& index, ServerConfig& server);
	bool parseLocationBlock(std::vector<Token>& tokens, size_t& index, Location& location);

	// ------------------- Directive Parsing -------------------
	// Parses a single directive and applies it to the correct context:
	//  - server (ServerConfig)
	//  - location (Location)
	//  - events (EventsConfig)
	bool parseDirective(const std::vector<Token>& tokens, size_t& index, 
						ServerConfig* server, Location* location, EventsConfig* events);

	// ------------------- Utility Parsing Functions -------------------
	// Tokenizes the input stream into a vector of Tokens
	std::vector<Token> tokenize(std::istream& input);

	// Validates that a directive is allowed in the given context
	// Throws std::runtime_error if directive is invalid
	void validateDirective(const std::string& directive, 
						const std::vector<std::string>& values,
						const std::string& context, int line);
};

#endif
