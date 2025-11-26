#include "UploadHandler.hpp"
#include "ErrorHandler.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

UploadHandler::UploadHandler() 
	: _uploadDirectory("./assets/upload") {}

UploadHandler::UploadHandler(const std::string& uploadDir)
	: _uploadDirectory(uploadDir) {}

UploadHandler::~UploadHandler() {
	// Destructor implementation
}

Response UploadHandler::handle(HandlerContext& ctx) {
	int status = 200;

	if (!ctx.req.hasHeader("Content-Type"))
		status = 400;

	std::vector<UploadedFile> files = parseMultipart(ctx.req);
	if (files.empty())
		status = 400;
	
	std::stringstream ss;
	ss << "<html><head><title>Upload Successful</title></head><body>";
	ss << "<h1>Upload successful</h1><ul>";

	bool saved = false;
	std::vector<UploadedFile>::iterator it;
	for (it = files.begin(); it != files.end(); ++it) {
		if (!validateFile(*it, *ctx.loc))
			continue;

		if (it->contentType.empty()) {
			std::string::size_type pos = it->fileName.find_last_of('.');
			std::string ext = (pos != std::string::npos) ? it->fileName.substr(pos + 1) : "";
			it->contentType = HttpUtils::getMimeType(ext);
		}

		std::string savedPath;
		if (!saveFile(*it, savedPath))
			continue;

		ss << "<li><a href=\"" << savedPath << "\">" << it->fileName << "</a></li>";
		saved = true;
	}

	if (!saved)
		ss << "<li>No valid files were uploaded.</li>";

	ss << "</ul><a href=\"/\">Back to Home</a>";
	ss << "</body></html>";

	Response res;
	if (status != 200) {
		Handler* tmp = new ErrorHandler(status);
		res = tmp->handle(ctx);
		delete tmp;
	} else {
		res.setStatus(200);
		setCommonHeaders(res);
		res.setHeader("Content-Type", "text/html");
		std::stringstream len;
		len << ss.str().size();
		res.setHeader("Content-Length", len.str());
		res.setBody(ss.str());

		// -- FIX: force close after upload to avoid leftover multipart noise --
		res.setHeader("Connection", "close");
		// ---------------------------------------------------------------------

	}

	return (res);
}

std::vector<UploadedFile> UploadHandler::parseMultipart(const Request& req) {
	std::vector<UploadedFile> uploaded;

	std::string contentType = req.getHeader("Content-Type");
	if (contentType.empty())
		return (uploaded);
	
	Logger::debug("parseMultipart - Content-Type: [" + contentType + "]");

	std::string key = "boundary=";
	std::string::size_type pos = contentType.find(key);
	if (pos == std::string::npos) {
		Logger::debug("parseMultipart - No boundary found in Content-Type");
		return (uploaded);
	}

	std::string boundary = contentType.substr(pos + key.size());
	if (boundary.size() > 2 && boundary[0] == '"' && boundary[boundary.size() - 1] == '"')
		boundary = boundary.substr(1, boundary.size() - 2);
	
	Logger::debug("parseMultipart - Raw boundary: [" + boundary + "]");
	boundary = "--" + boundary;
	Logger::debug("parseMultipart - Full boundary: [" + boundary + "]");

	const std::string& body = req.getBody();
	Logger::debug("parseMultipart - Body size: " + Utils::toString(body.size()));
	Logger::debug("parseMultipart - Body first 300 chars: [" + 
				body.substr(0, std::min((size_t)300, body.size())) + "]");


	std::string::size_type start = 0;

	while (true) {
		std::string::size_type partStart = body.find(boundary, start);
		if (partStart == std::string::npos)
			break;
		partStart += boundary.size();

		if (body.compare(partStart, 2, "--") == 0)
			break;
		if (body.compare(partStart, 2, "\r\n") == 0)
			partStart += 2;

		std::string::size_type partEnd = body.find(boundary, partStart);
		if (partEnd == std::string::npos)
			break;

		std::string part = body.substr(partStart, partEnd - partStart);
		start = partEnd;

		std::string::size_type headerEnd = part.find("\r\n\r\n");
		if (headerEnd == std::string::npos)
			continue;

		std::string headerBlock = part.substr(0, headerEnd);
		std::string dataBlock = part.substr(headerEnd + 4);

		UploadedFile file;
		std::stringstream ss(headerBlock);
		std::string line;

		while (std::getline(ss, line)) {
			if (!line.empty() && line[line.size() - 1] == '\r')
				line.erase(line.size() - 1);

			if (line.find("Content-Disposition:") == 0) {
				std::string::size_type fnPos = line.find("filename=");
				if (fnPos != std::string::npos) {
					std::string::size_type startQuote = line.find("\"", fnPos);
					std::string::size_type endQuote = line.find("\"", startQuote + 1);
					if (startQuote != std::string::npos && endQuote != std::string::npos)
						file.fileName = line.substr(startQuote + 1, endQuote - startQuote - 1);
				}
			} else if (line.find("Content-Type:") == 0) {
				file.contentType = line.substr(std::string("Content-Type:").size());
				std::string::size_type firstNonSpace = file.contentType.find_first_not_of(" \t");
				if (firstNonSpace != std::string::npos)
					file.contentType.erase(0, firstNonSpace);
			}
		}

		if (file.contentType.empty()) {
			std::string::size_type dot = file.fileName.rfind('.');
			std::string ext = (dot != std::string::npos) ? file.fileName.substr(dot + 1) : "";
			file.contentType = HttpUtils::getMimeType(ext);
		}

		file.data.assign(dataBlock.begin(), dataBlock.end());
		uploaded.push_back(file);

	}

	return (uploaded);
}

