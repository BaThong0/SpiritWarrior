@echo off
set BUILD_DIR=build
cmake -S . -B %BUILD_DIR%

cmake --build %BUILD_DIR% --config Debug --parallel
echo ===== START CLIENT =====
%BUILD_DIR%\Debug\Spirit_Warrior_Client.exe
pause