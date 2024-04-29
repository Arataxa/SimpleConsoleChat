#include "ChatSystem.h"

User& ChatSystem::RegisterUser(const std::string& username, const std::string& password, const std::string& name) {
	if (users_.count(username)) {
		throw std::runtime_error("Пользователь с таким логином уже существует");
	}

	User new_user(username, password, name);
	auto [it, inserted] = users_.emplace(new_user.GetName(), new_user);

	return it->second;
}

User& ChatSystem::LoginUser(const std::string& username, const std::string& password) {
	auto it = users_.find(username);

	if (it == users_.end()) {
		throw std::runtime_error("Неверный логин");
	}

	if (!it->second.IsPasswordCorrect(password)) {
		throw std::runtime_error("Неверный пароль");
	}

	return it->second;
}

void ChatSystem::SendPrivateMessage(const std::string& from, const std::string& to, std::string& message_content) {
	auto user_it = users_.find(to);

	if (user_it == users_.end()) {
		throw std::runtime_error("Пользователь не найден");
	}

	auto [it, inserted] = private_chats_.emplace(MakeKey(from, user_it->second.GetUsername()), Chat{});

	Message new_message(from, message_content);

	it->second.SendMessage(new_message);
}

void ChatSystem::SendPublicMessage(const std::string& from, const std::string& data) {
	Message new_message(from, data);
	public_chat_.SendMessage(new_message);
}

void ChatSystem::DisplayPublicChat() const {
	public_chat_.DisplayMessage();
}