#include "Message.h"

Message::Message(const std::string& sender_username, const std::string& data)
	: sender_username_(sender_username), data_(data) {
}

std::string Message::GetSenderUsername() const {
	return sender_username_;
}

std::string Message::GetData() const {
	return data_;
}

std::ostream& operator<<(std::ostream& os, const Message& message) {
	os << message.sender_username_ << ": " << message.data_;
	return os;
}