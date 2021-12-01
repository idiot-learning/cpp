cmake_minimum_required(VERSION 3.18)
project(call_back)

set(TARGET example)
add_executable(${TARGET})


add_subdirectory(example)
add_subdirectory(src)
