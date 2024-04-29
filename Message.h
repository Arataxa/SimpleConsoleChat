#pragma once

#include <string>
#include <iostream>

class Message {
private:
	std::string sender_username_;
	std::string data_;
public:
	Message(const std::string& sender_username, const std::string& data);

	std::string GetSenderUsername() const;

	std::string GetData() const;

	friend std::ostream& operator<<(std::ostream& os, const Message& message);
};

std::ostream& operator<<(std::ostream& os, const Message& message);