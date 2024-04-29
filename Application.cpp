#include "Application.h"

void Application::Run() {
    while (true) {
        if (!ProcessMainMenu()) {
            return;
        }
        ProcessAccountMenu();
    }
}

bool Application::ProcessMainMenu() {
    int choice = 0;
    while (true) {
        std::cout << "Выберите действие" << std::endl
            << "1. Вход" << std::endl
            << "2. Регистрация" << std::endl
            << "3. Закрыть приложение." << std::endl;

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка выбора. Введите соответствующую цифру действия." << std::endl;
            continue;
        }

        switch (choice) {
        case 1: {
            if (!Login()) {
                continue;
            }

            break;
        }
        case 2: {
            if (!Register()) {
                continue;
            }

            break;
        }
        case 3: {
            return false;
        }
        default:
            std::cout << "Ошибка выбора. Введите соответствующую цифру действия." << std::endl;
            continue;
        }

        return true;
    }
}

void Application::ProcessAccountMenu() {
    while (true) {
        int choice = 0;
        std::cout << "Выберите действие" << std::endl
            << "1. Личные сообщения." << std::endl
            << "2. Общий чат." << std::endl
            << "3. Выйти из аккаунта" << std::endl;

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка выбора. Введите соответствующую цифру действия." << std::endl;
            continue;
        }

        switch (choice) {
        case 1: {
            ProcessPrivateMessages();
            continue;
        }
        case 2: {
            ProcessPublicChat();
            continue;
        }
        case 3: {
            active_user_ = nullptr;
            return;
        }
        default:
            break;
        }
    }
}

void Application::ProcessPrivateMessages() {
    while (true) {
        int choice = 0;
        std::cout << "Выберите действие" << std::endl
            << "1. Отправить сообщение." << std::endl
            << "2. Просмотреть историю переписки." << std::endl
            << "3. Вернуться." << std::endl;

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка выбора. Введите соответствующую цифру действия." << std::endl;
            continue;
        }

        switch (choice) {
        case 1: {
            std::string giver_username;
            std::cout << "Введите ник пользователя, которому хотите отправить сообщение." << std::endl;
            std::cin >> giver_username;

            if (!chat_system_.IsUserExists(giver_username)) {
                std::cout << "Такого пользователя не существует." << std::endl;
                continue;
            }

            std::string message;
            std::cout << "Введите сообщение." << std::endl;

            std::cin.ignore();
            std::getline(std::cin, message);

            chat_system_.SendPrivateMessage(active_user_->GetUsername(), giver_username, message);

            std::cout << "Сообщение успешно отправлено." << std::endl;
            break;
        }
        case 2: {
            std::string username;
            std::cout << "Введите ник пользователя, с которым вы хотите просмотреть историю переписки." << std::endl;
            std::cin >> username;

            if (!chat_system_.IsUserExists(username)) {
                std::cout << "Такого пользователя не существует." << std::endl;
                continue;
            }

            if (!chat_system_.DisplayPrivateChat(active_user_->GetUsername(), username)) {
                std::cout << "У вас нету истории переписки с этим пользователем." << std::endl;
            }

            continue;
        }
        case 3:
            return;
        default:
            std::cout << "Ошибка выбора. Введите соответствующую цифру действия." << std::endl;
            continue;
        }
    }
}

void Application::ProcessPublicChat() {
    while (true) {
        int choice = 0;
        std::cout << "Выберите действие" << std::endl
            << "1. Отправить сообщение." << std::endl
            << "2. Просмотреть историю переписки." << std::endl
            << "3. Вернуться." << std::endl;

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка выбора. Введите соответствующую цифру действия." << std::endl;
            continue;
        }

        switch (choice) {
        case 1: {
            std::string message;
            std::cout << "Введите сообщение." << std::endl;

            std::cin.ignore();
            std::getline(std::cin, message);

            chat_system_.SendPublicMessage(active_user_->GetUsername(), message);

            std::cout << "Сообщение успешно отправлено." << std::endl;

            continue;
        }
        case 2: {
            chat_system_.DisplayPublicChat();

            continue;
        }
        case 3: {
            return;
        }
        default:
            std::cout << "Ошибка выбора. Введите соответствующую цифру действия." << std::endl;
            continue;
        }
    }
}

bool Application::Login() {
    std::string username;
    std::string password;

    while (true) {
        std::cout << "Введите логин" << std::endl;
        std::cin >> username;

        std::cout << "Введите пароль" << std::endl;
        std::cin >> password;

        try {
            active_user_ = &chat_system_.LoginUser(username, password);

            std::cout << "Вход прошёл успешно." << std::endl;

            return true;
        }
        catch (const std::runtime_error&) {
            std::cout << "Неверный логин или пароль." << std::endl;
        }
        catch (...) {
            std::cout << "Неизвестная ошибка." << std::endl;
        }

        while (true) {
            int choice = 0;
            std::cout << "Повторить попытку входа?" << std::endl
                << "1. Да" << std::endl
                << "2. Нет" << std::endl;
            std::cin >> choice;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка выбора. Введите соответствующую цифру действия." << std::endl;
                continue;
            }

            switch (choice) {
            case 1: break;
            case 2: return false;
            default: {
                std::cout << "Ошибка выбора. Введите соответствующую цифру действия." << std::endl;
                continue;
            }
            }

            break;
        }
    }
}

bool Application::Register() {
    std::string username;
    std::string password;
    std::string name;

    while (true) {
        std::cout << "Введите логин" << std::endl;
        std::cin >> username;

        std::cout << "Введите пароль" << std::endl;
        std::cin >> password;

        std::cout << "Введите имя" << std::endl;
        std::cin >> name;

        try {
            active_user_ = &chat_system_.RegisterUser(username, password, name);

            std::cout << "Регистрация прошла успешно." << std::endl;

            return true;
        }
        catch (std::runtime_error& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
        catch (...) {
            std::cout << "Ошибка при регистрации." << std::endl;
        }

        while (true) {
            int choice = 0;
            std::cout << "Повторить регистрацию?" << std::endl
                << "1. Да" << std::endl
                << "2. Нет" << std::endl;
            std::cin >> choice;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка выбора. Введите соответствующую цифру действия." << std::endl;
                continue;
            }

            switch (choice) {
            case 1: break;
            case 2: return false;
            default: {
                std::cout << "Ошибка выбора. Введите соответствующую цифру действия." << std::endl;
                continue;
            }
            }

            break;
        }
    }
}