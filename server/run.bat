@echo off
set BUILD_DIR=build
cmake -S . -B %BUILD_DIR% -G "Visual Studio 17 2022"
cmake --build %BUILD_DIR% --config Debug --parallel
echo ===== START SERVER =====
%BUILD_DIR%\Debug\Spirit_Warrior_Server.exe
pause