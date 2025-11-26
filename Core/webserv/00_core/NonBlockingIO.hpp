#ifndef WEBSERV_00_NONBLOCKINGIO_HPP
#define WEBSERV_00_NONBLOCKINGIO_HPP

#include <string>
#include <sys/types.h>
#include <unistd.h>

class NonBlockingIO {
public:
	// Perform a single non-blocking read and append to string buffer
	static ssize_t readOnce(int fd, std::string& out);

	// Perform a single non-blocking write from string buffer
	static ssize_t writeOnce(int fd, const std::string& in);
};

#endif // WEBSERV_00_NONBLOCKINGIO_HPP
