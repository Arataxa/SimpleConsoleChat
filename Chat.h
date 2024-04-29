#pragma once

#include <vector>
#include <iostream>

#include "Message.h"

class Chat {
private:
	std::vector<Message> messages_;
public:
	void SendMessage(Message& message);

	void DisplayMessage() const;

	Chat() = default;
};


