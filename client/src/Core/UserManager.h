#pragma once
#include <string>

class UserManager
{
private:
    std::string username;
    UserManager() = default;

public:
    static UserManager &Instance()
    {
        static UserManager instance;
        return instance;
    }

    void SetUsername(const std::string& name) {
        username = name;
    }

    std::string GetUsername() const {
        return username;
    }

    UserManager(const UserManager&) = delete;
    void operator=(const UserManager&) = delete;
};