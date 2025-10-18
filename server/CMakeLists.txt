cmake_minimum_required(VERSION 3.16)

project("Spirit_Warrior_Server" C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../src/*.c)


add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# ENet (build từ source)
add_subdirectory(
    "${CMAKE_SOURCE_DIR}/../enet"
    "${CMAKE_BINARY_DIR}/enet"
)
# JSON (build từ source)
add_subdirectory(
    "../external/json"
    "${CMAKE_BINARY_DIR}/json"
)
add_custom_target(run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
# Include ENet headers
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/../enet/include"
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# Link libs
target_link_libraries(${PROJECT_NAME} PRIVATE enet nlohmann_json::nlohmann_json)
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32 winmm)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()



# target "run" để chạy app sau khi build
# add_custom_target(run
#     COMMAND ${PROJECT_NAME}
#     DEPENDS ${PROJECT_NAME}
#     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
# )

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CONFIGURE_DEPENDS ON)
