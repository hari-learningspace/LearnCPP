cmake_minimum_required(VERSION 3.13)

set(This MathTest)
set(SOURCES MathTest.cpp)

include_directories(${CMAKE_SOURCE_DIR}/inc)
add_executable(${This} ${SOURCES})

target_link_libraries(${This}
                     gtest_main
                     MathApp
)       

add_test(
    NAME ${This}
    COMMAND ${This}
)