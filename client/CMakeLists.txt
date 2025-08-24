# Collect sources
file(GLOB CLIENT_SRC src/*.cpp)

add_executable(Client ${CLIENT_SRC})

# === Find Raylib ===
find_path(RAYLIB_INCLUDE_DIR raylib.h)
find_library(RAYLIB_LIBRARY NAMES raylib)

if(NOT RAYLIB_INCLUDE_DIR OR NOT RAYLIB_LIBRARY)
    message(FATAL_ERROR "Raylib not found! Please install Raylib or specify paths.")
endif()

# === Find ENet ===
find_path(ENET_INCLUDE_DIR enet/enet.h)
find_library(ENET_LIBRARY NAMES enet)

if(NOT ENET_INCLUDE_DIR OR NOT ENET_LIBRARY)
    message(FATAL_ERROR "ENet not found! Please install ENet or specify paths.")
endif()

# Includes
target_include_directories(Client PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${RAYLIB_INCLUDE_DIR}
    ${ENET_INCLUDE_DIR}
)

# Link libraries
target_link_libraries(Client PRIVATE
    GameCore
    ${RAYLIB_LIBRARY}
    ${ENET_LIBRARY}
)