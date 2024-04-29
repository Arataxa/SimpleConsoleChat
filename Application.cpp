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
        std::cout << "�������� ��������" << std::endl
            << "1. ����" << std::endl
            << "2. �����������" << std::endl
            << "3. ������� ����������." << std::endl;

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������ ������. ������� ��������������� ����� ��������." << std::endl;
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
            std::cout << "������ ������. ������� ��������������� ����� ��������." << std::endl;
            continue;
        }

        return true;
    }
}

void Application::ProcessAccountMenu() {
    while (true) {
        int choice = 0;
        std::cout << "�������� ��������" << std::endl
            << "1. ������ ���������." << std::endl
            << "2. ����� ���." << std::endl
            << "3. ����� �� ��������" << std::endl;

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������ ������. ������� ��������������� ����� ��������." << std::endl;
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
        std::cout << "�������� ��������" << std::endl
            << "1. ��������� ���������." << std::endl
            << "2. ����������� ������� ���������." << std::endl
            << "3. ���������." << std::endl;

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������ ������. ������� ��������������� ����� ��������." << std::endl;
            continue;
        }

        switch (choice) {
        case 1: {
            std::string giver_username;
            std::cout << "������� ��� ������������, �������� ������ ��������� ���������." << std::endl;
            std::cin >> giver_username;

            if (!chat_system_.IsUserExists(giver_username)) {
                std::cout << "������ ������������ �� ����������." << std::endl;
                continue;
            }

            std::string message;
            std::cout << "������� ���������." << std::endl;

            std::cin.ignore();
            std::getline(std::cin, message);

            chat_system_.SendPrivateMessage(active_user_->GetUsername(), giver_username, message);

            std::cout << "��������� ������� ����������." << std::endl;
            break;
        }
        case 2: {
            std::string username;
            std::cout << "������� ��� ������������, � ������� �� ������ ����������� ������� ���������." << std::endl;
            std::cin >> username;

            if (!chat_system_.IsUserExists(username)) {
                std::cout << "������ ������������ �� ����������." << std::endl;
                continue;
            }

            if (!chat_system_.DisplayPrivateChat(active_user_->GetUsername(), username)) {
                std::cout << "� ��� ���� ������� ��������� � ���� �������������." << std::endl;
            }

            continue;
        }
        case 3:
            return;
        default:
            std::cout << "������ ������. ������� ��������������� ����� ��������." << std::endl;
            continue;
        }
    }
}

void Application::ProcessPublicChat() {
    while (true) {
        int choice = 0;
        std::cout << "�������� ��������" << std::endl
            << "1. ��������� ���������." << std::endl
            << "2. ����������� ������� ���������." << std::endl
            << "3. ���������." << std::endl;

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������ ������. ������� ��������������� ����� ��������." << std::endl;
            continue;
        }

        switch (choice) {
        case 1: {
            std::string message;
            std::cout << "������� ���������." << std::endl;

            std::cin.ignore();
            std::getline(std::cin, message);

            chat_system_.SendPublicMessage(active_user_->GetUsername(), message);

            std::cout << "��������� ������� ����������." << std::endl;

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
            std::cout << "������ ������. ������� ��������������� ����� ��������." << std::endl;
            continue;
        }
    }
}

bool Application::Login() {
    std::string username;
    std::string password;

    while (true) {
        std::cout << "������� �����" << std::endl;
        std::cin >> username;

        std::cout << "������� ������" << std::endl;
        std::cin >> password;

        try {
            active_user_ = &chat_system_.LoginUser(username, password);

            std::cout << "���� ������ �������." << std::endl;

            return true;
        }
        catch (const std::runtime_error&) {
            std::cout << "�������� ����� ��� ������." << std::endl;
        }
        catch (...) {
            std::cout << "����������� ������." << std::endl;
        }

        while (true) {
            int choice = 0;
            std::cout << "��������� ������� �����?" << std::endl
                << "1. ��" << std::endl
                << "2. ���" << std::endl;
            std::cin >> choice;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "������ ������. ������� ��������������� ����� ��������." << std::endl;
                continue;
            }

            switch (choice) {
            case 1: break;
            case 2: return false;
            default: {
                std::cout << "������ ������. ������� ��������������� ����� ��������." << std::endl;
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
        std::cout << "������� �����" << std::endl;
        std::cin >> username;

        std::cout << "������� ������" << std::endl;
        std::cin >> password;

        std::cout << "������� ���" << std::endl;
        std::cin >> name;

        try {
            active_user_ = &chat_system_.RegisterUser(username, password, name);

            std::cout << "����������� ������ �������." << std::endl;

            return true;
        }
        catch (std::runtime_error& e) {
            std::cout << "������: " << e.what() << std::endl;
        }
        catch (...) {
            std::cout << "������ ��� �����������." << std::endl;
        }

        while (true) {
            int choice = 0;
            std::cout << "��������� �����������?" << std::endl
                << "1. ��" << std::endl
                << "2. ���" << std::endl;
            std::cin >> choice;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "������ ������. ������� ��������������� ����� ��������." << std::endl;
                continue;
            }

            switch (choice) {
            case 1: break;
            case 2: return false;
            default: {
                std::cout << "������ ������. ������� ��������������� ����� ��������." << std::endl;
                continue;
            }
            }

            break;
        }
    }
}