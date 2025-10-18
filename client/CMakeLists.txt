cmake_minimum_required(VERSION 3.10)
project(Spirit_Warrior_Client C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# --- Source code ---
file(GLOB_RECURSE CLIENT_SOURCES src/*.cpp src/*.h src/*.c)
add_executable(${PROJECT_NAME} ${CLIENT_SOURCES})

# --- Raylib ---
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../raylib
                 ${CMAKE_BINARY_DIR}/raylib)
target_link_libraries(${PROJECT_NAME} raylib nlohmann_json::nlohmann_json)

# --- ENet ---
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../enet
                 ${CMAKE_BINARY_DIR}/enet)

# --- JSON ---
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../external/json
                 ${CMAKE_BINARY_DIR}/json) 
# target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
# Thêm include directory cho ENet
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../enet/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)


# Link ENet (tùy target trong enet/CMakeLists.txt)
if (TARGET enet_static)
    target_link_libraries(${PROJECT_NAME} enet_static)
elseif (TARGET enet)
    target_link_libraries(${PROJECT_NAME} enet)
endif()

# --- Cross-platform settings ---
if (WIN32)
    message(STATUS "Configuring for Windows...")
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_WINDOWS)
elseif (UNIX)
    message(STATUS "Configuring for Linux...")
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_LINUX)
    target_link_libraries(${PROJECT_NAME} pthread)
endif()

# --- Run target ---
add_custom_target(run
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)