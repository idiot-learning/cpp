cmake_minimum_required(VERSION 3.18)
project(promise_and_future)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")
set(EXAMPLE "example_4")

add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
