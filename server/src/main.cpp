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

int main(int argc, char **argv)
{
    Server server;
    server.Run();
}