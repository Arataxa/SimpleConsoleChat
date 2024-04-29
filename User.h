#pragma once

#include <vector>
#include <string>

class User {
private:
	std::string username_;
	std::string password_;
	std::string name_;
public:
	User() = default;

	User(const std::string& username, const std::string& password, const std::string& name);
	
	const std::string& GetUsername() const;

	std::string GetName() const;

	bool IsPasswordCorrect(const std::string& password) const;
};