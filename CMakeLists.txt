cmake_minimum_required(VERSION 3.17)
project(test)

set(CMAKE_CXX_STANDARD 14)

add_executable(test main.cpp)

#GLFW

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(../libraries/glfw-3.3.2 glfw-3.3.2)

target_link_libraries(test glfw)

#GLEW

include_directories(../libraries/glew-2.1.0/include)

add_subdirectory(../libraries/glew-2.1.0/build/cmake glew-2.1.0/build/cmake)

target_link_libraries(test glew_s)
