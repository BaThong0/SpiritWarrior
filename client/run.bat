cd "%~dp0"
cmake -S . -B ../build
cmake --build ../build --target run --parallel
pause