#ifndef WEBSERV_06_UTILS_HPP
#define WEBSERV_06_UTILS_HPP

#include <string>
#include <sstream>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>
#include <iomanip>  // For std::setw and std::setfill

namespace Utils {
	// Template function for converting any type to string
	template <typename T>
	std::string toString(const T& value) {
		std::ostringstream oss;
		oss << value;
		return oss.str();
	}

	// Convert string to integer (safe version)
	inline int toInt(const std::string& str) {
		if (str.empty()) return 0;
		
		size_t start = str.find_first_not_of(" \t\r\n");
		size_t end = str.find_last_not_of(" \t\r\n");
		
		if (start == std::string::npos) return 0;
		
		std::string trimmed = str.substr(start, end - start + 1);
		char* end_ptr;
		long result = std::strtol(trimmed.c_str(), &end_ptr, 10);
		
		if (end_ptr == trimmed.c_str() || *end_ptr != '\0') return 0;
		if (result > INT_MAX) return INT_MAX;
		if (result < INT_MIN) return INT_MIN;
		
		return static_cast<int>(result);
	}

	// Trim whitespace from string
	inline std::string trim(const std::string& str) {
		size_t start = str.find_first_not_of(" \t\r\n");
		if (start == std::string::npos) return "";
		size_t end = str.find_last_not_of(" \t\r\n");
		return str.substr(start, end - start + 1);
	}

	// To lower case
	inline std::string toLowerCase(const std::string& str)
	{
		std::string result = str;
		for (size_t i = 0; i < result.length(); ++i) {
			result[i] = std::tolower(result[i]);
		}
		return result;
	}
}

#endif
