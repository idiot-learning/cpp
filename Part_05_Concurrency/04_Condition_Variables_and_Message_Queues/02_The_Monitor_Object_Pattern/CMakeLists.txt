cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")
project(monitor_object_pattern)

set(EXAMPLE "example_2_solution")
add_executable(${EXAMPLE} ${EXAMPLE}.cpp)