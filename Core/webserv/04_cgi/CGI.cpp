#include "../04_cgi/CGI.hpp"
#include "../06_utils/Logger.hpp"
#include "../06_utils/Utils.hpp"
#include "../06_utils/cgiUtils.hpp"

//-----CGIInterpreter-----
CGIInterpreter::CGIInterpreter() {}

CGIInterpreter::CGIInterpreter(const std::string& ext, const std::string& path, 
							const std::vector<std::string>& a)
	: extension(ext), interpreter_path(path), args(a) {}

//-----CGIRequest-----
CGIRequest::CGIRequest() {}

CGIRequest::CGIRequest(const std::string& script, const std::string& interp, 
					const std::map<std::string, std::string>& environment,
					const std::string& stdin_data,
					const std::string& wd,
					const std::vector<std::string>& args)
	: script_path(script), interpreter(interp), env(environment),
	stdin_data(stdin_data), working_dir(wd), script_args(args) {}

//-----CGIResponse-----
size_t CGIResponse::getContentLength() const { 
		return body.size(); 
	}
	
bool CGIResponse::hasHeaders() const { 
	return !headers.empty(); 
}

std::string CGIResponse::getHeader(const std::string& name) const {
	std::map<std::string, std::string>::const_iterator it = headers.find(name);
	return it != headers.end() ? it->second : "";
}

bool CGIResponse::hasHeader(const std::string& name) const {
	return headers.find(name) != headers.end();
}

CGIResponse::CGIResponse() : exit_code(-1), timed_out(false), success(false), 
				http_status(200), execution_time_ms(0), start_time(0) {}

//-----CGIStats-----
double CGIStats::getSuccessRate() const {
	if (total_executions > 0) {
		return (successful_executions * 100.0 / total_executions);
	} else {
		return 0;
	}
}

double CGIStats::getAverageExecutionTime() const {
	if (total_executions > 0) {
		return (total_execution_time_ms / static_cast<double>(total_executions));
	} else {
		return 0;
	}
}

double CGIStats::getAverageResponseSize() const {
	if (total_executions > 0) {
		return (total_content_bytes / static_cast<double>(total_executions));
	} else {
		return 0;
	}
}

std::string CGIStats::getMostUsedExtension() const {
	if (executions_by_extension.empty()) return "";
	std::map<std::string, size_t>::const_iterator max_it = executions_by_extension.begin();
	for (std::map<std::string, size_t>::const_iterator it = executions_by_extension.begin(); 
			it != executions_by_extension.end(); ++it) {
		if (it->second > max_it->second) {
			max_it = it;
		}
	}
	return max_it->first;
}

CGIStats::CGIStats() : total_executions(0), successful_executions(0), timed_out_executions(0),
			failed_executions(0), total_execution_time_ms(0), total_content_bytes(0) {}

CGI::CGI() {  // ✅ Remove default_timeout
	Logger::debug("CGI module initialized - limits will be determined from config");
}

// Destructor - clean up any running processes
CGI::~CGI() {
	// Kill all active CGI processes when CGI object is destroyed
	killAllActiveProcesses();
}

// Add a CGI interpreter for a specific file extension
void CGI::addInterpreter(const std::string& extension, const std::string& interpreter_path, 
					const std::vector<std::string>& args) {
	interpreters[extension] = CGIInterpreter(extension, interpreter_path, args);
	Logger::debug("Added CGI interpreter for " + extension + ": " + interpreter_path);
}

// Check if a file extension is supported by CGI
bool CGI::supportsCGI(const std::string& file_extension) const {
	return interpreters.find(file_extension) != interpreters.end();
}

// Remove an interpreter for a specific extension
void CGI::removeInterpreter(const std::string& extension) {
	std::map<std::string, CGIInterpreter>::iterator it = interpreters.find(extension);
	if (it != interpreters.end()) {
		interpreters.erase(it);
		Logger::debug("Removed CGI interpreter for " + extension);
	}
}

// Return all supported file extensions
std::vector<std::string> CGI::getSupportedExtensions() const {
	std::vector<std::string> extensions;
	for (std::map<std::string, CGIInterpreter>::const_iterator it = interpreters.begin();
		it != interpreters.end(); ++it) {
		extensions.push_back(it->first);
	}
	return extensions;
}

