#ifndef WEBSERV_06_UTILS_LOGGER_HPP
#define WEBSERV_06_UTILS_LOGGER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include "../06_utils/Utils.hpp"

// -----------------------------------------------------------------------------
// Logger
// -----------------------------------------------------------------------------
// Simple logging utility with levels and optional file output.
//
// Usage:
//   Logger::init("webserv.log"); // optional file logging
//   Logger::info("Server started");
//   Logger::error("Socket bind failed");
//
// Levels: INFO, WARN, ERROR, DEBUG
// -----------------------------------------------------------------------------
class Logger {
public:
	enum Level {
		DEBUG,
		INFO,
		WARN,
		ERROR
	};

	// Initialize with optional log file
	static void init(const std::string& filename = "");

	// Logging methods
	static void info(const std::string& msg);
	static void warn(const std::string& msg);
	static void error(const std::string& msg);
	static void debug(const std::string& msg);

	// Cleanup resources
	static void shutdown();

	// Control log level (everything below min_level will be ignored)
	static void setLevel(Level level);
	static Level getLevel();

private:
	static void log(Level level, const std::string& msg);
	static std::string levelToString(Level level);
	static std::string levelToColor(Level level);

	static std::ofstream logfile_;
	static bool use_file_;
	static Level min_level_;   // 👈 added for filtering
};

#endif // WEBSERV_06_UTILS_LOGGER_HPP
