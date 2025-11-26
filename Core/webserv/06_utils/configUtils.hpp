#ifndef WEBSERV_06_UTILS_CONFIG_UTILS_HPP
#define WEBSERV_06_UTILS_CONFIG_UTILS_HPP

#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <map>
#include "../06_utils/Utils.hpp"

namespace ConfigUtils {
	// ------------------- Parse Size with Unit -------------------
	// Converts a string representing size (with optional units) into a size_t value.
	// Supports units: K (kilobytes), M (megabytes), G (gigabytes).
	// Throws runtime_error if the value is invalid.
	//
	// Example inputs: "1024", "2K", "5M", "1G"
	inline size_t parseSizeWithUnit(const std::string& sizeStr, int line = 0) {
		if (sizeStr.empty()) {
			throw std::runtime_error("Empty size value at line " + Utils::toString(line));
		}
		
		char unit = sizeStr[sizeStr.size() - 1];
		std::string numberStr = sizeStr;
		size_t multiplier = 1;

		if (std::isalpha(static_cast<unsigned char>(unit))) {
			numberStr = sizeStr.substr(0, sizeStr.size() - 1);
			switch (std::tolower(static_cast<unsigned char>(unit))) {
				case 'k': multiplier = 1024; break;
				case 'm': multiplier = 1024 * 1024; break;
				case 'g': multiplier = 1024 * 1024 * 1024; break;
				default:
					throw std::runtime_error("Unknown size unit '" + std::string(1, unit) +
										"' at line " + Utils::toString(line));
			}
		}

		std::istringstream iss(numberStr);
		size_t value;
		if (!(iss >> value)) {
			throw std::runtime_error("Invalid size value '" + sizeStr +
								"' at line " + Utils::toString(line));
		}

		return value * multiplier;
	}

	// ------------------- Parse Time with Unit -------------------
	// Converts a string representing time (with optional units) into an integer (seconds).
	// Supported units: s (seconds), m (minutes), h (hours).
	// Throws runtime_error if the value is invalid.
	//
	// Example inputs: "30", "15s", "2m", "1h"
	inline int parseTimeWithUnit(const std::string& timeStr, int line = 0) {
		if (timeStr.empty()) {
			throw std::runtime_error("Empty time value at line " + Utils::toString(line));
		}

		char unit = timeStr[timeStr.size() - 1];
		std::string numberStr = timeStr;
		int multiplier = 1;

		// Check for unit suffix using std::isalpha / std::tolower
		if (std::isalpha(static_cast<unsigned char>(unit))) {
			numberStr = timeStr.substr(0, timeStr.size() - 1);
			switch (std::tolower(static_cast<unsigned char>(unit))) {
				case 's': multiplier = 1; break;
				case 'm': multiplier = 60; break;
				case 'h': multiplier = 3600; break;
				default:
					throw std::runtime_error("Unknown time unit '" + std::string(1, unit) +
										"' at line " + Utils::toString(line));
			}
		}

		std::istringstream iss(numberStr);
		int value;
		if (!(iss >> value)) {
			throw std::runtime_error("Invalid time value '" + timeStr +
								"' at line " + Utils::toString(line));
		}

		return value * multiplier;
	}

	// ------------------- Helper: makeVector -------------------
	// Utility functions to quickly construct a std::vector<std::string>
	// from 1, 2, or 3 C-style strings.
	inline std::vector<std::string> makeVector(const char* first) {
		std::vector<std::string> v;
		v.push_back(first);
		return v;
	}

	inline std::vector<std::string> makeVector(const char* first, const char* second) {
		std::vector<std::string> v;
		v.push_back(first);
		v.push_back(second);
		return v;
	}

	inline std::vector<std::string> makeVector(const char* first, const char* second, const char* third) {
		std::vector<std::string> v;
		v.push_back(first);
		v.push_back(second);
		v.push_back(third);
		return v;
	}
}

#endif