// Retrieve interpreter configuration for a specific extension
CGIInterpreter CGI::getInterpreter(const std::string& extension) const {
	std::map<std::string, CGIInterpreter>::const_iterator it = interpreters.find(extension);
	if (it != interpreters.end()) {
		return it->second;
	}
	return CGIInterpreter(); // Return empty/default interpreter if not found
}

// Build the environment variables for a CGI script execution
std::map<std::string, std::string> CGI::buildEnvironment(HandlerContext& ctx) const {
	std::map<std::string, std::string> env;

	Logger::debug("=== CGI::buildEnvironment CALLED ===");
	
	const std::string& script_path = ctx.req.getResolvedPath();
	const std::string& req_script_path = ctx.req.getReqPath();
	
	Logger::debug("script_path: " + script_path);
	Logger::debug("req_script_path: " + req_script_path);
	Logger::debug("location root: " + ctx.loc->root);
	Logger::debug("location path: " + ctx.loc->path);

	// Required CGI variables
	env["GATEWAY_INTERFACE"] = "CGI/1.1";
	env["SERVER_SOFTWARE"]   = "Webserv/1.0";
	env["SERVER_NAME"]       = ctx.req.getHost();
	env["SERVER_PROTOCOL"]   = "HTTP/1.1";
	env["PHP_SELF"] = req_script_path;

	// CRITICAL FOR PHP: Add REDIRECT_STATUS
	env["REDIRECT_STATUS"] = "200";

	// Request-specific variables
	env["REQUEST_METHOD"]  = HttpUtils::methodToString(ctx.req.getMethod());
	env["REQUEST_URI"]     = ctx.req.getPath();
	env["QUERY_STRING"]    = CGIUtils::makeQueryString(ctx.req.parseQueryString());
	env["SCRIPT_NAME"]     = req_script_path;
	env["SCRIPT_FILENAME"] = script_path;
	env["PATH_INFO"]       = "";
	env["PATH_TRANSLATED"] = script_path;

	// FIXED: Set DOCUMENT_ROOT correctly using location root
	std::string doc_root = ctx.loc->root;
	if (doc_root.empty()) {
		doc_root = ctx.config.default_root;
	}
	
	Logger::debug("buildEnvironment - Final DOCUMENT_ROOT: " + doc_root);
	env["DOCUMENT_ROOT"] = doc_root;

	// Content information if provided
	if (ctx.req.hasHeader("Content-Type"))
		env["CONTENT_TYPE"] = ctx.req.getHeader("Content-Type");
	if (ctx.req.hasHeader("Content-Length"))
		env["CONTENT_LENGTH"] = ctx.req.getHeader("Content-Length");

	// HTTP headers prefixed with HTTP_ (standard CGI format)
	const std::map<std::string,std::string>& headers = ctx.req.getAllHeaders();
	for (std::map<std::string,std::string>::const_iterator it = headers.begin();
		it != headers.end(); ++it)
	{
		std::string env_name = "HTTP_";
		for (std::string::size_type i = 0; i < it->first.size(); ++i)
		{
			char c = it->first[i];
			if (c == '-') env_name += '_';
			else env_name += static_cast<char>(std::toupper(c));
		}
		env[env_name] = it->second;
	}

	// Server port
	env["SERVER_PORT"] = Utils::toString(ctx.config.port);

	return env;
}

