#pragma once

#include "User.h"
#include "ChatSystem.h"

#include <iostream>

class Application {
private:
	User* active_user_;
	ChatSystem chat_system_;
public:
    void Run();
private:
    bool ProcessMainMenu();

    void ProcessAccountMenu();

    void ProcessPrivateMessages();

    void ProcessPublicChat();

    bool Login();

    bool Register();
};