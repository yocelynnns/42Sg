	#include "Cookie.hpp"
	#include "06_utils/Utils.hpp"
	#include <sstream>

	Cookie::Cookie() 
		: maxAge_(-1), httpOnly_(false), secure_(false) {}

	Cookie::Cookie(const std::string& name, const std::string& value)
		: name_(name), value_(value), maxAge_(-1), httpOnly_(false), secure_(false) {}

	void Cookie::setName(const std::string& name) { name_ = name; }
	void Cookie::setValue(const std::string& value) { value_ = value; }
	void Cookie::setPath(const std::string& path) { path_ = path; }
	void Cookie::setDomain(const std::string& domain) { domain_ = domain; }
	void Cookie::setMaxAge(int maxAge) { maxAge_ = maxAge; }
	void Cookie::setHttpOnly(bool httpOnly) { httpOnly_ = httpOnly; }
	void Cookie::setSecure(bool secure) { secure_ = secure; }

	const std::string& Cookie::getName() const { return name_; }
	const std::string& Cookie::getValue() const { return value_; }
	const std::string& Cookie::getPath() const { return path_; }
	const std::string& Cookie::getDomain() const { return domain_; }
	int Cookie::getMaxAge() const { return maxAge_; }
	bool Cookie::isHttpOnly() const { return httpOnly_; }
	bool Cookie::isSecure() const { return secure_; }

	std::string Cookie::toString() const {
		std::string result = name_ + "=" + value_;
		
		if (!path_.empty()) {
			result += "; Path=" + path_;
		}
		if (!domain_.empty()) {
			result += "; Domain=" + domain_;
		}
		if (maxAge_ > 0) {
			result += "; Max-Age=" + Utils::toString(maxAge_);
		}
		if (httpOnly_) {
			result += "; HttpOnly";
		}
		if (secure_) {
			result += "; Secure";
		}
		
		return result;
	}

	Cookie Cookie::parse(const std::string& cookieStr) {
		Cookie cookie;
		std::string::size_type pos = cookieStr.find('=');
		if (pos == std::string::npos) return cookie;
		
		cookie.setName(cookieStr.substr(0, pos));
		
		std::string::size_type end = cookieStr.find(';', pos);
		if (end == std::string::npos) {
			cookie.setValue(cookieStr.substr(pos + 1));
		} else {
			cookie.setValue(cookieStr.substr(pos + 1, end - pos - 1));
		}
		return cookie;
	}
