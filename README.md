# SpiritWarrior Game Project

* This project is made for learning purposes. The goal is to create a 2D multiplayer client-server game.
* Using C++ and the raylib library. Applying SOLID principles and Design Patterns to make the code easy to read, maintain.

---

## 📂 Project Structure
```text
SpiritWarrior/
│── client/               # Client application
│   │── CMakeLists.txt
│   │── src/              # Client-only sources
│   └── main.cpp          # Entry point for client
│
│── server/               # Server application
│   │── CMakeLists.txt
│   │── src/              # Server-only sources
│   └── main.cpp          # Entry point for server
```
## ⚙️ Dependencies
This project requires:  
- **CMake** ≥ 3.15  
- **C++20**  
- **Raylib** (for graphics in the client)  
- **ENet** (for networking in both client and server)  

## 🛠️ Build Instructions
### Linux/macOS
```bash
# 1. Create and enter the build folder
mkdir -p build && cd build

# 2. Run CMake to generate Makefiles
cmake ..

# 3. Build the project
make
```
### Window (Visual Studio)
```bash
# 1. Clone project raylib
git clone --recurse-submodules http://github.com/raysan5/raylib
git submodule update --init --recursive

# 2. Build and run
cmake -S . -B ../build && cmake --build ../build --target run --parallel
```