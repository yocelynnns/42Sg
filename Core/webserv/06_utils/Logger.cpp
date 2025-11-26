#include "Logger.hpp"
#include <sys/time.h>   // for gettimeofday
#include <ctime>
#include <cstdio>

std::ofstream Logger::logfile_;
bool Logger::use_file_ = false;
Logger::Level Logger::min_level_ = Logger::INFO;

void Logger::init(const std::string &filename)
{
	if (!filename.empty())
	{
		logfile_.open(filename.c_str(), std::ios::out | std::ios::app);
		if (logfile_.is_open())
		{
			use_file_ = true;
			info("Logger initialized with file: " + filename);
		}
		else
		{
			std::cerr << "[ERROR] Failed to open log file: " << filename << std::endl;
		}
	}
}

void Logger::shutdown()
{
	if (logfile_.is_open())
	{
		logfile_.close();
	}
	use_file_ = false;
}

void Logger::setLevel(Level level)
{
	min_level_ = level;
}

Logger::Level Logger::getLevel()
{
	return min_level_;
}

void Logger::info(const std::string &msg) { log(INFO, msg); }
void Logger::warn(const std::string &msg) { log(WARN, msg); }
void Logger::error(const std::string &msg) { log(ERROR, msg); }
void Logger::debug(const std::string &msg) { log(DEBUG, msg); }

void Logger::log(Level level, const std::string &msg)
{
	if (level < min_level_)
		return;

	// Timestamp with milliseconds
	struct timeval tv;
	gettimeofday(&tv, NULL);

	char timebuf[64];
	std::tm *lt = std::localtime(&tv.tv_sec);
	std::strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", lt);

	char fullbuf[80];
	std::snprintf(fullbuf, sizeof(fullbuf), "%s.%03ld", timebuf, (long)(tv.tv_usec / 1000));

	std::string prefix = "[" + std::string(fullbuf) + "] " + levelToString(level) + " ";
	std::string output = prefix + msg;

	std::string colored = levelToColor(level) + output + "\033[0m";

	if (level == ERROR)
		std::cerr << colored << std::endl;
	else
		std::cout << colored << std::endl;

	if (use_file_ && logfile_.is_open())
	{
		logfile_ << output << std::endl;
	}
}

std::string Logger::levelToString(Level level)
{
	switch (level)
	{
	case INFO:  return "[INFO] ";
	case WARN:  return "[WARN] ";
	case ERROR: return "[ERROR]";
	case DEBUG: return "[DEBUG]";
	}
	return "[UNKNOWN]";
}

std::string Logger::levelToColor(Level level)
{
	switch (level)
	{
	case INFO:  return "\033[32m"; // Green
	case WARN:  return "\033[33m"; // Yellow
	case ERROR: return "\033[31m"; // Red
	case DEBUG: return "\033[36m"; // Cyan
	}
	return "\033[0m"; // Reset
}