// Build CGI request from HandlerContext
CGIRequest CGI::buildCGIRequest(HandlerContext& ctx) const {
	CGIRequest cgi_req;

	// ------------------------
	// USE PRE-RESOLVED PATH FROM REQUEST
	cgi_req.script_path = ctx.req.getResolvedPath();
	cgi_req.req_script_path = ctx.req.getReqPath();
	
	// Working directory is the directory containing the script
	size_t last_slash = cgi_req.script_path.find_last_of('/');
	if (last_slash != std::string::npos) {
		cgi_req.working_dir = cgi_req.script_path.substr(0, last_slash);
	} else {
		cgi_req.working_dir = ".";
	}

	Logger::debug("CGI::buildCGIRequest - Using resolved script path: " + cgi_req.script_path);
	Logger::debug("CGI::buildCGIRequest - Working dir: " + cgi_req.working_dir);

	// ------------------------
	// Check if the script exists - should already be validated by resolvePath
	struct stat file_info;
	if (stat(cgi_req.script_path.c_str(), &file_info) != 0) {
		throw std::runtime_error("CGI script not found: " + cgi_req.script_path);
	}

	// ------------------------
	// Check if it is a regular file
	if (!S_ISREG(file_info.st_mode)) {
		throw std::runtime_error("CGI script is not a regular file: " + cgi_req.script_path);
	}

	// ------------------------
	// Check if file is executable
	if (access(cgi_req.script_path.c_str(), X_OK) != 0) {
		throw std::runtime_error("CGI script is not executable: " + cgi_req.script_path);
	}

	// ------------------------
	// Determine interpreter based on file extension
	// Use the resolved path to get the extension, not the request path
	size_t dot_pos = cgi_req.script_path.find_last_of('.');
	if (dot_pos != std::string::npos) {
		std::string ext = cgi_req.script_path.substr(dot_pos);
		
		// DEBUG: Log available interpreters
		Logger::debug("CGI::buildCGIRequest - Looking for interpreter for extension: " + ext);
		Logger::debug("CGI::buildCGIRequest - Available interpreters in location:");
		for (std::map<std::string, std::string>::const_iterator it = ctx.loc->cgi_interpreters.begin();
			it != ctx.loc->cgi_interpreters.end(); ++it) {
			Logger::debug("  " + it->first + " -> " + it->second);
		}
		Logger::debug("CGI::buildCGIRequest - Default interpreter: " + ctx.loc->default_cgi_interpreter);
		
		// First, try to find extension-specific interpreter
		std::map<std::string, std::string>::const_iterator it = ctx.loc->cgi_interpreters.find(ext);
		if (it != ctx.loc->cgi_interpreters.end()) {
			cgi_req.interpreter = it->second;
			Logger::debug("CGI::buildCGIRequest - Found interpreter: " + it->second);
		}
		// If not found, use default interpreter
		else if (!ctx.loc->default_cgi_interpreter.empty()) {
			cgi_req.interpreter = ctx.loc->default_cgi_interpreter;
			Logger::debug("CGI::buildCGIRequest - Using default interpreter: " + ctx.loc->default_cgi_interpreter);
		}
		// If still no interpreter, throw error
		else {
			throw std::runtime_error("No CGI interpreter configured for extension: " + ext);
		}
	} else {
		throw std::runtime_error("No file extension found in script path");
	}

	// Build CGI environment variables
	cgi_req.env = buildEnvironment(ctx);

	// If POST request, pass body as stdin
	if (ctx.req.getMethod() == POST) {
		cgi_req.stdin_data = ctx.req.getBody();
	}

	return cgi_req;
}

// Register an active CGI process
void CGI::registerProcess(pid_t pid) {
	active_processes.insert(pid);
}

// Unregister a finished CGI process
void CGI::unregisterProcess(pid_t pid) {
	active_processes.erase(pid);
}

// Update CGI execution statistics
void CGI::updateStats(const CGIResponse& response, const std::string& script_path, 
					const std::string& extension) {
	stats.total_executions++;
	
	if (response.success) {
		stats.successful_executions++;
	} else if (response.timed_out) {
		stats.timed_out_executions++;
	} else {
		stats.failed_executions++;
	}
	
	stats.executions_by_extension[extension]++;
	stats.executions_by_script[script_path]++;
	stats.executions_by_status[response.http_status]++;
	
	stats.total_execution_time_ms += response.execution_time_ms;
	stats.total_content_bytes += response.body.size();
}

// Get CGI statistics
CGIStats CGI::getStats() const {
	return stats;
}

// Reset statistics
void CGI::resetStats() {
	stats = CGIStats();
}

// Get number of currently active CGI processes
size_t CGI::getActiveProcessCount() const {
	return active_processes.size();
}

// Kill all active CGI processes
void CGI::killAllActiveProcesses() {
	for (std::set<pid_t>::const_iterator it = active_processes.begin();
		it != active_processes.end(); ++it) {
		kill(*it, SIGKILL);
	}
	active_processes.clear();
}

// Get max processes from config hierarchy: location -> server -> events -> default
size_t CGI::getMaxProcesses(HandlerContext& ctx) const {
	// Location value is already inherited from server if it was 0
	if (ctx.loc) {
		return ctx.loc->cgi_max_processes;
	}
	// Fallback to server value (which is already inherited from events if needed)
	return ctx.config.cgi_max_processes;
}

int CGI::getTimeout(HandlerContext& ctx) const {
	if (ctx.loc) {
		return ctx.loc->cgi_timeout;
	}
	return ctx.config.cgi_timeout;
}

