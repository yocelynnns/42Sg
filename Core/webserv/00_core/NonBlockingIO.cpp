#include "NonBlockingIO.hpp"
#include "06_utils/Logger.hpp"
#include "06_utils/Utils.hpp"
#include <unistd.h>

// -----------------------------------------------------------------------------
// readOnce - POLL COMPLIANT
// Subject requires: never read without poll() first
// Reads at most once into provided string buffer.
// -----------------------------------------------------------------------------
ssize_t NonBlockingIO::readOnce(int fd, std::string& out) {
	char buffer[4096];
	ssize_t n = ::read(fd, buffer, sizeof(buffer));
	if (n > 0) {
		out.append(buffer, n);
		Logger::debug("NonBlockingIO::readOnce fd=" + Utils::toString(fd) +
					" read " + Utils::toString(n) + " bytes");
	} else if (n == 0) {
		// EOF
		Logger::debug("NonBlockingIO::readOnce fd=" + Utils::toString(fd) + " EOF");
	} else {
		// n < 0: error or would-block
		Logger::debug("NonBlockingIO::readOnce fd=" + Utils::toString(fd) +
					" returned " + Utils::toString(n));
	}
	return n;
}

// -----------------------------------------------------------------------------
// writeOnce - POLL COMPLIANT
// Subject requires: never write without poll() first
// Writes at most once from provided string buffer.
// -----------------------------------------------------------------------------
ssize_t NonBlockingIO::writeOnce(int fd, const std::string& in) {
	if (in.empty()) return 0;
	
	ssize_t n = ::write(fd, in.c_str(), in.size());
	
	if (n > 0) {
		Logger::debug("NonBlockingIO::writeOnce fd=" + Utils::toString(fd) +
			" wrote " + Utils::toString(n) + " bytes");
		return n;
	} else {
		// n == 0 or n < 0 both mean "not ready, try again"
		Logger::debug("NonBlockingIO::writeOnce fd=" + Utils::toString(fd) + 
			" would block");
		return 0;
	}
}
