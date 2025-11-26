#ifndef WEBSERV_04_CGI_CGI_HPP
#define WEBSERV_04_CGI_CGI_HPP

#include <string>
#include <vector>
#include <map>
#include <set>
#include <ctime>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>

#include <sys/stat.h>

#include "01_config/Config.hpp"
#include "02_http/Request.hpp"
#include "03_handlers/Handler.hpp"

// Forward declarations
struct CGIInterpreter;  // Represents a specific interpreter (Python, PHP, etc.)
struct CGIRequest;      // Represents a CGI request to execute
struct CGIResponse;     // Represents the CGI response returned after execution
struct CGIStats;        // Keeps track of CGI statistics
struct CGIProcess;      // Could represent a running CGI process (optional)

// ------------------------------
// CGI Interpreter Configuration
// ------------------------------
struct CGIInterpreter {
	std::string extension;        // File extension, e.g., ".py", ".php"
	std::string interpreter_path; // Path to interpreter, e.g., "/usr/bin/python3"
	std::vector<std::string> args; // Optional additional args for the interpreter

	CGIInterpreter();

	CGIInterpreter(const std::string& ext, const std::string& path, 
			const std::vector<std::string>& a = std::vector<std::string>());
};

// ------------------------------
// Enhanced CGI Request
// ------------------------------
struct CGIRequest {
	std::string script_path;              // Absolute path to script
	std::string req_script_path;          // Request script path
	std::string interpreter;              // Interpreter to execute
	std::map<std::string, std::string> env; // Environment variables
	std::string stdin_data;               // Data to feed via stdin (POST body)
	std::string working_dir;              // Working directory for script
	std::vector<std::string> script_args; // Additional command-line args

	CGIRequest();
	
	CGIRequest(const std::string& script, const std::string& interp, 
		const std::map<std::string, std::string>& environment,
		const std::string& stdin_data = "",
		const std::string& wd = ".",
		const std::vector<std::string>& args = std::vector<std::string>());
};

// ------------------------------
// Enhanced CGI Response
// ------------------------------
struct CGIResponse {
	std::map<std::string, std::string> headers; // Headers parsed from CGI output
	std::string body;                           // Body content of CGI
	int exit_code;                              // Exit code from child process
	bool timed_out;                             // True if process timed out
	std::string error_output;                   // stderr output from CGI

	// Convenience fields
	bool success;       // True if exit_code == 0 and no error
	int http_status;    // HTTP status determined from CGI output or exit code

	// Debug information
	std::map<std::string, std::string> environment; // Environment variables actually passed
	std::string executed_command;                   // Full command executed
	long execution_time_ms;                         // Execution time in milliseconds
	time_t start_time;                              // Timestamp of execution start

	// ------------------------------
	// Helper methods
	// ------------------------------
	size_t getContentLength() const;
	bool hasHeaders() const;
	std::string getHeader(const std::string& name) const;
	bool hasHeader(const std::string& name) const;

	CGIResponse();
};

// ------------------------------
// CGI Statistics
// ------------------------------
struct CGIStats {
	size_t total_executions;           // Total scripts executed
	size_t successful_executions;      // Number of successful scripts
	size_t timed_out_executions;       // Number of scripts that timed out
	size_t failed_executions;          // Number of failed scripts
	std::map<std::string, size_t> executions_by_extension; // Count by file type
	std::map<std::string, size_t> executions_by_script;    // Count per script
	long total_execution_time_ms;      // Cumulative execution time
	
	// Enhanced statistics
	std::map<int, size_t> executions_by_status; // Count by HTTP status
	size_t total_content_bytes;                 // Total bytes returned

	// Helper methods
	double getSuccessRate() const;
	double getAverageExecutionTime() const;
	double getAverageResponseSize() const;
	std::string getMostUsedExtension() const;

	CGIStats();
};

struct PendingCGI {
	pid_t pid;
	int stdout_fd;
	int stderr_fd;
	int stdin_fd;  // Only if you need to write to stdin
	time_t start_time;
	std::string stdout_buffer;
	std::string stderr_buffer;
	int client_fd;  // Connection fd to send response back to
	CGIRequest request;
	int timeout_seconds;
	bool process_complete;
	bool headers_parsed;
	CGIResponse response;
};

// ------------------------------
// Main CGI class
// ------------------------------
class CGI {
private:
	std::map<std::string, CGIInterpreter> interpreters;	// Map extension -> interpreter
	std::set<pid_t> active_processes; 					// Track active processes
	std::map<pid_t, PendingCGI> pending_processes_;		// Track active CGI processes
	std::vector<std::pair<int, CGIResponse> > completed_responses_; // Completed responses

	CGIStats stats;              // Track statistics

	// Private methods
	void registerProcess(pid_t pid);      // Add pid to active_processes
	void unregisterProcess(pid_t pid);    // Remove pid
	
	void updateStats(const CGIResponse& response, const std::string& script_path, 
					const std::string& extension); // Update statistics

	// Build CGIRequest data from server Request and location config
	CGIRequest buildCGIRequest(HandlerContext& ctx) const;

	// Build environment variables for CGI execution
	std::map<std::string, std::string> buildEnvironment(HandlerContext& ctx) const;

	// Non-blocking process management
	bool startProcess(const CGIRequest& req, PendingCGI& pending, int client_fd, int timeout_seconds);
	void checkProcessCompletion(PendingCGI& pending);
	void cleanupProcess(PendingCGI& pending);
	void readAvailableData(PendingCGI& pending);

public:
	CGI();
	~CGI();
	
	// Interpreter management
	void addInterpreter(const std::string& extension, const std::string& interpreter_path, 
					const std::vector<std::string>& args = std::vector<std::string>());
	bool supportsCGI(const std::string& file_extension) const;
	
	void removeInterpreter(const std::string& extension);
	std::vector<std::string> getSupportedExtensions() const;
	CGIInterpreter getInterpreter(const std::string& extension) const;
	
	// Statistics access
	CGIStats getStats() const;
	void resetStats();
	
	// Process management
	size_t getActiveProcessCount() const;
	void killAllActiveProcesses();
	size_t getMaxProcesses(HandlerContext& ctx) const;
	bool canExecute(HandlerContext& ctx) const;

	int getTimeout(HandlerContext& ctx) const;

	// Non-blocking execution
	bool executeAsync(HandlerContext& ctx, int client_fd);
	void checkAllProcesses();
	std::vector<std::pair<int, CGIResponse> > getCompletedProcesses();

};

#endif // WEBSERV_04_CGI_CGI_HPP
