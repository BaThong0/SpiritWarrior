# Collect all cpp files in src/
file(GLOB GAMECORE_SRC *.cpp)

# Create GameCore library
add_library(GameCore ${GAMECORE_SRC})

# Add include directory for GameCore
target_include_directories(GameCore PUBLIC ${CMAKE_SOURCE_DIR}/include)