bool UploadHandler::validateFile(const UploadedFile& file, const Location loc) {
	if (file.fileName.empty())
		return (false);

	if (file.fileName.find("..") != std::string::npos || file.fileName.find('/') != std::string::npos || file.fileName.find("\\") != std::string::npos)
		return (false);

	// const size_t MAX_SIZE = 10 * 1024 * 1024;
	// if (file.data.size() > MAX_SIZE)
	// 	return (false);

	if (file.data.size() > loc.client_max_body_size)
			return (false);

	std::string::size_type dot = file.fileName.rfind('.');
	if (dot == std::string::npos)
		return (false);

	// // Temp Optional: whitelst certain types
	// std::string ext = file.fileName.substr(dot + 1);
	// if (ext != "txt" && ext != "png" && ext != "jpg" && ext != "pdf")
	// 	return (false);
	
	// // Temp Optional: reject files without extensions
	// if (dot == std::string::npos)
	// 	return false;

	return (true);
}

bool UploadHandler::saveFile(const UploadedFile& file, std::string& savedPath) {
	std::string uniqueName = generateUniqueFilename(file.fileName);
	savedPath = _uploadDirectory + "/" + uniqueName;

	// ---- FIX: Skip duplicate saves if identical file already exists ----
	std::ifstream existing(savedPath.c_str(), std::ios::binary);
	if (existing.is_open()) {
		existing.seekg(0, std::ios::end);
		std::streamsize existingSize = existing.tellg();
		existing.close();

		if (existingSize == static_cast<std::streamsize>(file.data.size())) {
			Logger::debug("Skipping duplicate save for " + savedPath);
			return true; // treat as success
		}
	}
	// --------------------------------------------------------------------

	std::ofstream out(savedPath.c_str(), std::ios::binary);
	if (!out.is_open()) {
		Logger::error("Failed to open file for writing: " + savedPath);
		return false;
	}

	out.write(&file.data[0], file.data.size());
	out.close();

	Logger::info("File saved to " + savedPath + " (" +
	             Utils::toString(file.data.size()) + " bytes)");
	return true;
}

std::string UploadHandler::generateUniqueFilename(const std::string& original) {
	static int counter = 0;

	std::string::size_type dot = original.find('.');
	std::string name = (dot != std::string::npos) ? original.substr(0, dot) : original;
	std::string ext = (dot != std::string::npos) ? original.substr(dot) : "";

	std::string unique = name;
	std::string candidate = unique + ext;
	while (true) {
		std::string path = _uploadDirectory + "/" + candidate;
		std::ifstream test(path.c_str());
		if (!test.is_open())
			break;
		std::stringstream ss;
		ss << counter++;
		candidate = unique + "_" + ss.str() + ext; //Need to implement stringstream
	}
	return (candidate);
}