// Check if a new CGI process can be executed (respecting config limits)
bool CGI::canExecute(HandlerContext& ctx) const {
	size_t max_processes = getMaxProcesses(ctx);
	bool can_exec = active_processes.size() < max_processes;
	
	if (!can_exec) {
		Logger::warn("CGI process limit reached (" + 
					Utils::toString(active_processes.size()) + "/" + 
					Utils::toString(max_processes) + ") for context");
	}
	
	return can_exec;
}

// Non-blocking process start
bool CGI::startProcess(const CGIRequest& req, PendingCGI& pending, int client_fd, int timeout_seconds) {
	Logger::debug("CGI::startProcess - ENTRY for script: " + req.script_path);
	
	int stdin_pipe[2] = {-1, -1};
	int stdout_pipe[2] = {-1, -1};
	int stderr_pipe[2] = {-1, -1};
	
	// Create non-blocking pipes
	if (pipe(stdout_pipe) < 0 || pipe(stderr_pipe) < 0) {
		Logger::error("Failed to create pipes for CGI execution");
		return false;
	}
	Logger::debug("CGI::startProcess - Pipes created successfully");
	
	// Set pipes to non-blocking
	fcntl(stdout_pipe[0], F_SETFL, O_NONBLOCK);
	fcntl(stderr_pipe[0], F_SETFL, O_NONBLOCK);
	
	// Create stdin pipe only if we have data to send
	if (!req.stdin_data.empty()) {
		if (pipe(stdin_pipe) < 0) {
			close(stdout_pipe[0]); close(stdout_pipe[1]);
			close(stderr_pipe[0]); close(stderr_pipe[1]);
			return false;
		}
		fcntl(stdin_pipe[1], F_SETFL, O_NONBLOCK);
	}
	
	Logger::debug("CGI::startProcess - About to fork()");
	pid_t pid = fork();
	
	if (pid < 0) {
		Logger::error("CGI::startProcess - Fork FAILED");
		// Cleanup pipes on fork failure
		close(stdout_pipe[0]); close(stdout_pipe[1]);
		close(stderr_pipe[0]); close(stderr_pipe[1]);
		if (stdin_pipe[0] != -1) { close(stdin_pipe[0]); close(stdin_pipe[1]); }
		return false;
	}
	
	if (pid == 0) {
		// ============ CHILD PROCESS ============
		Logger::debug("CGI::startProcess - CHILD process started");
		
		close(stdout_pipe[0]);
		close(stderr_pipe[0]);
		
		if (stdin_pipe[0] != -1) {
			close(stdin_pipe[1]);
			dup2(stdin_pipe[0], STDIN_FILENO);
			close(stdin_pipe[0]);
		} else {
			// If no stdin data, redirect from /dev/null
			int null_fd = open("/dev/null", O_RDONLY);
			if (null_fd >= 0) {
				dup2(null_fd, STDIN_FILENO);
				close(null_fd);
			}
		}
		
		dup2(stdout_pipe[1], STDOUT_FILENO);
		dup2(stderr_pipe[1], STDERR_FILENO);
		close(stdout_pipe[1]);
		close(stderr_pipe[1]);
		
		// Change working directory
		if (chdir(req.working_dir.c_str()) != 0) {
			exit(EXIT_FAILURE);
		}
		
		// Prepare environment
		std::vector<std::string> env_strings;
		for (std::map<std::string, std::string>::const_iterator it = req.env.begin();
			it != req.env.end(); ++it) {
			env_strings.push_back(it->first + "=" + it->second);
		}
		
		std::vector<char*> envp;
		for (size_t i = 0; i < env_strings.size(); ++i) {
			envp.push_back(const_cast<char*>(env_strings[i].c_str()));
		}
		envp.push_back(NULL);
		
		std::vector<char*> argv;
		argv.push_back(const_cast<char*>(req.interpreter.c_str()));
		argv.push_back(const_cast<char*>(req.script_path.c_str()));
		argv.push_back(NULL);
		
		// Execute
		execve(req.interpreter.c_str(),
			const_cast<char* const*>(&argv[0]),
			const_cast<char* const*>(&envp[0]));
		
		// If we get here, execve failed
		exit(EXIT_FAILURE);
		
	} else {
		// ============ PARENT PROCESS ============
		Logger::debug("CGI::startProcess - PARENT process, child PID=" + Utils::toString(pid));
		
		close(stdout_pipe[1]);
		close(stderr_pipe[1]);
		if (stdin_pipe[0] != -1) {
			close(stdin_pipe[0]);
		}
		
		// Initialize pending process tracking
		pending.pid = pid;
		pending.stdout_fd = stdout_pipe[0];
		pending.stderr_fd = stderr_pipe[0];
		pending.stdin_fd = (stdin_pipe[1] != -1) ? stdin_pipe[1] : -1;
		pending.start_time = time(NULL);
		pending.client_fd = client_fd;
		pending.request = req;
		pending.timeout_seconds = timeout_seconds;
		pending.process_complete = false;
		pending.headers_parsed = false;
		pending.response = CGIResponse();
		
		// Write stdin data if any (non-blocking)
		if (pending.stdin_fd != -1 && !req.stdin_data.empty()) {
			ssize_t written = write(pending.stdin_fd, req.stdin_data.c_str(), req.stdin_data.size());
			if (written < (ssize_t)req.stdin_data.size()) {
				Logger::warn("Partial write to CGI stdin");
			}
			close(pending.stdin_fd);
			pending.stdin_fd = -1;
		}
		
		registerProcess(pid);
		pending_processes_[pid] = pending;
		
		Logger::debug("CGI::startProcess - Process registered, pending_processes_ size=" + 
					Utils::toString(pending_processes_.size()));
		
		return true;
	}
}

