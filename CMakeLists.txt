cmake_minimum_required(VERSION 3.20)
project(SoulKnight LANGUAGES CXX)

#Require modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Output directories (bin for executable, lib for libraries)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#Add custom CMake scripts 
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#Add subdirectories 
add_subdirectory(src)
add_subdirectory(client)
add_subdirectory(server)
#add_subdirectory(external) 
