#include "AutoIndexHandler.hpp"
#include "ErrorHandler.hpp"
#include <dirent.h>
#include <sys/stat.h>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <algorithm>
#include <iomanip>

AutoIndexHandler::AutoIndexHandler() {}

AutoIndexHandler::~AutoIndexHandler() {}

Response AutoIndexHandler::handle(HandlerContext& ctx) {
	Response res;
	
	if (!ctx.req.hasResolvedPath()) {
		Logger::error("AutoIndexHandler - No resolved path available");
		return ErrorHandler(500).handle(ctx);
	}

	std::string dirPath = ctx.req.getResolvedPath();
	Logger::debug("AutoIndexHandler - Generating directory listing for: " + dirPath);

	struct stat st;
	
	// Single pre-check: Verify path exists and is a directory
	if (stat(dirPath.c_str(), &st) != 0 || !S_ISDIR(st.st_mode)) {
		Logger::debug("AutoIndexHandler - Path not accessible or not a directory: " + dirPath);
		return ErrorHandler(404).handle(ctx);
	}

	std::string requestPath = ctx.req.getPath();
	if (!requestPath.empty() && requestPath[requestPath.size() - 1] != '/') {
		requestPath += "/";
	}

	if (!dirPath.empty() && dirPath[dirPath.size() - 1] != '/') {
		dirPath += "/";
	}

	// Generate listing and check status
	std::pair<int, std::string> result = generateDirectoryListing(dirPath, requestPath);
	if (result.first != 200) {
		return ErrorHandler(result.first).handle(ctx);
	}

	res.setStatus(200);
	setCommonHeaders(res);
	res.setBody(result.second);
	res.setHeader("Content-Type", "text/html");
	res.setHeader("Content-Length", Utils::toString(result.second.size()));
	
	Logger::debug("AutoIndexHandler - Successfully generated directory listing");
	return res;
}

