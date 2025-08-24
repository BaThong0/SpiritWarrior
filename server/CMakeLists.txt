# Collect sources
file(GLOB SERVER_SRC src/*.cpp)

add_executable(Server ${SERVER_SRC})

# === Find ENet ===
find_path(ENET_INCLUDE_DIR enet/enet.h)
find_library(ENET_LIBRARY NAMES enet)

if(NOT ENET_INCLUDE_DIR OR NOT ENET_LIBRARY)
    message(FATAL_ERROR "ENet not found! Please install ENet or specify paths.")
endif()

# Includes
target_include_directories(Server PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${ENET_INCLUDE_DIR}
)

# Link libraries
target_link_libraries(Server PRIVATE
    GameCore
    ${ENET_LIBRARY}
)