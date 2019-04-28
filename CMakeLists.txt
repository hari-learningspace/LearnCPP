cmake_minimum_required(VERSION 3.13)

set(This GoogleDemo)
project(${This})

set(C_STANDARD 99)
set(CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

enable_testing()

include_directories(inc)

add_subdirectory(../lib/googletest build)
add_subdirectory(src)
add_subdirectory(test)