std::pair<int, std::string> AutoIndexHandler::generateDirectoryListing(const std::string& dirPath, const std::string& requestPath) {
	// No need to re-stat here—the caller already verified the directory
	
	DIR* dir = opendir(dirPath.c_str());
	if (!dir) {
		Logger::error("AutoIndexHandler - Permission denied opening directory: " + dirPath);
		// Since stat() succeeded, this is definitely a permission issue (EACCES)
		return std::make_pair(403, "");
	}

	std::stringstream ss;
	ss << "<!DOCTYPE html>\n";
	ss << "<html lang=\"en\">\n";
	ss << "<head>\n";
	ss << "  <meta charset=\"utf-8\" />\n";
	ss << "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />\n";
	ss << "  <title>Index of " << requestPath << "</title>\n";
	ss << "  <style>\n";
	ss << "    :root {\n";
	ss << "      --bg: #10120f;\n";
	ss << "      --card: #1c2418;\n";
	ss << "      --text: #f0fff5;\n";
	ss << "      --muted: #9bffb3;\n";
	ss << "      --accent1: #3399ff;\n";
	ss << "      --accent2: #78ffa1;\n";
	ss << "      --accent3: #5cf2b2;\n";
	ss << "      --ring: #6aff9533;\n";
	ss << "      --danger: #ff6a6a;\n";
	ss << "      --success: #78ffa1;\n";
	ss << "      --shadow: 0 20px 60px rgba(0,0,0,.4);\n";
	ss << "      --radius: 18px;\n";
	ss << "    }\n\n";
	ss << "    @media (prefers-color-scheme: light) {\n";
	ss << "      :root {\n";
	ss << "        --bg: #f6fcf6;\n";
	ss << "        --card: #ffffff;\n";
	ss << "        --text: #10120f;\n";
	ss << "        --muted: #4a6b5a;\n";
	ss << "        --ring: #6aff9520;\n";
	ss << "        --shadow: 0 20px 40px rgba(2,7,27,.12);\n";
	ss << "      }\n";
	ss << "    }\n\n";
	ss << "    * { box-sizing: border-box; }\n";
	ss << "    html, body { height: 100%; margin: 0; }\n";
	ss << "    body {\n";
	ss << "      background:\n";
	ss << "        radial-gradient(1200px 700px at 10% 0%, #102010 0%, var(--bg) 60%),\n";
	ss << "        radial-gradient(1200px 700px at 90% 100%, #182410 0%, var(--bg) 60%);\n";
	ss << "      color: var(--text);\n";
	ss << "      font: 500 16px/1.6 system-ui, \"Segoe UI\", Roboto, Inter, Arial, sans-serif;\n";
	ss << "      display: grid;\n";
	ss << "      place-items: center;\n";
	ss << "      padding: 20px;\n";
	ss << "    }\n\n";
	ss << "    .wrap {\n";
	ss << "      width: min(900px, 92%);\n";
	ss << "      position: relative;\n";
	ss << "    }\n\n";
	ss << "    .card {\n";
	ss << "      background: linear-gradient(180deg, rgba(255,255,255,.03), rgba(255,255,255,.02));\n";
	ss << "      border-radius: var(--radius);\n";
	ss << "      padding: 32px 28px;\n";
	ss << "      box-shadow: var(--shadow);\n";
	ss << "      border: 1px solid var(--ring);\n";
	ss << "      backdrop-filter: blur(8px);\n";
	ss << "    }\n\n";
	ss << "    .header {\n";
	ss << "      text-align: center;\n";
	ss << "      margin-bottom: 30px;\n";
	ss << "    }\n\n";
	ss << "    .code {\n";
	ss << "      display: inline-flex;\n";
	ss << "      gap: 10px;\n";
	ss << "      align-items: center;\n";
	ss << "      padding: 8px 14px;\n";
	ss << "      border-radius: 999px;\n";
	ss << "      background: linear-gradient(90deg, #142a1a, #1b2418);\n";
	ss << "      border: 1px solid var(--ring);\n";
	ss << "      color: var(--muted);\n";
	ss << "      font-weight: 600;\n";
	ss << "      margin-bottom: 20px;\n";
	ss << "    }\n\n";
	ss << "    .badge {\n";
	ss << "      width: 10px;\n";
	ss << "      height: 10px;\n";
	ss << "      border-radius: 50%;\n";
	ss << "      background: var(--success);\n";
	ss << "      box-shadow: 0 0 0 6px #78ffa120;\n";
	ss << "    }\n\n";
	ss << "    h1 { \n";
	ss << "      margin: 0 0 10px; \n";
	ss << "      font-size: 42px; \n";
	ss << "      letter-spacing: 1px; \n";
	ss << "      background: linear-gradient(135deg, var(--accent1), var(--accent3));\n";
	ss << "      -webkit-background-clip: text;\n";
	ss << "      -webkit-text-fill-color: transparent;\n";
	ss << "      background-clip: text;\n";
	ss << "    }\n\n";
	ss << "    .path {\n";
	ss << "      color: var(--muted);\n";
	ss << "      margin-bottom: 30px;\n";
	ss << "      font-size: 14px;\n";
	ss << "      word-break: break-all;\n";
	ss << "    }\n\n";
	ss << "    .listing {\n";
	ss << "      background: rgba(255,255,255,.02);\n";
	ss << "      border-radius: 12px;\n";
	ss << "      border: 1px solid var(--ring);\n";
	ss << "      padding: 20px;\n";
	ss << "      margin: 20px 0;\n";
	ss << "    }\n\n";
	ss << "    .entry {\n";
	ss << "      display: flex;\n";
	ss << "      align-items: center;\n";
	ss << "      padding: 4px 8px;\n";
	ss << "      margin: 4px 0;\n";
	ss << "      border-radius: 8px;\n";
	ss << "      transition: all 0.2s ease;\n";
	ss << "      border: 1px solid transparent;\n";
	ss << "    }\n\n";
	ss << "    .entry:hover {\n";
	ss << "      background: rgba(255,255,255,.05);\n";
	ss << "      border-color: var(--ring);\n";
	ss << "      transform: translateX(4px);\n";
	ss << "    }\n\n";
	ss << "    .entry a {\n";
	ss << "      text-decoration: none;\n";
	ss << "      color: inherit;\n";
	ss << "      display: flex;\n";
	ss << "      align-items: center;\n";
	ss << "      gap: 12px;\n";
	ss << "      flex: 1;\n";
	ss << "    }\n\n";
	ss << "    .icon {\n";
	ss << "      width: 20px;\n";
	ss << "      text-align: center;\n";
	ss << "      font-weight: bold;\n";
	ss << "    }\n\n";
	ss << "    .dir .icon { color: var(--accent1); }\n";
	ss << "    .file .icon { color: var(--accent3); }\n";
	ss << "    .parent .icon { color: var(--muted); }\n\n";
	ss << "    .dir .name { color: var(--accent1); font-weight: 600; }\n";
	ss << "    .file .name { color: var(--text); }\n";
	ss << "    .parent .name { color: var(--muted); }\n\n";
	ss << "    .size {\n";
	ss << "      color: var(--muted);\n";
	ss << "      font-size: 14px;\n";
	ss << "      margin-left: auto;\n";
	ss << "    }\n\n";
	ss << "    .btns {\n";
	ss << "      display: flex;\n";
	ss << "      gap: 12px;\n";
	ss << "      justify-content: center;\n";
	ss << "      margin-top: 30px;\n";
	ss << "    }\n\n";
	ss << "    a.button {\n";
	ss << "      display: inline-block;\n";
	ss << "      padding: 12px 18px;\n";
	ss << "      border-radius: 12px;\n";
	ss << "      border: 1px solid var(--ring);\n";
	ss << "      text-decoration: none;\n";
	ss << "      color: var(--text);\n";
	ss << "      font-weight: 700;\n";
	ss << "      letter-spacing: .2px;\n";
	ss << "      background: linear-gradient(135deg, #142418, #181824);\n";
	ss << "      box-shadow: 0 6px 20px rgba(0,0,0,.25);\n";
	ss << "    }\n\n";
	ss << "    a.button:hover { transform: translateY(-1px); }\n";
	ss << "    a.primary { background: linear-gradient(135deg, var(--accent1), var(--accent3)); color: #10120f; }\n";
	ss << "    a.ghost { background: transparent; }\n\n";
	ss << "    .art { position: relative; height: 120px; margin: 10px auto 20px; }\n";
	ss << "    svg { position: absolute; inset: 0; width: 100%; height: 100%; }\n";
	ss << "    .glow { filter: blur(24px); opacity: .35; }\n";
	ss << "    footer { margin-top: 30px; color: var(--muted); font-size: 14px; text-align: center; }\n";
	ss << "  </style>\n";
	ss << "</head>\n";
	ss << "<body>\n";
	ss << "  <div class=\"wrap\">\n";
	ss << "    <div class=\"card\">\n";
	ss << "      <div class=\"header\">\n";
	ss << "        <div class=\"code\">\n";
	ss << "          <span class=\"badge\"></span>\n";
	ss << "          <span>Directory Listing</span>\n";
	ss << "        </div>\n";
	ss << "        <h1>Folder Contents</h1>\n";
	ss << "        <div class=\"path\">" << requestPath << "</div>\n";
	ss << "      </div>\n";
	ss << "      \n";
	ss << "      <div class=\"listing\">\n";

	struct dirent* entry;
	std::vector<std::string> entries;
	
	// Collect all entries
	while ((entry = readdir(dir)) != NULL) {
		std::string name(entry->d_name);
		if (name[0] == '.' && name != "." && name != "..") {
			continue;
		}
		entries.push_back(name);
	}
	
	closedir(dir);
	std::sort(entries.begin(), entries.end());
	
	// Parent directory link
	if (requestPath != "/") {
		ss << "        <div class=\"entry parent\">\n";
		ss << "          <a href=\"../\">\n";
		ss << "            <span class=\"icon\">↩</span>\n";
		ss << "            <span class=\"name\">Parent Directory</span>\n";
		ss << "            <span class=\"size\">-</span>\n";
		ss << "          </a>\n";
		ss << "        </div>\n";
	}
	
	// Generate entries
	for (std::vector<std::string>::iterator it = entries.begin(); it != entries.end(); ++it) {
		std::string name = *it;
		std::string fullPath = dirPath + name;
		
		struct stat st;
		bool isDir = false;
		std::string sizeStr = "-";
		
		// Per-entry stat() failure is non-fatal—just show as plain file
		if (stat(fullPath.c_str(), &st) == 0) {
			isDir = S_ISDIR(st.st_mode);
			if (!isDir) {
				double size = st.st_size;
				const char* units[] = {"B", "KB", "MB", "GB"};
				int unitIndex = 0;
				while (size >= 1024 && unitIndex < 3) {
					size /= 1024;
					unitIndex++;
				}
				
				std::stringstream sizeStream;
				sizeStream << std::fixed << std::setprecision(unitIndex > 0 ? 1 : 0) << size << " " << units[unitIndex];
				sizeStr = sizeStream.str();
			}
		}
		
		std::string entryClass = isDir ? "dir" : "file";
		std::string icon = isDir ? "📁" : "📄";
		std::string displayName = name;
		
		if (isDir && name != "." && name != "..") {
			displayName += "/";
		}

		ss << "        <div class=\"entry " << entryClass << "\">\n";
		ss << "          <a href=\"" << requestPath << name;
		if (isDir && name != "." && name != "..") {
			ss << "/";
		}
		ss << "\">\n";
		ss << "            <span class=\"icon\">" << icon << "</span>\n";
		ss << "            <span class=\"name\">" << displayName << "</span>\n";
		ss << "            <span class=\"size\">" << sizeStr << "</span>\n";
		ss << "          </a>\n";
		ss << "        </div>\n";
	}

	ss << "      </div>\n";
	ss << "      <div class=\"btns\">\n";
	ss << "        <a class=\"button ghost\" href=\"#\" onclick=\"history.back();return false;\">Go Back</a>\n";
	ss << "      </div>\n";
	ss << "      <footer>\n";
	ss << "        " << entries.size() << " items\n";
	ss << "      </footer>\n";
	ss << "    </div>\n";
	ss << "  </div>\n";
	ss << "</body>\n";
	ss << "</html>\n";
	
	return std::make_pair(200, ss.str());
}
