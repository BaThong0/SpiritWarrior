cmake_minimum_required (VERSION 3.16)

project("Spirit_Warrior_Client")

file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

add_subdirectory(
    "../raylib" #source
    "${CMAKE_BINARY_DIR}/raylib"
)

add_subdirectory(
    "../enet" #source
    "${CMAKE_BINARY_DIR}/enet"
)

add_subdirectory(
    "../external/json"
    "${CMAKE_BINARY_DIR}/json"
)

# Link thư viện OS-specific
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE Ws2_32 Winmm raylib)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE enet raylib nlohmann_json::nlohmann_json pthread)
endif()

add_custom_target(run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CONFIGURE_DEPENDS ON)