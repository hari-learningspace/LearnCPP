cmake_minimum_required(VERSION 3.13)

set(This MathTest)
set(SOURCES MathTest.cpp)

include_directories(../../lib/googletest/include)
add_executable(${This} ${SOURCES})

target_link_libraries(${This}
                     gtest-main
                     MathApp
)       