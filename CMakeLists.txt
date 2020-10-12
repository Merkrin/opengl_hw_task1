cmake_minimum_required(VERSION 3.17)
project(test)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(../libraries libraries)

add_executable(test main.cpp)

#GLFW

target_link_libraries(test glfw)

#GLEW

include_directories(../libraries/glew-2.1.0/include)
target_link_libraries(test glew_s)
