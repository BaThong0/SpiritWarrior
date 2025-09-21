#pragma once
#include <string>
#include <nlohmann/json.hpp>

enum class RequestType
{
    CREATE_ROOM,
    JOIN_ROOM,
    PLAYER_MOVE,
    UNKNOWN
};

struct UserInfo
{
    int id = 0;
    std::string username;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(UserInfo, id, usernam)