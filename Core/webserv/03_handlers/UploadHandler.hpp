#ifndef WEBSERV_03_HANDLERS_UPLOADHANDLER_HPP
#define WEBSERV_03_HANDLERS_UPLOADHANDLER_HPP

#include "Handler.hpp"
#include <string>
#include <vector>

struct HttpRequest;

struct UploadedFile {
		std::string fileName;
		std::string contentType;
		std::vector<char> data;
};

class UploadHandler : public Handler {
public:
	UploadHandler();
	UploadHandler(const std::string& uploadDir);
	~UploadHandler();
	Response handle(HandlerContext& ctx);

private:
	std::string _uploadDirectory;

	std::vector<UploadedFile> parseMultipart(const Request& request);
	bool saveFile(const UploadedFile& file, std::string& savedPath);
	bool validateFile(const UploadedFile& file, const Location loc);
	std::string generateUniqueFilename(const std::string& original);
};

#endif
