#include <raylib.h>
#include <iostream>
#include "Core/include/StateManager.h"
#include "States/include/LoginState.h"
#include "Core/include/EventBus.h"
#include "Network/include/NetworkManager.h"
#include "../../include/logger.h"

/*
State Pattern – Quản lý các trạng thái của menu (Login, MainMenu...).
Singleton Pattern – Quản lý thông tin người chơi (UserManager).
Command Pattern (nếu mở rộng) – Cho xử lý sự kiện nút bấm (nếu có nhiều nút phức tạp).
/Game
 ├── main.cpp
 ├── Core/
 │    ├── StateManager.h/.cpp
 │    ├── UserManager.h/.cpp
 │    ├── EventBus.h
 │    └── ICommand.h
 ├── States/
 │    ├── IState.h
 │    ├── LoginState.h/.cpp
 │    └── MainMenuState.h/.cpp
 ├── Commands/
 │    ├── CreateRoomCommand.h/.cpp
 │    └── JoinRoomCommand.h/.cpp
 └── Network/
      └── NetworkManager.h/.cpp
Core/: Thành phần lõi (quản lý state, user, command interface).
States/: Các màn hình game (Login, Menu, GamePlay...).
Commands/: Các hành động người chơi (Tạo phòng, Vào phòng...).
Network/: Xử lý network.
*/

int main()
{
    InitWindow(800, 600, "Spirit Warrior");
    SetTargetFPS(60);

    bool exit = false;

    NetworkManager *networkManager = &NetworkManager::GetInstance();
    StateManager manager;
    manager.SetState(std::make_unique<LoginState>());

    LOG_INFO("Application started");
    while (WindowShouldClose() == false && exit == false)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        manager.Update();
        manager.Draw();
        EndDrawing();
    }

    // CloseWindow();
}