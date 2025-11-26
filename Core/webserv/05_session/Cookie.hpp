#ifndef WEBSERV_05_SESSION_Cookie_HPP
#define WEBSERV_05_SESSION_Cookie_HPP

#include <string>
#include <map>

class Cookie {
public:
	Cookie();
	Cookie(const std::string& name, const std::string& value);
	
	void setName(const std::string& name);
	void setValue(const std::string& value);
	void setPath(const std::string& path);
	void setDomain(const std::string& domain);
	void setMaxAge(int maxAge);
	void setHttpOnly(bool httpOnly);
	void setSecure(bool secure);
	
	const std::string& getName() const;
	const std::string& getValue() const;
	const std::string& getPath() const;
	const std::string& getDomain() const;
	int getMaxAge() const;
	bool isHttpOnly() const;
	bool isSecure() const;
	
	std::string toString() const;
	static Cookie parse(const std::string& cookieStr);
	
private:
	std::string name_;
	std::string value_;
	std::string path_;
	std::string domain_;
	int maxAge_;
	bool httpOnly_;
	bool secure_;
};

#endif // WEBSERV_05_SESSION_Cookie_HPP
