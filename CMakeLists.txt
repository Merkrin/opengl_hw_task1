cmake_minimum_required(VERSION 3.17)
project(task1)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(../libraries libraries)

add_executable(task1 src/cpp/main.cpp src/cpp/files.h src/cpp/files.cpp src/cpp/opengl.h src/cpp/opengl.cpp src/cpp/exception.cpp src/cpp/exception.h src/cpp/utils.cpp src/cpp/utils.h src/cpp/figure.cpp src/cpp/figure.h)

#GLFW

target_link_libraries(task1 glfw)

#GLEW

include_directories(../libraries/glew-2.1.0/include)
target_link_libraries(task1 glew_s)
