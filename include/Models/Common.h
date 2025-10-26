#pragma once
#include <string>
#include <nlohmann/json.hpp>

enum class RequestType
{
    CREATE_ROOM,
    JOIN_ROOM,
    PLAYER_MOVE,
    START_GAME,
    UNKNOWN
};

struct UserInfo
{
    int id = 0;
    unsigned int roomId = 0;
    std::string username;
};

struct MapInfo {
    //image
    //sound
    int height;
    int width;
};

struct PlayerInfo
{
    std::string name;
    int X;
    int Y;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(UserInfo, id, username)