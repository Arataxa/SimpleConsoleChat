#pragma once

#include <string_view>
#include <map>
#include <stdexcept>

#include "Chat.h"
#include "User.h"

class ChatSystem {
private:
	std::map<std::string, User> users_;
	Chat public_chat_;
	std::map<std::pair<std::string_view, std::string_view>, Chat> private_chats_;

	std::pair<std::string_view, std::string_view> MakeKey(std::string_view a, std::string_view b) const {
		return a < b ? std::make_pair(a, b) : std::make_pair(b, a);
	}
public:
	User& RegisterUser(const std::string& username, const std::string& password, const std::string& name);

	User& LoginUser(const std::string& username, const std::string& password);

	void SendPrivateMessage(const std::string& from, const std::string& to, std::string& message_content);

	void SendPublicMessage(const std::string& from, const std::string& data);

	void DisplayPublicChat() const;

	template<typename T>
	bool DisplayPrivateChat(const T& fst_username, const T& snd_username) const {
		auto it = private_chats_.find(MakeKey(fst_username, snd_username));

		if (it == private_chats_.end()) {
			return false;
		}

		it->second.DisplayMessage();

		return true;
	}

	template<typename T>
	bool IsUserExists(const T& user_name) const {
		return users_.count(user_name);
	}
};