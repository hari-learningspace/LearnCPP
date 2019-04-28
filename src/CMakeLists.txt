cmake_minimum_required(VERSION 3.13)

set(This MathApp)
set(SOURCES ${This}.cpp)

include_directories()
      
add_library(${This} STATIC ${SOURCES})