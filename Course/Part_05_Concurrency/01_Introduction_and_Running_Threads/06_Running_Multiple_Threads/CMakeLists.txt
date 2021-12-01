cmake_minimum_required(VERSION 3.18)
project(06)

set(EXAMPLE "example_2")
add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
find_package(Threads)
target_link_libraries(${EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})