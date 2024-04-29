#include "Chat.h"


void Chat::SendMessage(Message& message) {
	messages_.push_back(std::move(message));
}

void Chat::DisplayMessage() const {
	for (const auto& message : messages_) {
		std::cout << message << std::endl;
	}
}
