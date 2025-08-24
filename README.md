# SpiritWarrior Game Project

* This project is a **C++ multiplayer game** using **Raylib** (graphics) and **ENet** (networking).  
* The project is structured into **client**, **server**, and **game core logic** to keep everything modular.  

---

## 📂 Project Structure
```text
MultiplayerGame/
│── CMakeLists.txt        # Root build configuration
│── assets/               # Images, Music, Sounds, etc. 
│── build/                # CMake build output (generated, not in git)
│── cmake/                # Custom CMake modules (e.g., FindRaylib.cmake, FindENet.cmake)
│── docs/                 # Documentation (design docs, UML, etc.)
│── external/             # (Optional) Vendor libraries if needed
│── include/              # Public headers for GameCore
│── src/                  # GameCore source files (shared by client & server)
│   │── CMakeLists.txt
│── client/               # Client application
│   │── CMakeLists.txt
│   │── include/          # Client-only headers
│   │── src/              # Client-only sources
│   └── main.cpp          # Entry point for client
│
│── server/               # Server application
│   │── CMakeLists.txt
│   │── include/          # Server-only headers
│   │── src/              # Server-only sources
│   └── main.cpp          # Entry point for server
│── test/                 # UnitTesting and IntegrationTesting
```
## ⚙️ Dependencies
This project requires:  
- **CMake** ≥ 3.15  
- **C++17**  
- **Raylib** (for graphics in the client)  
- **ENet** (for networking in both client and server)  

### Install on Linux (Ubuntu/Debian)
```bash
sudo apt-get install libraylib-dev libenet-dev
```

### Install on Windows (vcpkg)
```bash
vcpkg install raylib enet
```
## 🔍 How Libraries Are Found (Macros)
We use find_path and find_library in CMake to auto-detect external libraries:
### Raylib 
```cmake 
find_path(RAYLIB_INCLUDE_DIR raylib.h)
find_library(RAYLIB_LIBRARY NAMES raylib)
```
### ENet 
```cmake 
find_path(ENET_INCLUDE_DIR enet/enet.h)
find_library(ENET_LIBRARY NAMES enet)
```
If CMake cannot find them, you can set paths manually when running cmake:
```bash
cmake .. -DRAYLIB_INCLUDE_DIR=/path/to/raylib/include -DRAYLIB_LIBRARY=/path/to/libraylib.so \
         -DENET_INCLUDE_DIR=/path/to/enet/include -DENET_LIBRARY=/path/to/libenet.so
```
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
# 1. Create and enter the build folder
mkdir build
cd build

# 2. Generate Visual Studio solution files
cmake .. -G "Visual Studio 17 2022"

# 3. Build with Visual Studio or from command line
cmake --build . --config Release
```
## 🚀 Running the Project
### Server
```bash
./bin/Server       # Linux/macOS
bin\Server.exe     # Windows
```
### Client
```bash
./bin/Client       # Linux/macOS
bin\Client.exe     # Windows
```
## 🧩 Future Improvements
* Add a test/ directory for unit tests (GTest / GMock).
* Add CI/CD pipelines for cross-platform builds.
