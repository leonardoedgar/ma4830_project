cmake_minimum_required(VERSION 3.10)
project(ma4830_project C)

set(CMAKE_C_STANDARD 90)
include(CTest)
include_directories(src)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(lib/unity)
