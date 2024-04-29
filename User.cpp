#include "User.h"

User::User(const std::string& username, const std::string& password, const std::string& name)
	: username_(username), password_(password), name_(name) {
}

const std::string& User::GetUsername() const {
	return username_;
}

std::string User::GetName() const {
	return name_;
}

bool User::IsPasswordCorrect(const std::string& password) const {
	return password_ == password;
}