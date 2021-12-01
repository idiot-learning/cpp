cmake_minimum_required(VERSION 3.18)
project(asyn)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")

set(EXAMPLE "example_3")
add_executable(${EXAMPLE} ${EXAMPLE}.cpp)