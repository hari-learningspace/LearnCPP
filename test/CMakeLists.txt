cmake_minimum_required(VERSION 3.13)


#set(This MathTest)
#set(SOURCES MathTest.cpp)
 
#set(This turtletest)
#set(SOURCES turtletest.cpp)

set(This testdb)
set(SOURCES testdb.cpp)

include_directories(../inc)
include_directories(../../lib/googletest/googletest/include ../../lib/googletest/googlemock/include)
add_executable(${This} ${SOURCES})
target_link_libraries(${This} 
                      gmock_main 
                    )

add_test(
    NAME ${This}
    COMMAND ${This}
)