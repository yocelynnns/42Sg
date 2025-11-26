#include "00_core/Server.hpp"
#include "01_config/Config.hpp"
#include "06_utils/Logger.hpp"
#include <iostream>
#include <cstdlib>
#include <csignal>

// Global flags for shutdown and reload
volatile sig_atomic_t g_shutdown = 0;
volatile sig_atomic_t g_reload = 0;

// -----------------------------------------------------------------------------
// Signal handler
// -----------------------------------------------------------------------------
void handle_signal(int sig) {
	if (sig == SIGINT || sig == SIGTERM) {
		Logger::info("Signal received, shutting down...");
		g_shutdown = 1;
	} else if (sig == SIGHUP) {
		Logger::info("Reload requested (SIGHUP)...");
		g_reload = 1;
	}
}

// -----------------------------------------------------------------------------
// Setup static signal handlers
// -----------------------------------------------------------------------------
void setup_signal_handlers() {
	signal(SIGPIPE, SIG_IGN);  // Ignore broken pipe
	signal(SIGINT, handle_signal);
	signal(SIGTERM, handle_signal);
	signal(SIGHUP, handle_signal);
}

// -----------------------------------------------------------------------------
// Main
// -----------------------------------------------------------------------------
int main(int argc, char** argv) {
	std::string config_file = "webserv.conf";
	if (argc > 1) config_file = argv[1];

	setup_signal_handlers();

	// Initialize logger (file optional)
	Logger::init("webserv.log");
	// Logger::setLevel(Logger::DEBUG);
	Logger::setLevel(Logger::INFO); // change to INFO for error only mode

	try {
		Server server(config_file);
		server.setShutdownFlag(&g_shutdown);
		server.setReloadFlag(&g_reload);

		Logger::info("Server starting...");
		
		if (!server.start()) {
			Logger::error("Server failed to start properly");
			Logger::shutdown();
			return 1;
		}
		
		Logger::info("Server exited gracefully");
		Logger::shutdown();
		return 0;
		
	} catch (const std::exception& e) {
		Logger::error(std::string("Fatal error: ") + e.what());
		Logger::shutdown();
		return 1;
	}
}
