#include "Session.hpp"
#include "06_utils/Utils.hpp"
#include <cstdlib>

Session::Session() 
    : creationTime_(std::time(NULL)), lastAccessTime_(creationTime_), 
    expirationTime_(creationTime_ + SESSION_TIMEOUT_24HOURS) {} 

Session::Session(const std::string& id)
    : id_(id), creationTime_(std::time(NULL)), lastAccessTime_(creationTime_),
    expirationTime_(creationTime_ + SESSION_TIMEOUT_24HOURS) {} 

const std::string& Session::getId() const { return id_; }

void Session::setData(const std::string& key, const std::string& value) {
	data_[key] = value;
	updateAccessTime();
}

std::string Session::getData(const std::string& key) const {
	std::map<std::string, std::string>::const_iterator it = data_.find(key);
	return it != data_.end() ? it->second : "";
}

bool Session::hasData(const std::string& key) const {
	return data_.find(key) != data_.end();
}

void Session::removeData(const std::string& key) {
	data_.erase(key);
	updateAccessTime();
}

void Session::clear() {
	data_.clear();
	updateAccessTime();
}

std::time_t Session::getCreationTime() const { return creationTime_; }
std::time_t Session::getLastAccessTime() const { return lastAccessTime_; }

void Session::updateAccessTime() {
	lastAccessTime_ = std::time(NULL);
}

bool Session::isExpired() const {
	return std::time(NULL) > expirationTime_;
}

void Session::setExpiration(std::time_t expiration) {
	expirationTime_ = expiration;
}

std::time_t Session::getExpiration() const {
	return expirationTime_;
}

const std::map<std::string, std::string>& Session::getAllData() const {
	return data_;
}
