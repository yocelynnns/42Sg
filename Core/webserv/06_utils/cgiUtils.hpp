#ifndef WEBSERV_06_UTILS_CGI_UTILS_HPP
#define WEBSERV_06_UTILS_CGI_UTILS_HPP

#include <string>
#include <map>
#include <sstream>
#include <cstdlib>
#include "../06_utils/Utils.hpp"
#include "../04_cgi/CGI.hpp"

namespace CGIUtils {

	// ------------------------------
	// Helper function to create a query string from parameters (key=value&key2=value2)
	// ------------------------------
	inline std::string makeQueryString(const std::map<std::string, std::string>& params) {
		std::ostringstream oss;
		std::map<std::string,std::string>::const_iterator it = params.begin();
		while (it != params.end()) {
			oss << it->first << '=' << it->second; // optionally URL-encode
			++it;
			if (it != params.end()) oss << '&';
		}
		return oss.str();
	}

	// Parse Status line to get HTTP status code
	inline void parseStatusLine(const std::string& status_line, CGIResponse& result) {
		size_t space_pos = status_line.find(' ');
		if (space_pos != std::string::npos) {
			std::string status_code_str = status_line.substr(space_pos + 1, 3);
			result.http_status = Utils::toInt(status_code_str);
		}
	}

	// ------------------------------
	// Determine HTTP status code if not explicitly set
	// ------------------------------
	inline void extractHttpStatus(CGIResponse& result) {
		if (result.http_status == 200) {
			if (result.timed_out) {
				result.http_status = 504; // Gateway Timeout
			} else if (result.exit_code != 0) {
				result.http_status = 500; // Internal Server Error
			}
		}
	}

	// Determine if CGI execution was successful
	inline void setSuccessFlag(CGIResponse& result) {
		result.success = (!result.timed_out && result.exit_code == 0 && result.http_status >= 200 && result.http_status < 300);
	}

	// ------------------------------
	// Parse CGI output into headers and body
	// ------------------------------
	inline void parseCGIOutput(const std::string& output, CGIResponse& result) {
		std::stringstream ss(output);
		std::string line;
		bool in_headers = true;
		
		while (std::getline(ss, line)) {
			// Remove carriage return (\r)
			if (!line.empty() && line[line.size() - 1] == '\r') {
				line = line.substr(0, line.size() - 1);
			}
			
			// Empty line separates headers from body
			if (line.empty()) {
				in_headers = false;
				continue;
			}
			
			if (in_headers) {
				// Parse Status header if present
				if (line.find("Status:") == 0) {
					parseStatusLine(line, result);
					continue;
				}
				
				// Parse other headers
				size_t colon_pos = line.find(':');
				if (colon_pos != std::string::npos) {
					std::string name = line.substr(0, colon_pos);
					std::string value = line.substr(colon_pos + 1);
					Utils::trim(name);
					Utils::trim(value);
					result.headers[name] = value;
				}
			} else {
				// Append body content
				result.body += line + "\n";
			}
		}
		
		// Remove trailing newline
		if (!result.body.empty() && result.body[result.body.size() - 1] == '\n') {
			result.body = result.body.substr(0, result.body.size() - 1);
		}
	}

	// ------------------------------
	// Generate debug info string for a CGIRequest
	// ------------------------------
	inline std::string generateDebugInfo(const CGIRequest& req) {
		std::stringstream ss;
		ss << "CGI Request Debug Info:\n";
		ss << "Script: " << req.script_path << "\n";
		ss << "Interpreter: " << req.interpreter << "\n";
		ss << "Working Directory: " << req.working_dir << "\n";
		ss << "Script Arguments: " << req.script_args.size() << "\n";
		for (size_t i = 0; i < req.script_args.size(); i++) {
			ss << "  " << i << ": " << req.script_args[i] << "\n";
		}
		ss << "Environment Variables: " << req.env.size() << "\n";
		for (std::map<std::string, std::string>::const_iterator it = req.env.begin();
			it != req.env.end(); ++it) {
			ss << "  " << it->first << "=" << it->second << "\n";
		}
		ss << "Stdin Data Size: " << req.stdin_data.size() << " bytes\n";
		
		return ss.str();
	}

}

#endif
