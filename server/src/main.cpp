#include <iostream>
#include <enet/enet.h>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <thread>
#include <nlohmann/json.hpp>
#include "Models/Common.h"
#include "Network/Server.h"
#include "../../include/Models/logger.h"

int main(int argc, char **argv)
{
    LOG_INFO("Server started");
    Server server;
    server.Run();
}