// Main non-blocking execution entry point
bool CGI::executeAsync(HandlerContext& ctx, int client_fd) {
	Logger::debug("CGI::executeAsync - ENTRY for client_fd=" + Utils::toString(client_fd));
	
	if (!canExecute(ctx)) {
		Logger::error("CGI::executeAsync - canExecute returned false");
		return false;
	}
	
	try {
		Logger::debug("CGI::executeAsync - Building CGI request");
		CGIRequest cgi_req = buildCGIRequest(ctx);
		
		Logger::debug("CGI::executeAsync - CGI request built successfully");
		PendingCGI pending;
		
		// Use your existing getTimeout method
		int timeout = getTimeout(ctx);
		Logger::debug("CGI::executeAsync - Timeout set to: " + Utils::toString(timeout));
		
		Logger::debug("CGI::executeAsync - Calling startProcess");
		if (startProcess(cgi_req, pending, client_fd, timeout)) {
			Logger::debug("CGI::executeAsync - startProcess returned TRUE");
			return true;
		} else {
			Logger::error("CGI::executeAsync - startProcess returned FALSE");
			return false;
		}
		
	} catch (const std::exception& e) {
		Logger::error("CGI::executeAsync - Exception: " + std::string(e.what()));
	}
	
	return false;
}


// Check if a process has completed
void CGI::checkProcessCompletion(PendingCGI& pending) {
	if (pending.process_complete) return;

	// Check for timeout
	time_t current_time = time(NULL);
	if (current_time - pending.start_time > pending.timeout_seconds) {
		Logger::warn("CGI process timeout, killing PID: " + Utils::toString(pending.pid));
		kill(pending.pid, SIGKILL);
		pending.response.timed_out = true;
		pending.response.http_status = 504;
		pending.process_complete = true;
		return;
	}

	// Check if process has exited (non-blocking)
	int status;
	pid_t result = waitpid(pending.pid, &status, WNOHANG);
	
	if (result == 0) {
		// Process still running
		return;
	} else if (result == pending.pid) {
		// Process has exited
		if (WIFEXITED(status)) {
			pending.response.exit_code = WEXITSTATUS(status);
		} else if (WIFSIGNALED(status)) {
			pending.response.exit_code = -1;
			Logger::warn("CGI process terminated by signal: " + Utils::toString(WTERMSIG(status)));
		}
		pending.process_complete = true;
	} else if (result == -1) {
		// Error
		Logger::error("waitpid error for PID: " + Utils::toString(pending.pid));
		pending.process_complete = true;
		pending.response.http_status = 500;
	}
}

// Read available data from file descriptors
void CGI::readAvailableData(PendingCGI& pending) {
	char buffer[4096];
	ssize_t bytes_read;

	// Read from stdout
	bytes_read = read(pending.stdout_fd, buffer, sizeof(buffer));
	while (bytes_read > 0) {
		pending.stdout_buffer.append(buffer, bytes_read);
		bytes_read = read(pending.stdout_fd, buffer, sizeof(buffer));
	}

	// Read from stderr  
	bytes_read = read(pending.stderr_fd, buffer, sizeof(buffer));
	while (bytes_read > 0) {
		pending.stderr_buffer.append(buffer, bytes_read);
		bytes_read = read(pending.stderr_fd, buffer, sizeof(buffer));
	}
}

