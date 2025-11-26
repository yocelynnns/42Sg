#ifndef WEBSERV_05_SESSION_Session_HPP
#define WEBSERV_05_SESSION_Session_HPP

#include <string>
#include <map>
#include <ctime>

const std::time_t SESSION_TIMEOUT_1MIN = 60;
const std::time_t SESSION_TIMEOUT_10MIN = 600;
const std::time_t SESSION_TIMEOUT_30MIN = 1800;
const std::time_t SESSION_TIMEOUT_60MIN = 18000;
const std::time_t SESSION_TIMEOUT_24HOURS = 86400;

class Session {
public:
    Session();
    Session(const std::string& id);
    
    const std::string& getId() const;
    void setData(const std::string& key, const std::string& value);
    std::string getData(const std::string& key) const;
    bool hasData(const std::string& key) const;
    void removeData(const std::string& key);
    void clear();
    
    std::time_t getCreationTime() const;
    std::time_t getLastAccessTime() const;
    void updateAccessTime();
    
    bool isExpired() const;
    void setExpiration(std::time_t expiration);
    std::time_t getExpiration() const;
    
    const std::map<std::string, std::string>& getAllData() const;
    
private:
    std::string id_;
    std::map<std::string, std::string> data_;
    std::time_t creationTime_;
    std::time_t lastAccessTime_;
    std::time_t expirationTime_;
};


#endif // WEBSERV_05_SESSION_Session_HPP
