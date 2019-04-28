cmake_minimum_required(VERSION 3.13)

set(This GoogleDemo)
project(${This})

set(C_STANDARD 99)
set(CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

enable_testing()

include_directories("${CMAKE_SOURCE_DIR}/inc"
    "${CMAKE_SOURCE_DIR}/../lib/googletest/googletest/include/"
    "${CMAKE_SOURCE_DIR}/../lib/googletestgooglemock/include/")

add_subdirectory(../lib/googletest build)
add_subdirectory(src)
add_subdirectory(test)