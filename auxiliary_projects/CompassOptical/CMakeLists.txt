cmake_minimum_required(VERSION 3.15)
project(CompassOptical C)

set(CMAKE_C_STANDARD 99)

add_executable(CompassOptical main.c)
# This is required for math.h to be included
target_link_libraries(CompassOptical m)