// Clean up a completed process
void CGI::cleanupProcess(PendingCGI& pending) {
	if (pending.stdout_fd != -1) {
		close(pending.stdout_fd);
		pending.stdout_fd = -1;
	}
	if (pending.stderr_fd != -1) {
		close(pending.stderr_fd);
		pending.stderr_fd = -1;
	}
	if (pending.stdin_fd != -1) {
		close(pending.stdin_fd);
		pending.stdin_fd = -1;
	}
	
	unregisterProcess(pending.pid);
}

// Check all pending processes
void CGI::checkAllProcesses() {
	// Logger::debug("CGI::checkAllProcesses - ENTRY, pending count=" + Utils::toString(pending_processes_.size()));
	
	std::vector<pid_t> to_remove;
	
	for (std::map<pid_t, PendingCGI>::iterator it = pending_processes_.begin();
		it != pending_processes_.end(); ++it) {
		
		PendingCGI& pending = it->second;
		Logger::debug("CGI::checkAllProcesses - Checking PID=" + Utils::toString(pending.pid) +
					" fd=" + Utils::toString(pending.client_fd));
		
		// Read available data
		readAvailableData(pending);
		Logger::debug("CGI::checkAllProcesses - After readAvailableData, stdout_buffer size=" + 
					Utils::toString(pending.stdout_buffer.size()));
		
		// Check if process completed
		checkProcessCompletion(pending);
		Logger::debug("CGI::checkAllProcesses - After checkProcessCompletion, process_complete=" + 
					Utils::toString(pending.process_complete));
		
		if (pending.process_complete) {
			Logger::debug("CGI::checkAllProcesses - Process PID=" + Utils::toString(pending.pid) + 
						" completed, finalizing response");
			
			if (!pending.response.timed_out) {
				// Parse CGI output only if not timed out and not killed by signal
				if (pending.response.exit_code != -1 && !pending.stdout_buffer.empty()) {
					CGIUtils::parseCGIOutput(pending.stdout_buffer, pending.response);
					pending.headers_parsed = true;
					Logger::debug("CGI::checkAllProcesses - Headers parsed");
				}

				// Set error output
				pending.response.error_output = pending.stderr_buffer;
				
				// Validate response
				if (!pending.response.hasHeaders() || !pending.response.hasHeader("Content-Type")) {
					Logger::warn("CGI output malformed: missing Content-Type header");
					pending.response.http_status = 502;
					pending.response.success = false;
				} else if (pending.response.exit_code != 0) {
					Logger::warn("CGI::checkAllProcesses - Non-zero exit code: " + 
								Utils::toString(pending.response.exit_code));
					pending.response.http_status = 502;
					pending.response.success = false;
				} else {
					Logger::info("CGI::checkAllProcesses - Response successful");
					pending.response.success = true;
				}
			} else {
				pending.response.success = false;
				pending.response.http_status = 504;
			}
			
			// Save to completed list
			completed_responses_.push_back(std::make_pair(pending.client_fd, pending.response));
			Logger::debug("CGI::checkAllProcesses - Saved response for fd=" + 
						Utils::toString(pending.client_fd));
			
			cleanupProcess(pending);
			to_remove.push_back(it->first);
		}
	}
	
	// Remove completed processes
	for (size_t i = 0; i < to_remove.size(); ++i) {
		Logger::debug("CGI::checkAllProcesses - Removing completed PID=" + 
					Utils::toString(to_remove[i]));
		pending_processes_.erase(to_remove[i]);
	}
	
	// Logger::debug("CGI::checkAllProcesses - EXIT, remaining pending=" + Utils::toString(pending_processes_.size()));
}

// Get completed CGI responses
std::vector<std::pair<int, CGIResponse> > CGI::getCompletedProcesses() {
	// Logger::debug("CGI::getCompletedProcesses - Returning " + Utils::toString(completed_responses_.size()) + " responses");
	
	// Return and clear
	std::vector<std::pair<int, CGIResponse> > result = completed_responses_;
	completed_responses_.clear();
	return result;
}
