#pragma once
#include <string>
#include "Models/Common.h"

class UserManager
{
private:
    UserInfo userInfo;
    UserManager() = default;

public:
    static UserManager &Instance()
    {
        static UserManager instance;
        return instance;
    }

    void SetUserID(int id)
    {
        userInfo.id = id;
    }

    int GetUserID() const
    {
        return userInfo.id;
    }

    void SetUsername(const std::string &name)
    {
        userInfo.username = name;
    }

    std::string GetUsername() const
    {
        return userInfo.username;
    }

    UserManager(const UserManager &) = delete;
    void operator=(const UserManager &) = delete;
};