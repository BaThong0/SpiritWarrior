#include <raylib.h>
#include <iostream>
#include "Core/StateManager.h"
#include "States/LoginState.h"
#include "Core/EventBus.h"

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

    StateManager manager;
    manager.SetState(new LoginState());

    while (WindowShouldClose() == false && exit == false)
    {
        EventBus::GetInstance().Dispatch();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        manager.Update();
        manager.Draw();
        EndDrawing();
    }

    CloseWindow();
}