cmake_minimum_required(VERSION 3.18)
project(05)

set(EXAMPLE "quiz")
add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
find_package(Threads)
target_link_libraries(${EXAMPLE} ${CMAKE_THREAD_LIBS_INIT})